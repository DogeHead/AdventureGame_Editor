#include<windows.h>
#include"MyWindow.h"
#include"Monster.h"
#include"MenuScene.h"
#include"MainScene.h"
#include"FightScene.h"
#include"CharacterPropertyPannel.h"
#include"ObjectPannel.h"
#include"ObjectManager.h"
#include"MusicManager.h"
#include"GameUtil.h"



//ȫ�ֱ���
DWORD g_tNow=0, 
	g_tPre=0;
TCHAR* gameName = L"����ʩ����ѧ��ð��";//������

class GameMain{
	enum GameState { GS_MENU, GS_MAIN, GS_CHARACTERPROPERTY, GS_FIGHT,GS_OBJPANNEL } game_state;
//��Ϸ����
HWND m_hWnd;
RECT clientRect;
//��Ƶ����
CMusicManager musicManager;
//��Ϸ����
CMenuScene menu_scene;
CMainScene main_scene;
CFightScene fight_scene;

//��Ϸ���
CCharacterPropertyPannel property_pannel;
CObjectPannel obj_pannel;


CMainCharacter m_character[MAX_MCCOUNT];				//��Ϸ��ɫ

CObjectManager objManager;							//��Ʒ������



public:
	void setHWND(HWND hwnd){ m_hWnd = hwnd; }
	void setCRC(LPARAM lParam);


	HWND getHWND(){ return m_hWnd; }

	void newGame();
	void turnToPropertyPannel(WPARAM wParam);
	void turnToMain(WPARAM wParam);
	void turnToFight(WPARAM wParam);
	void turnToObjPannel();

	void GameInit(HWND hwnd);
	void Paint(HDC memHdc);
	void Handle();
	void Update();
	void WinFight(){ main_scene.WinFight(); }
}*gameMain;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//������Ӧ����
void		Object_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow);//������Ϣ��ʼ��
void		Game_Paint(HWND hwnd);		//��Ϸ��ͼ
void 		Game_Init(HWND hwnd);//��Ϸ��ʼ��
void		HandleKeys();//������Ӧ
void		Game_Update();//�߼�����
void		ClearGame();