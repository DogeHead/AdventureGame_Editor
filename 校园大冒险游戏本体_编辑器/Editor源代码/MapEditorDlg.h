
// MapEditorDlg.h : ͷ�ļ�
//

#pragma once
#include"stdafx.h"


// CMapEditorDlg �Ի���
class CMapEditorDlg : public CDialogEx
{
// ����
public:
	CMapEditorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAPEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	
	int *m_map;
	BITMAP m_nowBitmapInfo;
	HBITMAP m_updatedMap;
	CBitmap m_nowBitmap;
	CString FilePathName;
	CString m_csMapName;
	CRect m_rcClient;//�ͻ�������
	CRect m_rcBigBitmap;//��λͼ����
	CRect m_rcSmallBitmap;//Сλͼ����
	CRect m_rcMap;//��ͼ������
	BOOL m_bIsSelected;//�Ƿ�ѡ��Сλͼ
	int m_etCol;
	int m_etRow;
	int m_iSourceX, m_iSourceY;
	int m_iDestX, m_iDestY;
	int m_iXOffset, m_iYOffset;//x,y��ƫ����
	//��ѡ��ͼ
	CComboBox m_comboxMaps;
	vector<CString> m_vecMaps;
	int m_iMapIDStart;
	int m_iSourceCol, m_iSourceRow;
	CDialog* m_parentDlg;
	HBITMAP GetSmallBitmap(HBITMAP bitmap,int x,int y,int cx,int cy);


	BOOL GetGlobalArg();
	BOOL SaveMap();
	BOOL LoadMap();
	void LoadMap(CString mapName);

	void SetParentDlg(CDialog* dlg);
	BOOL ExportMapToBinary();
	void DrawMap(int row,int col,int *map);							//��m_updatedMapλͼ�ϻ�
	void UpdateMap();												//ͨ�����е�m_map����m_updateMap
	int getImageInfo(int num);										//ͨ��ש���Ż��ש������ͼƬ��Ϣ
	HBITMAP GetResourceMap(int num);								//ͨ����Ż�õ�ǰ����ͼƬ
	HBITMAP MyLoadBitmap(int num);
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelchangeCombo1();

	void InitCombox();
	
//	afx_msg void OnEnChangeEdit3();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void On32771();
//	afx_msg void OnBnClickedButton4();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);//�пؼ�����´����޷�ͨ���ú�����ü�������
	virtual BOOL PreTranslateMessage(MSG* pMsg);//�пؼ������ͨ���ú������������Ӧ
	afx_msg void OnBnClickedButton4();
};
