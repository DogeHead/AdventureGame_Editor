#include<windows.h>
#include"MainCharacter.h"
#include"Background.h"
#include"resource.h"

#pragma comment(lib, "Msimg32.lib")

class CCharacterPropertyPannel{
private:
	HWND m_hWnd;
	RECT m_rcClient;
	int m_iCharacterCount;					//��ɫ����
	int m_iCurShow;							//��ǰ��ʾ�ڼ�����ɫ��Ϣ
	CMainCharacter* m_mc;					//��ɫ��Ϣ��Ϊ�����޸ģ�ʹ��ָ��
	RECT m_rcArea[15];
	HBITMAP m_hBitmap;

	CBackground m_bg;
public:
	void Init(HWND hwnd,RECT* clientRc,CMainCharacter* mc);

	void Paint(HDC hdc);
	void Exit();
	void Handle();
};