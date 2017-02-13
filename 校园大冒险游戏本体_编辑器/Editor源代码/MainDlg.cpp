// MainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MapEditor.h"
#include "MainDlg.h"
#include "afxdialogex.h"


// CMainDlg �Ի���

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_SIZE()
	ON_COMMAND(ID_32771, &CMainDlg::On32771)
	ON_COMMAND(ID_32773, &CMainDlg::On32773)
	ON_COMMAND(ID_32774, &CMainDlg::On32774)
	ON_COMMAND(ID_32775, &CMainDlg::On32775)
	ON_COMMAND(ID_32777, &CMainDlg::On32777)
	ON_COMMAND(ID_32778, &CMainDlg::On32778)
END_MESSAGE_MAP()


// CMainDlg ��Ϣ�������


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_iCurSel = 0;
	m_mapDlg.Create(IDD_MAPEDITOR_DIALOG, GetDlgItem(IDC_GroupBox));
	m_objDlg.Create(IDD_OBJEDITOR_DIALOG, GetDlgItem(IDC_GroupBox));
	m_mapDlg.SetParentDlg(this);
	m_dlgs[0] = &m_mapDlg;
	m_dlgs[1] = &m_objDlg;
	ResizeWindow();
	SwitchWindow(MAPEDITOR_NUM);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRect rect;
	this->GetClientRect(&rect);
	
	CWnd* temp = GetDlgItem(IDC_GroupBox);
	if (temp)
	{
		ResizeWindow();
	}//m_mapDlg.MoveWindow(&rect);
	//m_objDlg.MoveWindow(&rect);
	// TODO:  �ڴ˴������Ϣ����������
}


void CMainDlg::On32771()
{
	// TODO:  �ڴ���������������
	m_mapDlg.On32771();
}


void CMainDlg::On32773()
{
	// TODO:  �ڴ���������������
	m_mapDlg.On32773();
}


void CMainDlg::On32774()
{
	// TODO:  �ڴ���������������
	m_mapDlg.On32774();
}


void CMainDlg::On32775()
{
	// TODO:  �ڴ���������������
	m_mapDlg.On32775();
}

void CMainDlg::SwitchWindow(int choice)
{
	m_dlgs[m_iCurSel]->ShowWindow(SW_HIDE);
	m_dlgs[choice]->ShowWindow(SW_SHOW);
	m_iCurSel = choice;
	CMenu* menu = GetMenu();
	switch (choice)
	{
	case MAPEDITOR_NUM:
		menu->EnableMenuItem(ID_32773, MF_ENABLED);
		menu->EnableMenuItem(ID_32774, MF_ENABLED);
		menu->EnableMenuItem(ID_32775, MF_ENABLED);
		this->SetWindowTextW(L"��ͼ�༭��");
		break;
	case OBJEDITOR_NUM:
		menu->EnableMenuItem(ID_32773, MF_GRAYED);
		menu->EnableMenuItem(ID_32774, MF_GRAYED);
		menu->EnableMenuItem(ID_32775, MF_GRAYED);
		this->SetWindowTextW(L"��Ʒ�༭��");
		break;
	}
	AfxGetMainWnd()->DrawMenuBar();
}


void CMainDlg::ResizeWindow()
{
	CRect rect;
	this->GetClientRect(&rect);
	for (int i = 0; i < DLG_COUNT; ++i)
		m_dlgs[i]->MoveWindow(&rect);
	CWnd* temp = GetDlgItem(IDC_GroupBox);
	temp->MoveWindow(&rect);
}

void CMainDlg::On32777()
{
	// TODO:  �ڴ���������������
	if (m_iCurSel == MAPEDITOR_NUM)
		return;
	SwitchWindow(MAPEDITOR_NUM);
}


void CMainDlg::On32778()
{
	// TODO:  �ڴ���������������
	if (m_iCurSel == OBJEDITOR_NUM)
		return;
	SwitchWindow(OBJEDITOR_NUM);
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���

	if (m_iCurSel == MAPEDITOR_NUM)
	{
		return m_mapDlg.PreTranslateMessage(pMsg);
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
