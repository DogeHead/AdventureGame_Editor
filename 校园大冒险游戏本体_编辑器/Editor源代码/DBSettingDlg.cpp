// DBSettingDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "DBSettingDlg.h"
#include "afxdialogex.h"


// CDBSettingDlg 对话框

IMPLEMENT_DYNAMIC(CDBSettingDlg, CDialogEx)

CDBSettingDlg::CDBSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDBSettingDlg::IDD, pParent)
	, m_csProvider(_T(""))
	, m_csDataSource(_T(""))
	, m_csDataBase(_T(""))
	, m_csIS(_T(""))
{

}

CDBSettingDlg::~CDBSettingDlg()
{
}

void CDBSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csProvider);
	DDX_Text(pDX, IDC_EDIT2, m_csDataSource);
	DDX_Text(pDX, IDC_EDIT4, m_csDataBase);
	DDX_Text(pDX, IDC_EDIT5, m_csIS);
}


BEGIN_MESSAGE_MAP(CDBSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDBSettingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &CDBSettingDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CDBSettingDlg::OnBnClickedButton4)

//	ON_EN_CHANGE(IDC_EDIT5, &CDBSettingDlg::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CDBSettingDlg 消息处理程序


BOOL CDBSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetPrivateProfileString(INI_NAME, KEY_PROVIDER, L"NULL", m_csProvider.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_DATASOURCE, L"NULL", m_csDataSource.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_DATABASE, L"NULL", m_csDataBase.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_IS, L"NULL", m_csIS.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDBSettingDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	WriteCurSetting();
	SendMessage(WM_CLOSE);
}


void CDBSettingDlg::OnBnClickedButton5()
{
	// TODO:  在此添加控件通知处理程序代码
	if (IDYES == MessageBox(L"是否恢复默认值", L"注意", MB_YESNO))
	{
		m_csProvider = DEFAULT_PROVIDER;
		m_csDataSource = DEFAULT_DATASOURCE;
		m_csDataBase = DEFAULT_DATABASE;
		m_csIS = DEFAULT_IS;
		UpdateData(FALSE);

		WriteCurSetting();
	}
}


void CDBSettingDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	SendMessage(WM_CLOSE);
}
void CDBSettingDlg::WriteCurSetting()
{
	WritePrivateProfileString(INI_NAME, KEY_PROVIDER, m_csProvider, DATABASE_INI_PATH);
	WritePrivateProfileString(INI_NAME, KEY_DATASOURCE, m_csDataSource, DATABASE_INI_PATH);
	WritePrivateProfileString(INI_NAME, KEY_DATABASE, m_csDataBase, DATABASE_INI_PATH);
	WritePrivateProfileString(INI_NAME, KEY_IS, m_csIS, DATABASE_INI_PATH);

	global_provider = m_csProvider;
	global_dataSource = m_csDataSource;
	global_database = m_csDataBase;
	global_integratedSecurity = m_csIS;


}
BOOL CDBSettingDlg::GetGlobalArg()
{
	CFileFind finder;
	BOOL isFind = finder.FindFile(DATABASE_INI_PATH);

	if (!isFind){
		WritePrivateProfileString(INI_NAME, KEY_PROVIDER, DEFAULT_PROVIDER, DATABASE_INI_PATH);
		WritePrivateProfileString(INI_NAME, KEY_DATASOURCE, DEFAULT_DATASOURCE, DATABASE_INI_PATH);
		WritePrivateProfileString(INI_NAME, KEY_DATABASE, DEFAULT_DATABASE, DATABASE_INI_PATH);
		WritePrivateProfileString(INI_NAME, KEY_IS, DEFAULT_IS, DATABASE_INI_PATH);
	}
	GetPrivateProfileString(INI_NAME, KEY_PROVIDER, L"NULL", global_provider.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_DATASOURCE, L"NULL", global_dataSource.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_DATABASE, L"NULL", global_database.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);
	GetPrivateProfileString(INI_NAME, KEY_IS, L"NULL", global_integratedSecurity.GetBuffer(MAX_PATH), MAX_PATH, DATABASE_INI_PATH);

	//设置数据库表
	global_table = DEFAULT_TB;
	global_tool_table = DEFAULT_TOOL_TB;
	global_equipment_table = DEFAULT_EQUIPMENT_TB;
	global_medicine_table = DEFAULT_MEDICINE_TB;
	return TRUE;
}
