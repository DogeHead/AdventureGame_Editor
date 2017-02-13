#include"SkillAnime.h"


void CSkillAnime::Init(TCHAR* name, int picCount, int allFrame)
{
	lstrcpy(m_csName, name);
	m_iPicCount = picCount;
	m_iAllFrame = allFrame;
	m_iCurFrame = 0;
	m_iEachPicFrame = m_iAllFrame / m_iPicCount;
}
void CSkillAnime::Paint(HDC hdc, int x, int y,int cx,int cy)
{
	
	int picNum = m_iCurFrame / m_iEachPicFrame + 1;
	if (picNum > m_iPicCount)
		picNum -= 2;
	TCHAR imageName[64];
	wsprintf(imageName, L"%s%s%d.bmp", PATH_SKILL, m_csName, picNum);
	
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, imageName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (bitmap==NULL)
		MessageBox(NULL, imageName, L"2", MB_OK);
	CGraphHelper::MyTransparentBlt(hdc, bitmap, x, y,cx,cy,RGB(255,255,255));
	if (++m_iCurFrame >= m_iAllFrame)
		m_iCurFrame = 0;
}