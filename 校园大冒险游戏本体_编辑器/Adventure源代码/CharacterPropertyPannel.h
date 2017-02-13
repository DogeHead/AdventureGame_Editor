#include<windows.h>
#include"MainCharacter.h"
#include"Background.h"
#include"resource.h"

#pragma comment(lib, "Msimg32.lib")

class CCharacterPropertyPannel{
private:
	HWND m_hWnd;
	RECT m_rcClient;
	int m_iCharacterCount;					//角色数量
	int m_iCurShow;							//当前显示第几个角色信息
	CMainCharacter* m_mc;					//角色信息，为方便修改，使用指针
	RECT m_rcArea[15];
	HBITMAP m_hBitmap;

	CBackground m_bg;
public:
	void Init(HWND hwnd,RECT* clientRc,CMainCharacter* mc);

	void Paint(HDC hdc);
	void Exit();
	void Handle();
};