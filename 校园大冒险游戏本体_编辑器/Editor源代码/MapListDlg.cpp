// MapListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MapListDlg.h"
#include "afxdialogex.h"


// CMapListDlg �Ի���

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


// CMapListDlg ��Ϣ�������
BOOL CMapListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_mainDialog != NULL)
	{
		CString mapName;
		m_lbMapList.GetText(m_lbMapList.GetCurSel(), mapName);
		m_mainDialog->LoadMap(mapName);
	}
}
