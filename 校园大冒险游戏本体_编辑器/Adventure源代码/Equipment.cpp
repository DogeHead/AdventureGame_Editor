#include"Equipment.h"

void CEquipment::Init(TCHAR *name)
{
	lstrcpy(m_csName, name);
	lstrcpy(m_csIntro, L"屠龙宝刀，点击就送");

	//m_objectType = OT_EQUIPMENT;
	m_iMaxHP = 100;
	m_iMaxMP = 0;
	m_iZhiyu = 10;
	m_iTiyu = 10;			
	m_iDeyu = 10;
	m_iPhysicalAttack = 100;
	m_iPhysicalDefense = 0;
	m_iMagicAttack = 0;
	m_iCritChance = 80;
	m_iEvdChance = 0;
	m_iMagicDefense = 0;
	m_iActionSpeed = 0;
	m_iCount = 1;
	m_type = ET_WEAPON;

	
}
BOOL CEquipment::LoadData(TCHAR *name)
{
	lstrcpy(m_csName, name);
	ifstream ifs;
	ifs.open(PATH_DAT_EQUIPMENT, ios::binary);
	ifs.seekg(0, ios::beg);
	while (!ifs.eof())
	{
		CEquipment_ equipment;
		ifs.read((char*)&equipment, sizeof(CEquipment_));
		if (lstrcmp(name, equipment.m_csName) == 0)
		{
			lstrcpy(this->m_csIntro, equipment.m_csIntro);
			lstrcpy(this->m_csName, equipment.m_csName);
			this->m_iActionSpeed = equipment.m_iActionSpeed;
			this->m_iCount = equipment.m_iCount;
			this->m_iCritChance = equipment.m_iCritChance;
			this->m_iDeyu = equipment.m_iDeyu;
			this->m_iEvdChance = equipment.m_iEvdChance;
			this->m_iMagicAttack = equipment.m_iMagicAttack;
			this->m_iMagicDefense = equipment.m_iMagicDefense;
			this->m_iMaxHP = equipment.m_iMaxHP;
			this->m_iMaxMP = equipment.m_iMaxMP;
			this->m_iPhysicalAttack = equipment.m_iPhysicalAttack;
			this->m_iPhysicalDefense = equipment.m_iPhysicalDefense;
			this->m_iTiyu = equipment.m_iTiyu;
			this->m_iZhiyu = equipment.m_iZhiyu;
			switch (equipment.m_type)
			{
			case CEquipment_::ET_WEAPON:
				this->m_type = ET_WEAPON;
				break;
			case CEquipment_::ET_1:
				this->m_type = ET_1;
				break;
			case CEquipment_::ET_2:
				this->m_type = ET_2;
				break;
			case CEquipment_::ET_3:
				this->m_type = ET_3;
				break;
			case CEquipment_::ET_4:
				this->m_type = ET_4;
				break;
			case CEquipment_::ET_5:
				this->m_type = ET_5;
				break;

			}
			ifs.close();
			return TRUE;
		}
	}
	return FALSE;
}
void CEquipment::Paint(HDC hdc, int x, int y, int cx, int cy)
{
	static HBITMAP m_bitmap;
	static BOOL flag = TRUE;
	if (flag)
	{
		flag = FALSE;
		TCHAR str[128];
		wsprintf(str, L"%s%s.bmp", PATH_IMAGE_EQUIPMENT, m_csName);
		m_bitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	if (m_bitmap != NULL)
		CGraphHelper::MyTransparentBlt(hdc, m_bitmap, x, y, cx, cy);
}
void CEquipment::ListMoreInfo(TCHAR* str)
{
	lstrcpy(str, L"");
	TCHAR tempStr[256];
	if (m_iMaxHP)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n最大生命值+ %d", tempStr, m_iMaxHP);
	}
	if (m_iMaxMP){
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n最大魔法值+ %d", tempStr, m_iMaxMP);
	}
	if (m_iZhiyu)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n智育+ %d", tempStr, m_iZhiyu);
	}
	if (m_iTiyu)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n体育+ %d", tempStr, m_iTiyu);
	}
	if (m_iDeyu)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n德育+ %d", tempStr, m_iDeyu);
	}
	if (m_iPhysicalAttack)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n物理攻击+ %d", tempStr, m_iPhysicalAttack);
	}
	if (m_iPhysicalDefense)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n物理防御+ %d", tempStr, m_iPhysicalDefense);
	}
	if (m_iMagicAttack)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n魔法攻击+ %d", tempStr, m_iMagicAttack);
	}
	if (m_iMagicDefense)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n魔法防御+ %d", tempStr, m_iMagicDefense);
	}
	if (m_iCritChance)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n暴击率+ %d", tempStr, m_iCritChance);
	}
	if (m_iEvdChance)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n闪避率+ %d", tempStr, m_iEvdChance);
	}
	if (m_iActionSpeed)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n反应力+ %d", tempStr, m_iActionSpeed);
	}
}