#pragma once


// CDBSettingDlg �Ի���
#include"resource.h"


class CDBSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDBSettingDlg)

public:
	CDBSettingDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDBSettingDlg();

// �Ի�������
	enum { IDD = IDD_SETTING_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
