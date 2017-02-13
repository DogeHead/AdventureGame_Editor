#include<windows.h>
#include<time.h>
#include<fstream>
#include"GameUtil.h"
#include"MainCharacter.h"
#include"FunctionArea.h"
#include"resource.h"
#pragma comment(lib, "Msimg32.lib")
using namespace std;
class CMainScene{
private:
	HWND m_hWnd;
	
	BOOL *m_bIsMon;						//该位置是否为怪物
	int *map;							//地图
	int m_iNowMapNum;					//当前地图编号
	int m_iColCount;
	int m_iRowCount;
	int m_iShowRowCount;				//显示的行数
	int m_iShowColCount;				//显示的列数
	POINT m_ptCharacter;
	//HBITMAP m_bitmap[7];
	RECT m_rcClient;
	int m_idx, m_idy;					//人物原位置跟新位置所距像素
	int m_iMonXPos, m_iMonYPos;
	
	//功能区
	BOOL m_bIsFunctionHidden;
	CFunctionArea m_functionArea;
	
	//角色
	int m_iMCCount;
	CMainCharacter* m_character;

public:
	void Init(HWND hwnd, RECT clientRc, CMainCharacter* mc,int mcCount);
	void Paint(HDC hdc);
	void Handle();
	void Update();
	void BufferBitBltDraw(HDC destHdc, int x1, int y1, int cx, int cy, HBITMAP sourceBitmap, int x2, int y2);
	void SwitchDraw(HDC destHdc, int x1, int y1, int cx, int cy, int type);
	void DefeatMonster(int x, int y){ m_bIsMon[y*m_iColCount + x] = FALSE; }

	void Clear();

	void LoadMonster(int size);//读取怪物
	void LoadMap();//读取地图
	void SetMap(int choice){ m_iNowMapNum = choice; }
	void Fight();
	void WinFight();
	BOOL CanWalk(int x, int y,int type);
	BOOL ExistMon(int x, int y);
};