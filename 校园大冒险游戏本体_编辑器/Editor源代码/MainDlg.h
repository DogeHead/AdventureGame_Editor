#pragma once
#include"MapEditorDlg.h"
#include"ObjEditorDlg.h"

// CMainDlg �Ի���
#define MAPEDITOR_NUM 0
#define OBJEDITOR_NUM 1


#define DLG_COUNT 2
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

	//��¼��ǰ��ʾҳ�������
	int m_iCurSel;

	//���Ի������
	CMapEditorDlg m_mapDlg;
	CObjEditorDlg m_objDlg;
	CDialog *m_dlgs[DLG_COUNT];//�Ի�������

	void SwitchWindow(int choice);
	void ResizeWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void On32771();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32777();//�л�Ϊ��ͼ�༭��
	afx_msg void On32778();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
