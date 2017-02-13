#include"Monster.h"


void CMonster::Init(TCHAR* name, int maxHP, int hp, int atk, int dfs){
	lstrcpy(m_csName, name);
	m_bIsDead = FALSE;
	m_iMaxHP = maxHP;
	m_iHP = hp;
	m_iPhysicalAttack = atk;
	m_iMagicAttack = atk / 2;
	m_iPhysicalDefense = dfs;
	m_iMagicDefense = dfs;
	m_iActionSpeed = 4;
	m_bShowDamage = FALSE;
	m_iMoney = 5;
	m_iExp = 5;

}

void CMonster::Paint(HDC hdc, int x, int y,int size)
{
	//首先读取位图
	static 	HBITMAP m_bitmap;
	static BOOL flag = TRUE;
	if (flag)
	{
		flag = FALSE;
		TCHAR tempName[128];
		wsprintf(tempName, L"%s%s.bmp", PATH_IMAGE, m_csName);
		m_bitmap = (HBITMAP)LoadImage(NULL, tempName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		if (m_bitmap == NULL)
		{
			MessageBox(NULL, L"error", L"", MB_OK);
		}
	}

	CGraphHelper::MyTransparentBlt(hdc, m_bitmap, x, y, EACH_WIDTH*size, EACH_HEIGHT*size);
	if (m_bShowDamage){
		SetTextColor(hdc, RGB(255, 0, 0));
		TCHAR tempStr[16];
		wsprintf(tempStr, L"-%d", m_iDamage);
		TextOut(hdc, x+5, y - 10, tempStr, wcslen(tempStr));
	}
	
}
void CMonster::Update()
{
	if (rand()%5==0)
		m_actionTypes = AT_SKILL;
	else 
		m_actionTypes = AT_NORMAL;
}
void CMonster::BeAttacked(int damage){
	m_iHP -= damage;
	m_iDamage = damage;
	m_bShowDamage = TRUE;
	if (m_iHP <=0)
	{
		m_iHP = 0;
		m_bIsDead = TRUE;
	}
}
void CMonster::Attack(CCreature* mc, int mcCount)
{
	int realDamage = 0;
	if (m_actionTypes == AT_SKILL){
		
		for (int i = 0; i < mcCount; ++i){
			int mdfs = ((CMainCharacter*)mc)[i].GetMagicDefense();
			int damage = m_iMagicAttack - mdfs;
			realDamage = 1>damage ? 1 : damage;
			((CMainCharacter*)mc)[i].BeAttacked(realDamage);
		}
	}
	else if (m_actionTypes == AT_NORMAL){
		int ran = rand() % mcCount;
		int pdfs = ((CMainCharacter*)mc)[ran].GetPhysicalDefense();
		int damage = m_iPhysicalAttack - pdfs;
		realDamage = 1 > damage ? 1 : damage;
		((CMainCharacter*)mc)[ran].BeAttacked(realDamage);
	}

}