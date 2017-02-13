#include<windows.h>
#include"MainCharacter.h"
#include"GameUtil.h"
#define AREA_SPACE 30
class CFunctionArea{
private:
	HWND m_hWnd;
	int m_iFunctionCount;//功能数目
	int m_iCurSelect;//当前选择位置
	RECT m_rcFunction[10];
	TCHAR m_csFunction[10][16];
	RECT m_rcClient;
	
	CMainCharacter* m_character;//角色
	COLORREF m_colorSelect,
		m_colorNoSelect;
public:
	void Init(HWND hwnd, RECT clientRc, CMainCharacter* character);
	void Handle();
	void Paint(HDC hdc);
};