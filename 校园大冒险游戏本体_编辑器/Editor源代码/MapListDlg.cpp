// MapListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapListDlg.h"
#include "afxdialogex.h"


// CMapListDlg 对话框

IMPLEMENT_DYNAMIC(CMapListDlg, CDialogEx)

CMapListDlg::CMapListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMapListDlg::IDD, pParent)
{
	m_mainDialog = NULL;
}

CMapListDlg::~CMapListDlg()
{
}

void CMapListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbMapList);
}


BEGIN_MESSAGE_MAP(CMapListDlg, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST1, &CMapListDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CMapListDlg 消息处理程序
BOOL CMapListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	GetMapList();
	AddStringToListBox(m_vecMapNameList);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CMapListDlg::GetMapList()
{
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();
	dbHelper.GetMapNameList(m_vecMapNameList);

	dbHelper.CoInitDBHelper();
}
void CMapListDlg::AddStringToListBox(vector<CString> vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		m_lbMapList.AddString(vec[i]);
	}
}
void CMapListDlg::SetMainDlg(CMapEditorDlg* dlg)
{
	m_mainDialog = dlg;
}

void CMapListDlg::OnLbnDblclkList1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_mainDialog != NULL)
	{
		CString mapName;
		m_lbMapList.GetText(m_lbMapList.GetCurSel(), mapName);
		m_mainDialog->LoadMap(mapName);
	}
}
