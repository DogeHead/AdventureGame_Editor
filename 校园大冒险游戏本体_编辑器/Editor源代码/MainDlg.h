#pragma once
#include"MapEditorDlg.h"
#include"ObjEditorDlg.h"

// CMainDlg 对话框
#define MAPEDITOR_NUM 0
#define OBJEDITOR_NUM 1


#define DLG_COUNT 2
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainDlg();

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

	//记录当前显示页面的索引
	int m_iCurSel;

	//属对话框对象
	CMapEditorDlg m_mapDlg;
	CObjEditorDlg m_objDlg;
	CDialog *m_dlgs[DLG_COUNT];//对话框数组

	void SwitchWindow(int choice);
	void ResizeWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void On32771();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32777();//切换为地图编辑器
	afx_msg void On32778();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
