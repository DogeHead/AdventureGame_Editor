#pragma once
#include<windows.h>
#include"MainCharacter.h"
#include"Background.h"
#include"ObjectManager.h"
#define CHOICE_MEDICINE 0
#define CHOICE_EQUIPMENT 1
#define CHOICE_TOOL 2
//��Ʒ��壬������ʾ��Ʒ��Ϣ
class CObjectPannel{
	//����ѡ��׶Σ���Ʒѡ��׶Σ�ʹ�ý׶�,ѡ�˽׶�
	enum ObjPannelState{OP_TYPESEL,OP_OBJSEL,OP_USE,OP_SELMC}m_opState;
private:
	HWND m_hWnd;
	//��������
	RECT m_rcClient,
		m_rcArea[4];							//0Ϊҩ�װ��������ѡ�1Ϊ��Ʒ��Ϣ��2Ϊʹ�á�װ��ѡ�3��Ʒ����
	CBackground	m_bg;							//����
	CMainCharacter* m_pMc;						//��ɫ��Ϣ
	CObjectManager* m_pObjManager;				//��Ʒ��Ϣ
	int m_iMcCount;


	TCHAR m_csOption[5][8];						//ѡ�����Ϊ:ҩ�װ�������ߣ�װ����ʹ��

	//����ѡ��׶�
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		int choice,
			maxChoice;
	}m_typeSelState;
	//��Ʒѡ��׶�
	struct{
		int maxRow,
		maxCol,								//���������
		curX,								//��ǰѡ��λ�õ�X,Yֵ
		curY;
	}m_objSelState;
	//ʹ�ý׶�
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		int choice,
			maxChoice;
	}m_useState;
	//ѡ�����ý�ɫ�׶�
	struct{
		COLORREF color_sel = RGB(255, 255, 255),
		color_nor = RGB(0, 0, 0);
		BOOL showMsg;
		TCHAR msg[256];
		int choice;
		int maxChoice;
	}m_selMCState;
	
	//������һ��
	void TurnTypeSelState();
	void TurnObjSelState();
	void TurnUseState();
	void TurnSelMCState();

	//�뿪��ǰ״̬��������һ��
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