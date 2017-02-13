#pragma once
#include "afxwin.h"
#include"MapEditorDlg.h"
#include<vector>
using namespace std;

// CMapListDlg 对话框

class CMapListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMapListDlg)

	vector<CString> m_vecMapNameList;
public:
	CMapListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMapListDlg();

// 对话框数据
	enum { IDD = IDD_MAPLIST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lbMapList;
	CMapEditorDlg* m_mainDialog;

	void SetMainDlg(CMapEditorDlg* dlg);
	void AddStringToListBox(vector<CString> vec);
	void GetMapList();
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnDblclkList1();
};
