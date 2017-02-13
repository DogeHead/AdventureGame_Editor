#include"Medicine.h"

void CMedicine::Init(TCHAR* name)
{
	lstrcpy(m_csName, name);
	lstrcpy(m_csIntro, L"测试介绍");
	//m_objectType = OT_MEDICINE;
	
	m_iCount = 1;
	m_iMaxHP = 0;
	m_iHP = 20;
	m_iMaxMP = 0;
	m_iMP = 10;
	m_iExp = 0;
	m_bUnscramble = FALSE;
}

BOOL CMedicine::LoadData(TCHAR *name)
{
	lstrcpy(m_csName, name);
	
	fstream ifs;
	ifs.open(PATH_DAT_MEDICINE, ios::in | ios::binary);
	ifs.seekg(0, ios::beg);
	CMedicine_ medicine;
	while(!ifs.eof()){
		ifs.read((char*)&medicine, sizeof(CMedicine_));

		if (lstrcmp(name, medicine.m_csName) == 0)
		{
			this->m_bUnscramble = medicine.m_bUnscramble;
			lstrcpy(this->m_csIntro, medicine.m_csIntro);
			lstrcpy(this->m_csName, medicine.m_csName);
			this->m_iCount = medicine.m_iCount;
			this->m_iExp = medicine.m_iExp;
			this->m_iHP = medicine.m_iHP;
			this->m_iMaxHP = medicine.m_iMaxHP;
			this->m_iMaxMP = medicine.m_iMaxMP;
			this->m_iMP = medicine.m_iMP;
			ifs.close();
			return TRUE;
		}
	}
	return FALSE;
}

void CMedicine::Paint(HDC hdc, int x, int y, int cx, int cy)
{
	static BOOL flag = TRUE;
	static HBITMAP m_bitmap;
	if (flag){
		flag = FALSE;
		TCHAR tempStr[128];
		wsprintf(tempStr, L"%s%s.bmp", PATH_IMAGE_MEDICINE, m_csName);
		m_bitmap = (HBITMAP)LoadImage(NULL, tempStr, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	if (m_bitmap!=NULL)
		CGraphHelper::MyTransparentBlt(hdc, m_bitmap, x, y, cx, cy);
}
void CMedicine::BeUsed()
{
	--m_iCount;
}
void CMedicine::ListMoreInfo(TCHAR* str)
{
	lstrcpy(str, L"");
	TCHAR tempStr[128];
	if (m_iHP)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n+ %d 生命", tempStr,m_iHP);
	}
	if (m_iMP){
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n+ %d 魔法", tempStr,m_iMP);
	}
	if (m_iMaxHP)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n+ %d 最大生命值", tempStr, m_iMaxHP);
	}
	if (m_iMaxMP)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n最+ %d 最大魔法值", tempStr, m_iMaxMP);
	}
	if (m_iExp)
	{
		wsprintf(tempStr, str);
		wsprintf(str, L"%s\n+ %d 经验值", tempStr, m_iExp);
	}
}