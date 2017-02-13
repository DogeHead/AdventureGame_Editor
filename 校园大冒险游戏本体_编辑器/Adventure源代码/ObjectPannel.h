#pragma once
#include<windows.h>
#include"MainCharacter.h"
#include"Background.h"
#include"ObjectManager.h"
#define CHOICE_MEDICINE 0
#define CHOICE_EQUIPMENT 1
#define CHOICE_TOOL 2
//物品面板，用来显示物品信息
class CObjectPannel{
	//类型选择阶段，物品选择阶段，使用阶段,选人阶段
	enum ObjPannelState{OP_TYPESEL,OP_OBJSEL,OP_USE,OP_SELMC}m_opState;
private:
	HWND m_hWnd;
	//划分区域
	RECT m_rcClient,
		m_rcArea[4];							//0为药物、装备、道具选项，1为物品信息，2为使用、装备选项、3物品陈列
	CBackground	m_bg;							//背景
	CMainCharacter* m_pMc;						//角色信息
	CObjectManager* m_pObjManager;				//物品信息
	int m_iMcCount;


	TCHAR m_csOption[5][8];						//选项，依次为:药物，装备，道具，装备，使用

	//类型选择阶段
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		int choice,
			maxChoice;
	}m_typeSelState;
	//物品选择阶段
	struct{
		int maxRow,
		maxCol,								//最大行列数
		curX,								//当前选中位置的X,Y值
		curY;
	}m_objSelState;
	//使用阶段
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		int choice,
			maxChoice;
	}m_useState;
	//选择作用角色阶段
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		BOOL showMsg;
		TCHAR msg[256];
		int choice;
		int maxChoice;
	}m_selMCState;
	
	//进入下一级
	void TurnTypeSelState();
	void TurnObjSelState();
	void TurnUseState();
	void TurnSelMCState();

	//离开当前状态，返回上一级
	void ExitTypeSelState();
	void ExitObjSelState();
	void ExitUseState();
	void ExitSelMCState();
	
	void TypeSelHandle();
	void ObjSelHandle();
	void UseStateHandle();
	void SelMCHandle();
	
	void PaintObj(HDC hdc);
	void PaintObjData(HDC hdc);
	void PaintMCSel(HDC hdc);
public:
	void Init(HWND hwnd, RECT client, CMainCharacter* mc, CObjectManager* objManager);
	void Paint(HDC hdc);
	
	void Handle();

	
	
};