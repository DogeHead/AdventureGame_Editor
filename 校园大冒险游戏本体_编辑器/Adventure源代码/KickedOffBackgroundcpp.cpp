#include"KickedOffBackground.h"

CKickedOffBackground::CKickedOffBackground()
{
	m_iAllFrame = m_iCurFrame = 0;
}
void CKickedOffBackground::Init(int frame, TCHAR* name)
{
	m_iAllFrame = frame;
	m_iCurFrame = 0;
	CBackground::Init(name);
}
void CKickedOffBackground::Paint(HDC hdc, RECT rc)
{
	HDC memdc = CreateCompatibleDC(hdc);

	SelectObject(memdc, m_bitmap);
	BITMAP bitmap;
	GetObject(m_bitmap, sizeof(BITMAP), &bitmap);
	int bitmapHalf = bitmap.bmWidth / 2,//位图的一半宽度
		screenHalf = (rc.right - rc.left) / 2;//屏幕宽的一半
	int height = rc.bottom - rc.top;//屏幕的高
	int dx = screenHalf / m_iAllFrame;//每次偏移量
	
	//贴左侧的图
	TransparentBlt(hdc, rc.left-m_iCurFrame*dx, rc.top, screenHalf, height,
		memdc, 0, 0, bitmapHalf, bitmap.bmHeight, RGB(255, 255, 255));
	//贴右侧的图
	TransparentBlt(hdc, screenHalf + m_iCurFrame*dx, rc.top, screenHalf, height,
		memdc, bitmapHalf, 0, bitmapHalf, bitmap.bmHeight, RGB(255, 255, 255));
	DeleteObject(memdc);
}
void CKickedOffBackground::Update()
{
	if (++m_iCurFrame > m_iAllFrame)
		m_iCurFrame = 0;
	
}