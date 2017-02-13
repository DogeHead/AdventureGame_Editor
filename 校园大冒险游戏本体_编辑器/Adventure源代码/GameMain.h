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



//全局变量
DWORD g_tNow=0, 
	g_tPre=0;
TCHAR* gameName = L"华南施工大学大冒险";//窗口名

class GameMain{
	enum GameState { GS_MENU, GS_MAIN, GS_CHARACTERPROPERTY, GS_FIGHT,GS_OBJPANNEL } game_state;
//游戏窗口
HWND m_hWnd;
RECT clientRect;
//音频管理
CMusicManager musicManager;
//游戏场景
CMenuScene menu_scene;
CMainScene main_scene;
CFightScene fight_scene;

//游戏面板
CCharacterPropertyPannel property_pannel;
CObjectPannel obj_pannel;


CMainCharacter m_character[MAX_MCCOUNT];				//游戏角色

CObjectManager objManager;							//物品管理器



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

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);//窗口响应函数
void		Object_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow);//窗口信息初始化
void		Game_Paint(HWND hwnd);		//游戏绘图
void 		Game_Init(HWND hwnd);//游戏初始化
void		HandleKeys();//操作响应
void		Game_Update();//逻辑更新
void		ClearGame();