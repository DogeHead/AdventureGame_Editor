
// MapEditorDlg.h : 头文件
//

#pragma once
#include"stdafx.h"


// CMapEditorDlg 对话框
class CMapEditorDlg : public CDialogEx
{
// 构造
public:
	CMapEditorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAPEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	CRect m_rcClient;//客户区区域
	CRect m_rcBigBitmap;//大位图区域
	CRect m_rcSmallBitmap;//小位图区域
	CRect m_rcMap;//地图的区域
	BOOL m_bIsSelected;//是否选中小位图
	int m_etCol;
	int m_etRow;
	int m_iSourceX, m_iSourceY;
	int m_iDestX, m_iDestY;
	int m_iXOffset, m_iYOffset;//x,y轴偏移量
	//可选地图
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
	void DrawMap(int row,int col,int *map);							//在m_updatedMap位图上画
	void UpdateMap();												//通过已有的m_map画出m_updateMap
	int getImageInfo(int num);										//通过砖块编号获得砖块所在图片信息
	HBITMAP GetResourceMap(int num);								//通过编号获得当前所需图片
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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);//有控件情况下窗口无法通过该函数获得键盘输入
	virtual BOOL PreTranslateMessage(MSG* pMsg);//有控件情况下通过该函数处理键盘响应
	afx_msg void OnBnClickedButton4();
};
