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
	int bitmapHalf = bitmap.bmWidth / 2,//λͼ��һ����
		screenHalf = (rc.right - rc.left) / 2;//��Ļ���һ��
	int height = rc.bottom - rc.top;//��Ļ�ĸ�
	int dx = screenHalf / m_iAllFrame;//ÿ��ƫ����
	
	//������ͼ
	TransparentBlt(hdc, rc.left-m_iCurFrame*dx, rc.top, screenHalf, height,
		memdc, 0, 0, bitmapHalf, bitmap.bmHeight, RGB(255, 255, 255));
	//���Ҳ��ͼ
	TransparentBlt(hdc, screenHalf + m_iCurFrame*dx, rc.top, screenHalf, height,
		memdc, bitmapHalf, 0, bitmapHalf, bitmap.bmHeight, RGB(255, 255, 255));
	DeleteObject(memdc);
}
void CKickedOffBackground::Update()
{
	if (++m_iCurFrame > m_iAllFrame)
		m_iCurFrame = 0;
	
}