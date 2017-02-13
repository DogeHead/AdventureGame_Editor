#pragma once
#include<windows.h>

class CGraphHelper{
public:
	static void MyTransparentBlt(HDC hdc, HBITMAP bmp, int x, int y, int cx, int cy,COLORREF color=RGB(0,0,0));
	static void MyRectangle(HDC hdc, RECT &rc, COLORREF color = RGB(166, 166, 166));
	static void MyBitBlt(HDC hdc, HBITMAP bmp, int x, int y);
};

