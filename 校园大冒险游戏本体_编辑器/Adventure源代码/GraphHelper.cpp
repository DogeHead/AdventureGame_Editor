#include"GraphHelper.h"


void CGraphHelper::MyTransparentBlt(HDC hdc, HBITMAP bmp, int x, int y, int cx, int cy, COLORREF color)
{
	HDC memdc = CreateCompatibleDC(hdc);
	
	HBITMAP oldBmp=(HBITMAP)SelectObject(memdc, bmp);
	BITMAP bitmap;
	GetObject(bmp, sizeof(BITMAP), &bitmap);
	TransparentBlt(hdc, x, y, cx, cy, memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, color);
	SelectObject(memdc, oldBmp);
	DeleteObject(memdc);
	
}
void CGraphHelper::MyRectangle(HDC hdc, RECT &rc, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(RGB(128, 128, 128));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}
void CGraphHelper::MyBitBlt(HDC hdc, HBITMAP bmp, int x, int y)
{
	HDC memdc = CreateCompatibleDC(hdc);

	HBITMAP oldBmp = (HBITMAP)SelectObject(memdc, bmp);
	BITMAP bitmap;
	GetObject(bmp, sizeof(BITMAP), &bitmap);
	BitBlt(hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, memdc, 0, 0,SRCCOPY);
	SelectObject(memdc, oldBmp);
	DeleteObject(memdc);
}