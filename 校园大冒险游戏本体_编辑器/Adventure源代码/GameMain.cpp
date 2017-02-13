#include"GameMain.h"




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow)
{
	//初始化窗口信息
	Object_Init(hInstance,hPrevInstance,szCmdLine,iCmdShow);
	
	//将窗口置于屏幕中央
	int ix = GetSystemMetrics(SM_CXSCREEN) / 2 - WINWIDTH / 2;
	int iy = GetSystemMetrics(SM_CYSCREEN) / 2 - WINWIDTH / 2;
	MoveWindow(gameMain->getHWND(), ix, iy, WINWIDTH, WINHEIGHT, true);

	ShowWindow(gameMain->getHWND(), iCmdShow);
	UpdateWindow(gameMain->getHWND());
	//MessageBox(NULL, L"123", L"32", MB_OK);
	
	Game_Init(gameMain->getHWND());
	MSG msg = { 0 };				//定义并初始化msg
	
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_tNow = GetTickCount();
			if (g_tNow - g_tPre >= GAME_FRAME)       
			{	
				static int test = 0;
				if (++test >= GAME_FRAME / 20)
				{
					test = 0;
					HandleKeys();
				}
				
				Game_Update();
				Game_Paint(gameMain->getHWND());
				g_tPre = g_tNow;
			}
			
		}
		
	}
	ClearGame();
	return 0;
}


void Object_Init(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow){
	gameMain = new GameMain();

	//设置 窗口类信息
	WNDCLASS                      wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = WndProc;

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = 0;

	wndclass.hInstance = hInstance;

	wndclass.hIcon = LoadIcon(NULL, IDI_INFORMATION);

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

	wndclass.lpszMenuName = NULL;

	wndclass.lpszClassName = gameName;
	//注册 窗口类
	if (!RegisterClass(&wndclass))

	{

		MessageBox(NULL, TEXT("This program requires Windows NT!"),

			gameName, MB_ICONERROR);

		return;

	}
	
	HWND hwnd = CreateWindow(gameName, gameName, WS_OVERLAPPEDWINDOW^WS_MAXIMIZEBOX^WS_THICKFRAME ,//禁用最大化按钮与边框

		CW_USEDEFAULT, CW_USEDEFAULT,

		WINWIDTH, WINHEIGHT,

		NULL, NULL, hInstance, NULL);
	gameMain->setHWND(hwnd);
}




LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

{


	switch (message)

	{
	case WM_SIZE:
	{
					gameMain->setCRC(lParam);
	}
		return 0;
	case MSG_TURN_PROPERTY_PANNEL:
	{
					gameMain->turnToPropertyPannel(wParam);
	}
		return 0;
	case MSG_TURN_OBJ_PANNEL:
	{
					gameMain->turnToObjPannel();
	}
		return 0;
	case MSG_TURN_MAIN:
	{
					gameMain->turnToMain(wParam);
						 
						 // main_scene.Init(hwnd,clientRect);
	}
		return 0;
	case MSG_NEW_GAME:
	{
						 gameMain->newGame();
	}
		return 0;
	case MSG_FIGHT:
	{
					  gameMain->turnToFight(wParam);
	}
		break;
	case MSG_WIN_FIGHT:
	{
						  gameMain->WinFight();
						  gameMain->turnToMain(wParam);
	}
		break;
	case   WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}
void Game_Paint(HWND hwnd){
	HDC hdc = GetDC(hwnd);
	HDC memHdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, WINWIDTH, WINHEIGHT);
	HBITMAP oldBitmap = (HBITMAP)SelectObject(memHdc, hBitmap);

	gameMain->Paint(memHdc);

	BitBlt(hdc, 0, 0, WINWIDTH, WINHEIGHT, memHdc, 0, 0, SRCCOPY);

	SelectObject(memHdc, oldBitmap);
	
	DeleteObject(hBitmap);
	DeleteObject(memHdc);
	
	ReleaseDC(hwnd, hdc);
}
void HandleKeys(){
	

	gameMain->Handle();
}
void Game_Update()
{
	gameMain->Update();
}
void Game_Init(HWND hwnd)
{
	gameMain->GameInit(hwnd);
}
void ClearGame()
{
	delete gameMain;
}


//GameMain部分
void  GameMain::GameInit(HWND hwnd)
{
	srand((unsigned)time(NULL));
	game_state = GS_MENU;
	menu_scene.Init(hwnd, clientRect);
	musicManager.PlayMusicLoop(MS_MENU);
	m_character[0].Init(CMainCharacter::PeopleCareer::PC_COMPUTER);
}
void GameMain::Paint(HDC memHdc)
{
	switch (game_state)
	{
	case GS_MENU:
	{
					menu_scene.Paint(memHdc);
	}
		break;
	case GS_MAIN:
	{
					main_scene.Paint(memHdc);
	}
		break;
	case GS_CHARACTERPROPERTY:
	{
					property_pannel.Paint(memHdc);
	}
		break;
	case GS_FIGHT:
	{
					 fight_scene.Paint(memHdc);
	}
		break;
	case GS_OBJPANNEL:{
			obj_pannel.Paint(memHdc);
		}
		break;
	}
}
void GameMain::Handle()
{
	switch (game_state)
	{
	case GS_MENU:
	{
					menu_scene.Handle();
	}
		break;
	case GS_MAIN:
	{
					main_scene.Handle();
	}
		break;
	case GS_CHARACTERPROPERTY:
	{
					property_pannel.Handle();
	}
		break;
	case GS_FIGHT:
	{
					fight_scene.Handle();
	}
		break;
	case GS_OBJPANNEL:{
						  obj_pannel.Handle();
	}
		break;
	}
}
void GameMain::Update()
{
	switch (game_state)
	{
	case GS_MAIN:
	{
					main_scene.Update();
	}
		break;
	case GS_FIGHT:
	{
					 fight_scene.Update();
	}
		break;
	}
}

void GameMain::turnToFight(WPARAM wParam)
{
	musicManager.StopMusic();
	musicManager.PlayMusicLoop(MS_BATTLE_C12);
	game_state = GS_FIGHT;
	fight_scene.Init(m_hWnd, &clientRect,wParam,m_character);
	
}

void GameMain::turnToMain(WPARAM wParam)
{
	//musicManager.StopMusic();
	if (wParam!=WPARAM_KEEP_MUSIC)
		musicManager.PlayMusicLoop(MS_MAIN_C12);
	game_state = GS_MAIN;
	main_scene.LoadMap();
	
}
void GameMain::turnToPropertyPannel(WPARAM wParam)
{
	game_state = GS_CHARACTERPROPERTY;
	property_pannel.Init(m_hWnd, &clientRect, (CMainCharacter*)wParam);
}
void GameMain::turnToObjPannel()
{
	game_state = GS_OBJPANNEL;

}
void GameMain::newGame()
{
	musicManager.StopMusic();
	musicManager.PlayMusicLoop(MS_MAIN_C12);
	game_state = GS_MAIN;
	main_scene.Init(m_hWnd, clientRect,m_character,1);
	objManager.Init();
	obj_pannel.Init(m_hWnd,clientRect,m_character,&objManager);
}
void GameMain::setCRC(LPARAM lParam)
{
	clientRect.top = clientRect.left = 0;
	clientRect.right = LOWORD(lParam);
	clientRect.bottom = HIWORD(lParam);
}