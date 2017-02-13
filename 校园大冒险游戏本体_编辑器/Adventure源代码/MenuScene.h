#include<windows.h>
#include"Scene.h"
#include"GameUtil.h"
#include"Background.h"
class CMenuScene:public CScene{
private:
	HWND hwnd;
	int m_maxRow;
	int m_choseRow;
	RECT text_rect[3];
	TCHAR text[3][32];
	COLORREF color_selected, color_normal;
	CBackground m_bg;
	RECT m_rcClient;
public:
	virtual void Init(HWND hwnd,RECT& rect);
	virtual void Paint(HDC hdc);
	virtual void Handle();
};