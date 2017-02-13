#pragma once


// CDBSettingDlg 对话框
#include"resource.h"


class CDBSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBSettingDlg)

public:
	CDBSettingDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDBSettingDlg();

// 对话框数据
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_csProvider;
	CString m_csDataSource;
	CString m_csDataBase;
	CString m_csIS;


	void WriteCurSetting();
	static BOOL GetGlobalArg();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	
	
};
