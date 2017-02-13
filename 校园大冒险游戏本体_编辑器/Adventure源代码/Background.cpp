#include"Background.h"

void CBackground::Init(TCHAR* name)
{
	lstrcpy(m_csName, name);

	TCHAR tempName[128];
	wsprintf(tempName, L"%s%s.bmp", PATH_BG, m_csName);
	m_bitmap = (HBITMAP)LoadImage(NULL, tempName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (m_bitmap == NULL)
	{
		MessageBox(NULL, L"Background bitmap load fail", L"error", MB_OK);
	}
}
void CBackground::Paint(HDC hdc,RECT rc)
{
	CGraphHelper::MyTransparentBlt(hdc, m_bitmap, 0, 0, rc.right - rc.left, rc.bottom - rc.top,RGB(255,255,255));
}