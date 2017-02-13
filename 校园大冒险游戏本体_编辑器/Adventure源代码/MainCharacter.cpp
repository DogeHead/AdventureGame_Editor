#include"MainCharacter.h"

void CMainCharacter::Init(PeopleCareer pc)
{
	m_action = 0;
	m_maxAction = 4;
	m_dir = DIR_DOWN;

	SetName(L"����");

	m_iLevel = 0;
	m_iZhiyu = 1;
	m_iTiyu = 1;
	m_iDeyu = 1;
	m_iExp = 0;

	m_iLevelUpExp = 10;

	m_iMaxHP = 50;
	m_iPhysicalAttack = 5;
	m_iPhysicalDefense = 5;
	m_iMaxMP = 20;
	m_iMagicAttack = 5;
	m_iCritChance = 0;
	m_iEvdChance = 0;
	m_iMagicDefense = 5;
	m_iActionSpeed = 5;

	m_iHP = m_iMaxHP;
	m_iMP = m_iMaxMP;
	m_actionTypes = AT_NORMAL;

	m_iDamage = 0;
	m_bShowDamage = FALSE;

	if (pc == PC_COMPUTER){
		lstrcpyW(m_csCareer, L"�����רҵ");
	}
	else if (pc == PC_SPORTS){
		lstrcpy(m_csCareer, L"����רҵ");
	}
	else if (pc == PC_FOOD){
		lstrcpy(m_csCareer, L"ʳƷרҵ");
	}

	//װ����ʼ��
	memset(&m_equipment, 0, sizeof(m_equipment));
	for (int i = 0; i < EQUIPMENT_COUNT; ++i)
	{
		m_equipment.bIsExist[i] = FALSE;
		m_equipment.equipment[i] = NULL;
	}
}
void CMainCharacter::Paint(HDC hdc,int x,int y)
{
	HDC memHdc = CreateCompatibleDC(hdc);
	BITMAP bm;
	GetObject(m_bitmapCharacter, sizeof(bm), &bm);
	int realY = y + EACH_HEIGHT - bm.bmHeight/4;
	SelectObject(memHdc, m_bitmapCharacter);
	//BitBlt(hdc, x, y, EACH_WIDTH, EACH_HEIGHT, memHdc, m_action*EACH_WIDTH, m_dir*EACH_HEIGHT, SRCCOPY);
	int each_width = bm.bmWidth / 4,
		each_height = bm.bmHeight / 4;
	TransparentBlt(hdc, x, realY, each_width, each_height,
		memHdc, m_action*each_width, m_dir*each_height, each_width, each_height, RGB(0, 0, 0));
	DeleteObject(memHdc);
	ZeroMemory(&bm, sizeof(bm));

}
void CMainCharacter::PaintFightMC(HDC hdc, int x, int y)
{
	CGraphHelper::MyTransparentBlt(hdc, m_bitmapFightCharacter, x, y, 2 * EACH_WIDTH, 3 * EACH_HEIGHT);
	if (m_bShowDamage){
		SetTextColor(hdc, RGB(255, 0, 0));
		TCHAR tempStr[16];
		wsprintf(tempStr, L"-%d", m_iDamage);
		TextOut(hdc, x + 30, y - 10, tempStr, wcslen(tempStr));
	}
}
void CMainCharacter::Update()
{
	if (m_bIsWalk)
	{
		++m_action;

		if (m_action == m_maxAction)
		{
			m_action = 0;
			m_bIsWalk = FALSE;
		}
	}
	
}

void CMainCharacter::SetName(TCHAR *name)
{
	lstrcpy(m_csName, name);
	if (lstrcmp(name, L"����")==0){
		m_bitmapCharacter = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP4));
		TCHAR str[128];
		wsprintf(str, L"%s%s.bmp", PATH_IMAGE_CHARACTER, name);
		m_bitmapFightCharacter = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
}

void CMainCharacter::Attack(int monNum, CCreature *mon, int selMon)
{
	//������õ�����ͨ����
	if (m_actionTypes == AT_NORMAL)
	{
		//��ȡ�������
		int monDefense = ((CMonster*)mon)[selMon].GetPhysicalDefense();
		//������-�������
		int damage = (m_iPhysicalAttack - monDefense);
		((CMonster*)mon)[selMon].BeAttacked(damage);
		((CMonster*)mon)[selMon].SetShowDamage(TRUE);
	}
	else if (m_actionTypes == AT_SKILL){
		//��ȡħ������
		int monDefense = ((CMonster*)mon)[selMon].GetMagicDefense();
		//ħ������-ħ������
		int damage = (m_iMagicAttack - monDefense);
		for (int i = 0; i < monNum; ++i)
		{
			((CMonster*)mon)[i].BeAttacked(damage);
		}
	}
}
void CMainCharacter::BeAttacked(int damage)
{
	m_iHP -= damage;
	m_iDamage = damage;
	m_bShowDamage = TRUE;
	if (m_iHP <= 0)
	{
		m_iHP = 0;
	}
}
int CMainCharacter::UseMedicine(CMedicine* medicine, CObjectManager* manager, TCHAR* resultStr)
{
	if (medicine->GetCount() <= 0){
		lstrcpy(resultStr, L"�����ڸ���Ʒ");
		return 0;
	}
	lstrcpy(resultStr, L"");
	TCHAR tempStr[128];
	if (medicine->m_iHP)
	{
		m_iHP += medicine->m_iHP;
		m_iHP = min(m_iHP, m_iMaxHP);
		wsprintf(tempStr, resultStr);
		wsprintf(resultStr, L"%s\n�ָ�����ֵ %d", tempStr, medicine->m_iHP);
	}
	if (medicine->m_iMP){
		m_iMP += medicine->m_iMP;
		m_iMP = min(m_iMP, m_iMaxMP);
		wsprintf(tempStr, resultStr);
		wsprintf(resultStr, L"%s\n�ָ�ħ��ֵ %d", tempStr, medicine->m_iMP);
	}
	if (medicine->m_iMaxHP)
	{
		m_iMaxHP += medicine->m_iMaxHP;
		wsprintf(tempStr, resultStr);
		wsprintf(resultStr, L"%s\n�������ֵ���� %d", tempStr, medicine->m_iMaxHP);
	}
	if (medicine->m_iMaxMP)
	{
		m_iMaxMP += medicine->m_iMaxMP;
		wsprintf(tempStr, resultStr);
		wsprintf(resultStr, L"%s\n���ħ��ֵ���� %d", tempStr, medicine->m_iMaxMP);
	}
	if (medicine->m_iExp)
	{

		GainExp(medicine->m_iExp);
		wsprintf(tempStr, resultStr);
		wsprintf(resultStr, L"%s\n����ֵ���� %d", tempStr, medicine->m_iExp);
	}
	medicine->BeUsed();
	manager->CheckObjectRunOut(medicine->GetName(), CObjectManager::ObjectType::OT_MEDI);
	return medicine->m_iCount;
}
void  CMainCharacter::WearEquipment(CEquipment* equipment, CObjectManager* manager)
{
	int pos;
	switch (equipment->m_type)
	{
	case CEquipment::ET_WEAPON:
		pos = 0;
		break;
	default:
		pos = 1;
	}
	//���ԭ����װ����������
	if (m_equipment.bIsExist[pos])
	{
		UnWearEquipment(pos);
		
		manager->GetNewObject((CMyObject*)(m_equipment.equipment[pos]), CObjectManager::OT_EQUI);
		
	}
	--equipment->m_iCount;
	manager->CheckObjectRunOut(equipment->GetName(), CObjectManager::OT_EQUI);
	//������װ��
	m_equipment.bIsExist[pos] = TRUE;
	m_equipment.equipment[pos] = equipment;

	//���HP
	if (m_equipment.equipment[pos]->m_iMaxHP)
	{
		m_iMaxHP += m_equipment.equipment[pos]->m_iMaxHP;
		m_iHP += m_equipment.equipment[pos]->m_iMaxHP;
	}
	//���MP
	if (m_equipment.equipment[pos]->m_iMaxMP)
	{
		m_iMaxMP += m_equipment.equipment[pos]->m_iMaxMP;
		m_iMP += m_equipment.equipment[pos]->m_iMaxMP;
	}
	//����
	if (m_equipment.equipment[pos]->m_iZhiyu)
	{
		m_iZhiyu += m_equipment.equipment[pos]->m_iZhiyu;
		m_iMaxMP += m_equipment.equipment[pos]->m_iZhiyu * 10;
	}
	//����
	if (m_equipment.equipment[pos]->m_iTiyu)
	{
		m_iTiyu += m_equipment.equipment[pos]->m_iTiyu;
		m_iMaxHP += m_equipment.equipment[pos]->m_iTiyu * 10;
	}
	//����
	if (m_equipment.equipment[pos]->m_iDeyu)
	{
		m_iDeyu += m_equipment.equipment[pos]->m_iDeyu;
	}
	//������
	if (m_equipment.equipment[pos]->m_iPhysicalAttack)
	{
		m_iPhysicalAttack += m_equipment.equipment[pos]->m_iPhysicalAttack;
	}
	//�������
	if (m_equipment.equipment[pos]->m_iPhysicalDefense)
	{
		m_iPhysicalDefense += m_equipment.equipment[pos]->m_iPhysicalDefense;
	}
	//ħ������
	if (m_equipment.equipment[pos]->m_iMagicAttack)
	{
		m_iMagicAttack += m_equipment.equipment[pos]->m_iMagicAttack;
	}
	//����
	if (m_equipment.equipment[pos]->m_iCritChance)
	{
		m_iCritChance += m_equipment.equipment[pos]->m_iCritChance;
	}
	//����
	if (m_equipment.equipment[pos]->m_iEvdChance)
	{
		m_iEvdChance += m_equipment.equipment[pos]->m_iEvdChance;
	}
	//ħ������
	if (m_equipment.equipment[pos]->m_iMagicDefense)
	{
		m_iMagicDefense += m_equipment.equipment[pos]->m_iMagicDefense;
	}
	//�ٶ�
	if (m_equipment.equipment[pos]->m_iActionSpeed)
	{
		m_iActionSpeed += m_equipment.equipment[pos]->m_iActionSpeed;
	}
}
void CMainCharacter::UnWearEquipment(int pos)
{
	//���HP
	if (m_equipment.equipment[pos]->m_iMaxHP)
	{
		m_iMaxHP -= m_equipment.equipment[pos]->m_iMaxHP;
		m_iHP -= m_equipment.equipment[pos]->m_iMaxHP;
	}
	//���MP
	if (m_equipment.equipment[pos]->m_iMaxMP)
	{
		m_iMaxMP -= m_equipment.equipment[pos]->m_iMaxMP;
		m_iMP -= m_equipment.equipment[pos]->m_iMaxMP;
	}
	//����
	if (m_equipment.equipment[pos]->m_iZhiyu)
	{
		m_iZhiyu -= m_equipment.equipment[pos]->m_iZhiyu;
		m_iMaxMP -= m_equipment.equipment[pos]->m_iZhiyu * 10;
	}
	//����
	if (m_equipment.equipment[pos]->m_iTiyu)
	{
		m_iTiyu -= m_equipment.equipment[pos]->m_iTiyu;
		m_iMaxHP -= m_equipment.equipment[pos]->m_iTiyu * 10;
	}
	//����
	if (m_equipment.equipment[pos]->m_iDeyu)
	{
		m_iDeyu -= m_equipment.equipment[pos]->m_iDeyu;
	}
	//������
	if (m_equipment.equipment[pos]->m_iPhysicalAttack)
	{
		m_iPhysicalAttack -= m_equipment.equipment[pos]->m_iPhysicalAttack;
	}
	//�������
	if (m_equipment.equipment[pos]->m_iPhysicalDefense)
	{
		m_iPhysicalDefense -= m_equipment.equipment[pos]->m_iPhysicalDefense;
	}
	//ħ������
	if (m_equipment.equipment[pos]->m_iMagicAttack)
	{
		m_iMagicAttack -= m_equipment.equipment[pos]->m_iMagicAttack;
	}
	//����
	if (m_equipment.equipment[pos]->m_iCritChance)
	{
		m_iCritChance -= m_equipment.equipment[pos]->m_iCritChance;
	}
	//����
	if (m_equipment.equipment[pos]->m_iEvdChance)
	{
		m_iEvdChance -= m_equipment.equipment[pos]->m_iEvdChance;
	}
	//ħ������
	if (m_equipment.equipment[pos]->m_iMagicDefense)
	{
		m_iMagicDefense -= m_equipment.equipment[pos]->m_iMagicDefense;
	}
	//�ٶ�
	if (m_equipment.equipment[pos]->m_iActionSpeed)
	{
		m_iActionSpeed -= m_equipment.equipment[pos]->m_iActionSpeed;
	}
}
void CMainCharacter::GainExp(int exp)
{
	m_iExp += exp;
	while (m_iExp >= m_iLevelUpExp)
	{
		++m_iLevel;
		m_iExp -= m_iLevelUpExp;
		m_iLevelUpExp += m_iLevel * 10;
	}
}
