#include<windows.h>
#include<time.h>
#include"Background.h"
#include"KickedOffBackground.h"
#include"MainCharacter.h"
#include"Monster.h"
#include"SkillAnime.h"
#include"GameUtil.h"
class CFightScene
{
private:
	//战斗状态:战斗结束，战斗中，战斗结束
	enum FightState{FS_OVER,FS_FIGHT,FS_LOADING};
	
	FightState m_fsState;			//当前状态
	RECT m_rcClient;				//屏幕矩阵
	int m_iFrame;					//当前帧
	int m_iMapNum;					//当前地图编号
	//指令类型
	enum CmdState{CS_CMD,CS_SELMON,};

	const int maxMonNum = MAX_MONCOUNT;//最大怪物数量
	CMonster m_mon[MAX_MONCOUNT];	//本场战斗怪物信息
	CMainCharacter* m_mc;			//本场战斗主角信息
	int m_iMcCount;					//本场战斗人物数量

	CBackground m_bg;				//背景
	CSkillAnime m_skillAnime;		//技能动画
	//读取阶段
	CKickedOffBackground m_koBg;	//揭开序幕的背景
	int m_iLoadingFrame;			//读取帧数

	//战斗中阶段
	int m_iActionTurn[MAX_MONCOUNT + MAX_MCCOUNT];		//出手顺序
	int m_iMonCount;				//本场战斗怪物数量
	POINT m_ptMonPos[5];			//怪物的五个位置
	RECT m_rcChaPos[5];				//主角的五个位置
	int m_iFrameNum;				//当前位于第几帧
	int m_iCurActionNum;			//当前轮到第几个出手

	//指令阶段
	CmdState m_cmdState;			//何种指令
	BOOL m_bIsCmd;					//处于指令阶段
	int m_iCurCmd;					//当前选定指令
	RECT m_rcCmd;					//指令区域
	TCHAR m_csCmd[4][16];			//指令
	RECT m_rcEachCmd[4];			//各个指令区域
	RECT m_rcMcState[5];			//主角状态面板区域
	int m_iSelMon;					//当前选定怪物

	//结束阶段
	int money,
		exp;


	HWND m_hWnd;
	
	void paintLoading(HDC hdc);		//绘制读取界面
	void paintGameOver(HDC hdc);
	void paintFight(HDC hdc);

	void upateLoading();
	void upateGameOver();
	void upateFight();

	void handleLoading();
	void handleGameOver();
	void handleFight();

	void Exit();					//逃跑
	void WinFight();				//赢得战斗
	void InitActionTurn();			//初始化出手顺序
	BOOL IsGameOver();
	void ClearShow();				//清除受到伤害显示
public:
	void Init(HWND hwnd,RECT* rc,int mapNum,CMainCharacter* mc);
	
	void Paint(HDC hdc);
	void Handle();
	void Update();
	void randMon(int mapNum);//根据m_iMapNum生成怪物
};