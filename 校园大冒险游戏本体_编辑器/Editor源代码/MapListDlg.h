#pragma once
#include "afxwin.h"
#include"MapEditorDlg.h"
#include<vector>
using namespace std;

// CMapListDlg �Ի���

class CMapListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMapListDlg)

	vector<CString> m_vecMapNameList;
public:
	CMapListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMapListDlg();

// �Ի�������
	enum { IDD = IDD_MAPLIST_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
