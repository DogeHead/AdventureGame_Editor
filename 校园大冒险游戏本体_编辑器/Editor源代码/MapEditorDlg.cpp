
// MapEditorDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "afxdialogex.h"
#include "MapEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorDlg 对话框



CMapEditorDlg::CMapEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMapEditorDlg::IDD, pParent)
	, m_etCol(0)
	, m_etRow(0)
	, m_csMapName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_etCol);
	DDV_MinMaxInt(pDX, m_etCol, 0, 100);
	DDX_Text(pDX, IDC_EDIT1, m_etRow);
	DDV_MinMaxInt(pDX, m_etRow, 0, 100);
	DDX_Control(pDX, IDC_COMBO1, m_comboxMaps);
	DDX_Text(pDX, IDC_EDIT3, m_csMapName);
}

BEGIN_MESSAGE_MAP(CMapEditorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON1, &CMapEditorDlg::OnBnClickedButton1)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON3, &CMapEditorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapEditorDlg::OnBnClickedButton2)
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapEditorDlg::OnCbnSelchangeCombo1)
//	ON_EN_CHANGE(IDC_EDIT3, &CMapEditorDlg::OnEnChangeEdit3)
ON_BN_CLICKED(IDC_BUTTON1, &CMapEditorDlg::OnBnClickedButton1)
ON_COMMAND(ID_32771, &CMapEditorDlg::On32771)
//ON_BN_CLICKED(IDC_BUTTON4, &CMapEditorDlg::OnBnClickedButton4)
ON_COMMAND(ID_32773, &CMapEditorDlg::On32773)
ON_COMMAND(ID_32774, &CMapEditorDlg::On32774)
ON_COMMAND(ID_32775, &CMapEditorDlg::On32775)
ON_WM_KEYDOWN()
ON_BN_CLICKED(IDC_BUTTON4, &CMapEditorDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMapEditorDlg 消息处理程序

BOOL CMapEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	if (FALSE == GetGlobalArg())
	{
		MessageBox(L"获得数据库设置失败，无法进行数据库操作");
	}

	this->GetClientRect(&m_rcClient);
	m_map = NULL;
	m_rcBigBitmap.top = 150;
	m_rcBigBitmap.bottom = m_rcClient.bottom;
	m_rcBigBitmap.left = 0;
	m_rcBigBitmap.right = 450;

	m_rcSmallBitmap.top = 108;
	m_rcSmallBitmap.left = 0;
	m_rcSmallBitmap.right = m_rcSmallBitmap.left + EACH_WIDTH;
	m_rcSmallBitmap.bottom = m_rcSmallBitmap.top + EACH_HEIGHT;

	m_rcMap.top = 0;
	m_rcMap.left = 450;
	m_rcMap.right = m_rcClient.right;
	m_rcMap.bottom = m_rcClient.bottom;

	m_iSourceX = m_iSourceY = -1;
	m_iXOffset = m_iYOffset = 0;
	m_updatedMap = NULL;
	m_bIsSelected = FALSE;

	InitCombox();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
BOOL  CMapEditorDlg::GetGlobalArg()
{
	return CDBSettingDlg::GetGlobalArg();
}
// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMapEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		CDC* clientDC = GetDC();

		CDC memdc;
		memdc.CreateCompatibleDC(clientDC);
		HBITMAP oldBitmap=(HBITMAP)memdc.SelectObject(m_nowBitmap);
		//绘制m_rcBigBitmap区域
		clientDC->BitBlt(m_rcBigBitmap.left, m_rcBigBitmap.top, m_nowBitmapInfo.bmWidth, m_nowBitmapInfo.bmHeight, &memdc, 0, 0, SRCCOPY);
		
		if (m_iSourceX != -1){
				//画个绿色小方框
				CPen pen;
				HPEN oldPen;
				pen.CreatePen(PS_SOLID, 1,RGB(0,255,0));
				oldPen=(HPEN)clientDC->SelectObject(pen);
				int left, top, right, bottom;
				left = m_rcBigBitmap.left + m_iSourceX*EACH_WIDTH;
				top = m_rcBigBitmap.top + m_iSourceY*EACH_HEIGHT;
				right = left + EACH_WIDTH;
				bottom = top + EACH_HEIGHT;
				clientDC->MoveTo(left,top);
				clientDC->LineTo(right,top);
				clientDC->LineTo(right, bottom);
				clientDC->LineTo(left, bottom);
				clientDC->LineTo(left,top);
				clientDC->SelectObject(oldPen);
				pen.DeleteObject();
				
		}
		//绘制m_rcSmallBitmap区域
		//在小位图处绘制选中位图

		memdc.SelectObject(m_nowBitmap);

		clientDC->BitBlt(m_rcSmallBitmap.left, m_rcSmallBitmap.top, EACH_WIDTH, EACH_HEIGHT, &memdc,
		m_iSourceX*EACH_WIDTH, m_iSourceY*EACH_HEIGHT, SRCCOPY);

		//绘制分割线
		CPen pen;
		HPEN oldPen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		oldPen = (HPEN)clientDC->SelectObject(pen);

		clientDC->MoveTo(m_rcMap.left, m_rcMap.top);
		clientDC->LineTo(m_rcMap.left, m_rcClient.bottom);

		clientDC->MoveTo(m_rcClient.left, m_rcBigBitmap.top);
		clientDC->LineTo(m_rcMap.left, m_rcBigBitmap.top);

		clientDC->MoveTo(m_rcSmallBitmap.left, m_rcSmallBitmap.top);
		clientDC->LineTo(m_rcSmallBitmap.right , m_rcSmallBitmap.top);
		clientDC->LineTo(m_rcSmallBitmap.right, m_rcSmallBitmap.bottom);
		clientDC->LineTo(m_rcSmallBitmap.left, m_rcSmallBitmap.bottom);
		clientDC->LineTo(m_rcSmallBitmap.left, m_rcSmallBitmap.top);

		clientDC->SelectObject(oldPen);
		pen.DeleteObject();

		//绘制m_rcMap区域
		if (m_etCol > 0 && m_etRow > 0)
		{
			memdc.SelectObject(m_updatedMap);
			int remainX = (m_etCol - m_iXOffset)*EACH_WIDTH,
				remainY = (m_etRow - m_iYOffset)*EACH_HEIGHT;
			int clientX = (m_rcMap.right - m_rcMap.left)/EACH_WIDTH*EACH_WIDTH,
				clientY = m_rcMap.bottom - m_rcMap.top/EACH_HEIGHT*EACH_HEIGHT;//取整
			int tempX = remainX < clientX ? remainX : clientX,
				tempY = remainY < clientY ? remainY : clientY;

			clientDC->BitBlt(m_rcMap.left, m_rcMap.top, tempX, tempY,
				&memdc, m_iXOffset*EACH_WIDTH, m_iYOffset*EACH_HEIGHT, SRCCOPY);
		}
		
		memdc.SelectObject(oldBitmap);
		memdc.DeleteDC();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMapEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMapEditorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC* cdc = GetDC();

	if (m_rcBigBitmap.PtInRect(point)){
		
		//如果在当前位图区域
		if (point.x >= m_rcBigBitmap.left&&point.y >= m_rcBigBitmap.top&&
			point.x <= m_rcBigBitmap.left + m_nowBitmapInfo.bmWidth&&
			point.y <= m_rcBigBitmap.top + m_nowBitmapInfo.bmHeight)
		{
			//将选中标志设为TRUE
			m_bIsSelected = TRUE;

			m_iSourceX = (point.x - m_rcBigBitmap.left) / EACH_WIDTH;
			m_iSourceY = (point.y - m_rcBigBitmap.top) / EACH_HEIGHT;

			this->Invalidate();
		}
	}
	else if (m_rcMap.PtInRect(point)&&m_etCol>0&&m_etRow>0)
	{
		//m_parentDlg->SetFocus();
		if (m_bIsSelected)
		{
			m_iDestX = (point.x - m_rcMap.left) / EACH_WIDTH;
			m_iDestY = (point.y - m_rcMap.top) / EACH_HEIGHT;

			//在数组中记录，x,y的值得加上偏移量
			m_map[(m_iDestX+m_iXOffset) + (m_iDestY+m_iYOffset)*m_etCol] = m_iMapIDStart + m_iSourceX + m_iSourceY*m_iSourceCol;

			CDC memdc, bufferdc;
			memdc.CreateCompatibleDC(cdc);
			bufferdc.CreateCompatibleDC(cdc);
			HBITMAP hBitmap = CreateCompatibleBitmap(::GetDC(this->m_hWnd), m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT);
			HBITMAP oldBitmap = (HBITMAP)bufferdc.SelectObject(hBitmap);
			//先将原图贴入
			memdc.SelectObject(m_updatedMap);
			bufferdc.BitBlt(0, 0, m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT, &memdc, 0, 0, SRCCOPY);
			//在缓存位图中加上偏移量的位置贴上图片
			memdc.SelectObject(m_nowBitmap);
			bufferdc.BitBlt((m_iDestX+m_iXOffset)*EACH_WIDTH, (m_iDestY+m_iYOffset)*EACH_HEIGHT, EACH_WIDTH, EACH_HEIGHT,
				&memdc, m_iSourceX*EACH_WIDTH, m_iSourceY*EACH_HEIGHT, SRCCOPY);

			DeleteObject(m_updatedMap);
			m_updatedMap = (HBITMAP)bufferdc.SelectObject(oldBitmap);

			//DeleteObject(hBitmap);
			bufferdc.DeleteDC();
			memdc.DeleteDC();
			this->Invalidate();

		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMapEditorDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	if (m_updatedMap != NULL)
		DeleteObject(m_updatedMap);
	m_updatedMap=CreateCompatibleBitmap(::GetDC(this->m_hWnd), m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT);

	m_rcMap.right = m_rcMap.left + m_etCol*EACH_WIDTH;
	m_rcMap.bottom = m_rcMap.top + m_etRow*EACH_HEIGHT;

	CDC* clientdc = GetDC();
	CDC memdc;
	memdc.CreateCompatibleDC(clientdc);
	HBITMAP oldBitmap = (HBITMAP)memdc.SelectObject(m_updatedMap);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	memdc.SelectObject(pen);
	//画横线
	for (int i = 0; i <= m_etRow;++i)
	{
		memdc.MoveTo(0, i*EACH_HEIGHT);
		memdc.LineTo(m_etCol*EACH_WIDTH, i*EACH_HEIGHT);
	}
	//画竖线
	for (int i = 0; i <= m_etCol; ++i)
	{
		memdc.MoveTo(i*EACH_WIDTH, 0);
		memdc.LineTo(i*EACH_WIDTH, m_etRow*EACH_HEIGHT);
	}
	
	if (m_map != NULL)
	{
		delete[]m_map;
	}
	m_map = new int[m_etCol*m_etRow];
	for (int i = 0; i < m_etCol*m_etRow; ++i)
		m_map[i] = 0;
	//偏移量置零
	m_iXOffset = m_iYOffset = 0;
	//不可删除m_updatedMap，否则会导致位图消失
	//DeleteObject(m_updatedMap);
	m_updatedMap = (HBITMAP)memdc.SelectObject(oldBitmap);
	this->Invalidate();
}

//保存地图按钮
void CMapEditorDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_csMapName == L"")
	{
		MessageBox(L"地图名不可为空", L"Error", MB_OK);
		return;
	}
	if (m_etRow <= 0 || m_etCol <= 0)
	{
		MessageBox(L"行或列需要大于0");
		return;
	}
	if (FALSE == SaveMap())
	{
		return;
	}
	MessageBox(L"保存地图成功");
}
HBITMAP CMapEditorDlg::GetSmallBitmap(HBITMAP bitmap, int x, int y,int cx,int cy)
{
	if (bitmap != NULL)
	{
		HDC memdc, bufferdc;
			memdc=CreateCompatibleDC(NULL);
			bufferdc = CreateCompatibleDC(NULL);
			HBITMAP hBitmap = CreateCompatibleBitmap(memdc, cx, cy);
			HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
			HBITMAP hOldBitmap2 = (HBITMAP)SelectObject(bufferdc, bitmap);
			BitBlt(memdc, 0, 0, cx, cy, bufferdc, x, y, SRCCOPY);

			DeleteObject(hBitmap);
			hBitmap = (HBITMAP)SelectObject(memdc, hOldBitmap);

			SelectObject(bufferdc, hOldBitmap2);
			DeleteObject(bufferdc);
			DeleteObject(memdc);
			return hBitmap;
	}
	else{
		HDC memdc;
		memdc = CreateCompatibleDC(NULL);
		HBITMAP hBitmap = CreateCompatibleBitmap(memdc, cx, cy);
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);

		DeleteObject(hBitmap);
		hBitmap = (HBITMAP)SelectObject(memdc, hOldBitmap);

		DeleteObject(memdc);
		return hBitmap;
	}
	
}

void CMapEditorDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	this->GetClientRect(&m_rcClient);
}

void CMapEditorDlg::InitCombox()
{
	if (!m_vecMaps.empty())
		m_vecMaps.clear();
	m_vecMaps.push_back(L"Map_1");
	m_vecMaps.push_back(L"Map_2");
	m_vecMaps.push_back(L"Map_3");
	for (int i = 0; i < m_vecMaps.size();++i)
	m_comboxMaps.AddString(m_vecMaps[i]);
}

void CMapEditorDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	
	const int index=m_comboxMaps.GetCurSel();
	
	HBITMAP hbitmap;
	switch (index)
	{
	case 0:
		hbitmap = MyLoadBitmap(IDB_MAP1);
		m_iMapIDStart = MAP1_START;
		break;
	case 1:
		hbitmap = MyLoadBitmap(IDB_MAP2);
		m_iMapIDStart = MAP2_START;
		break;
	case 2:
		hbitmap = MyLoadBitmap(IDB_MAP3);
		m_iMapIDStart = MAP3_START;
		break;
	}
	m_nowBitmap.Detach();
	if (FALSE == m_nowBitmap.Attach(hbitmap))
	{
		MessageBox(L"位图文件加载失败");
		return;
	}
	ZeroMemory(&m_nowBitmapInfo, sizeof(m_nowBitmapInfo));
	m_nowBitmap.GetBitmap(&m_nowBitmapInfo);

	m_iSourceCol = m_nowBitmapInfo.bmWidth / EACH_WIDTH;
	m_iSourceRow = m_nowBitmapInfo.bmHeight / EACH_HEIGHT;

	//如果选择的图片宽度超过默认限制，则更新m_rcMap与m_rcBigBitmap边界
	int tempX = m_rcBigBitmap.left + m_nowBitmapInfo.bmWidth;
	m_rcMap.left = m_rcBigBitmap.right = max(tempX, m_rcMap.left);
	//高度
	int tempY = m_rcBigBitmap.top + m_nowBitmapInfo.bmHeight;
	m_rcBigBitmap.bottom = max(m_rcBigBitmap.bottom, tempY);


	this->Invalidate();
	m_bIsSelected = FALSE;
	m_iSourceX = m_iSourceY = -1;
}
BOOL CMapEditorDlg::SaveMap()
{

	CDBHelper dbHelper;
	dbHelper.InitDBHelper();
	if(!dbHelper.SaveMap(m_csMapName,m_etRow,m_etCol,m_map))
		return FALSE;
	dbHelper.CoInitDBHelper();
	return TRUE;
}
BOOL CMapEditorDlg::LoadMap()
{
	m_iXOffset = m_iYOffset = 0;
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();
	m_map = dbHelper.LoadMap(m_csMapName, m_etRow, m_etCol);
	if (m_map == NULL)
	{
		dbHelper.CoInitDBHelper();
		return FALSE;
	}
	dbHelper.CoInitDBHelper();
	return TRUE;
}
void CMapEditorDlg::LoadMap(CString mapName)
{
	m_csMapName = mapName;
	if (FALSE == LoadMap())
	{
		//MessageBox(L"FALSE");
		return;
	}
	UpdateData(FALSE);
	DrawMap(m_etRow, m_etCol, m_map);
	this->Invalidate();
}
void CMapEditorDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	m_etRow = m_etCol = 1;
	if (UpdateData(TRUE) == FALSE)
	{
		MessageBox(L"UpdataData失败");
		return;
	}
	if (FALSE == LoadMap())
	{
		//MessageBox(L"FALSE");
		return;
	}
	UpdateData(FALSE);
	DrawMap(m_etRow, m_etCol, m_map);
	this->Invalidate();
	
}
void CMapEditorDlg::DrawMap(int m_etRow, int m_etCol, int* map)
{
	if (m_updatedMap != NULL)
		DeleteObject(m_updatedMap);
	m_updatedMap = CreateCompatibleBitmap(::GetDC(this->m_hWnd), m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT);

	m_rcMap.right = m_rcMap.left + m_etCol*EACH_WIDTH;
	m_rcMap.bottom = m_rcMap.top + m_etRow*EACH_HEIGHT;

	CDC* clientdc = GetDC();
	CDC memdc, 
		bufferdc;
	memdc.CreateCompatibleDC(clientdc);
	bufferdc.CreateCompatibleDC(clientdc);

	HBITMAP oldBitmap = (HBITMAP)memdc.SelectObject(m_updatedMap);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
	memdc.SelectObject(pen);
	//画横线
	for (int i = 0; i <= m_etRow; ++i)
	{
		memdc.MoveTo(0, i*EACH_HEIGHT);
		memdc.LineTo(m_etCol*EACH_WIDTH, i*EACH_HEIGHT);
	}
	//画竖线
	for (int i = 0; i <= m_etCol; ++i)
	{
		memdc.MoveTo(i*EACH_WIDTH, 0);
		memdc.LineTo(i*EACH_WIDTH, m_etRow*EACH_HEIGHT);
	}

	//贴图
	for (int i = 0; i < m_etRow*m_etCol; ++i)
	{
		
		if (MAP_BLACK == map[i])
			continue;
		HBITMAP tempBitmap = GetResourceMap(map[i]);
		bufferdc.SelectObject(tempBitmap);
		BITMAP bitmapInfo;
		GetObject(tempBitmap, sizeof(BITMAP), &bitmapInfo);
		int start = (map[i] / MAP_DIVISION)*MAP_DIVISION,
			bitmapX = bitmapInfo.bmWidth / EACH_WIDTH,
			sourceX = (map[i]-start) % bitmapX,
			sourceY = (map[i]-start) / bitmapX,
			desX = i%m_etCol,
			desY = i / m_etCol;
		
		memdc.BitBlt(desX*EACH_WIDTH,desY*EACH_HEIGHT, EACH_WIDTH, EACH_HEIGHT,
			&bufferdc, sourceX*EACH_WIDTH, sourceY*EACH_HEIGHT, SRCCOPY);
		DeleteObject(tempBitmap);
	}

	//获得画好的位图
	m_updatedMap = (HBITMAP)memdc.SelectObject(oldBitmap);
	this->Invalidate();
}
HBITMAP CMapEditorDlg::GetResourceMap(int num)
{
	//map1
		if (num < MAP2_START){
			return MyLoadBitmap(IDB_MAP1);
		}
		//map2
		else if (num < MAP3_START){
			return MyLoadBitmap(IDB_MAP2);
		}
		//map3
		else{
			return MyLoadBitmap(IDB_MAP3);
		}
}
HBITMAP CMapEditorDlg::MyLoadBitmap(int num)
{
	return LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(num));
}
void CMapEditorDlg::On32771()
{
	// TODO:  在此添加命令处理程序代码
	CDBSettingDlg dlg;
	dlg.DoModal();
}

BOOL CMapEditorDlg::ExportMapToBinary()
{
	CFile exportFile;
	if (exportFile.Open(FilePathName, CFile::modeRead))
	{
		exportFile.Close();
		MessageBox(L"已存在同名文件，请重新命名");
		return FALSE;
	}
	if (FALSE == exportFile.Open(FilePathName, CFile::modeNoTruncate | CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(L"未知错误");
		return FALSE;
	}
	MapInfo mapInfo;
	mapInfo.m_col = m_etCol;
	mapInfo.m_row = m_etRow;
	lstrcpy(mapInfo.m_mapName, m_csMapName.GetBuffer());
	for (int i = 0; i < m_etRow;++i)
	for (int j = 0; j < m_etCol; ++j)
		mapInfo.m_map[m_etCol*i + j] = m_map[m_etCol*i + j];

	exportFile.Write(&mapInfo, sizeof(mapInfo));
	exportFile.Flush();
	exportFile.Close();
	return TRUE;
}

void CMapEditorDlg::On32773()
{
	// TODO:  在此添加命令处理程序代码
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
	}
	else
	{
		return;
	}
	CFile file;
	MapInfo mapInfo;
	if (file.Open(FilePathName, CFile::modeRead))
	{
		file.Read(&mapInfo, sizeof(mapInfo));
	}
	else{
		MessageBox(L"打开文件失败");
		return;
	}
	m_iXOffset = m_iYOffset = 0;
	m_etRow = mapInfo.m_row;
	m_etCol = mapInfo.m_col;
	if (m_map != NULL)
		delete[] m_map;
	m_map = new int[m_etRow*m_etCol];
	for (int i = 0; i < m_etRow;++i)
	for (int j = 0; j < m_etCol; ++j)
	{
		m_map[i*m_etCol + j] = mapInfo.m_map[i*m_etCol + j];
	}
	m_csMapName = mapInfo.m_mapName;
	UpdateData(FALSE);
	DrawMap(m_etRow,m_etCol,m_map);
	this->Invalidate();
}

int CMapEditorDlg::getImageInfo(int num)
{
	int temp;
	int imageNum = num / 500 - 1;
	switch (imageNum)
	{
	case 0:
		temp = IDB_MAP1;
		break;
	case 1:
		temp = IDB_MAP2;
		break;
	case 2:
		temp = IDB_MAP3;
		break;
	default:
		temp = -1;
		break;
	}
	return temp;
	
}

void CMapEditorDlg::On32774()
{
	if (m_csMapName=="")
	{
		MessageBox(L"地图名不可为空");
		return;
	}
	if (m_etCol <= 0 || m_etRow <= 0 || m_map == NULL)
	{
		MessageBox(L"行和列数值错误，地图不可为空");
		return;
	}

	// TODO:  在此添加命令处理程序代码
	CFileDialog dlg(FALSE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
	}
	else
	{
		return;
	}
	if (TRUE == ExportMapToBinary())
	{
		MessageBox(L"导出成功");
		return;
	}

}


void CMapEditorDlg::On32775()
{
	// TODO:  在此添加命令处理程序代码
	CMapListDlg mapDlg;
	mapDlg.SetMainDlg(this);
	mapDlg.DoModal();

}



void CMapEditorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CMapEditorDlg::SetParentDlg(CDialog* dlg)
{
	m_parentDlg = dlg;
}

BOOL CMapEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	BOOL flag = TRUE;
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			if (--m_iXOffset < 0)
			{
				m_iXOffset = 0;
				flag = FALSE;
			}
			break;
		case VK_RIGHT:
			if (++m_iXOffset >= m_etCol)
			{
				m_iXOffset = m_etCol - 1;
				flag = FALSE;
			}
			break;
		case VK_UP:
			if (--m_iYOffset < 0)
			{
				m_iYOffset = 0;
				flag = FALSE;
			}
			break;
		case VK_DOWN:
			if (++m_iYOffset >= m_etRow)
			{
				m_iYOffset = m_etRow - 1;
				flag = FALSE;
			}
			break;
		}
		if (flag)
			this->Invalidate();
		/*TCHAR str[256];
		wsprintf(str, L"m_iXOffset=%d,m_iYOffset=%d", m_iXOffset, m_iYOffset);
		MessageBox(str);
		*/
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMapEditorDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT3, m_csMapName);
	if (m_csMapName == L""){
		MessageBox(L"地图名不可为空");
		return;
	}
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();

	if (dbHelper.DeleteMap(m_csMapName)){
		MessageBox(L"删除成功");
	}
	dbHelper.CoInitDBHelper();
}
