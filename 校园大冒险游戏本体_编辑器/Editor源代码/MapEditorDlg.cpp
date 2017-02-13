
// MapEditorDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "afxdialogex.h"
#include "MapEditorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapEditorDlg �Ի���



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


// CMapEditorDlg ��Ϣ�������

BOOL CMapEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	if (FALSE == GetGlobalArg())
	{
		MessageBox(L"������ݿ�����ʧ�ܣ��޷��������ݿ����");
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
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
BOOL  CMapEditorDlg::GetGlobalArg()
{
	return CDBSettingDlg::GetGlobalArg();
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMapEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		CDC* clientDC = GetDC();

		CDC memdc;
		memdc.CreateCompatibleDC(clientDC);
		HBITMAP oldBitmap=(HBITMAP)memdc.SelectObject(m_nowBitmap);
		//����m_rcBigBitmap����
		clientDC->BitBlt(m_rcBigBitmap.left, m_rcBigBitmap.top, m_nowBitmapInfo.bmWidth, m_nowBitmapInfo.bmHeight, &memdc, 0, 0, SRCCOPY);
		
		if (m_iSourceX != -1){
				//������ɫС����
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
		//����m_rcSmallBitmap����
		//��Сλͼ������ѡ��λͼ

		memdc.SelectObject(m_nowBitmap);

		clientDC->BitBlt(m_rcSmallBitmap.left, m_rcSmallBitmap.top, EACH_WIDTH, EACH_HEIGHT, &memdc,
		m_iSourceX*EACH_WIDTH, m_iSourceY*EACH_HEIGHT, SRCCOPY);

		//���Ʒָ���
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

		//����m_rcMap����
		if (m_etCol > 0 && m_etRow > 0)
		{
			memdc.SelectObject(m_updatedMap);
			int remainX = (m_etCol - m_iXOffset)*EACH_WIDTH,
				remainY = (m_etRow - m_iYOffset)*EACH_HEIGHT;
			int clientX = (m_rcMap.right - m_rcMap.left)/EACH_WIDTH*EACH_WIDTH,
				clientY = m_rcMap.bottom - m_rcMap.top/EACH_HEIGHT*EACH_HEIGHT;//ȡ��
			int tempX = remainX < clientX ? remainX : clientX,
				tempY = remainY < clientY ? remainY : clientY;

			clientDC->BitBlt(m_rcMap.left, m_rcMap.top, tempX, tempY,
				&memdc, m_iXOffset*EACH_WIDTH, m_iYOffset*EACH_HEIGHT, SRCCOPY);
		}
		
		memdc.SelectObject(oldBitmap);
		memdc.DeleteDC();

	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMapEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMapEditorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC* cdc = GetDC();

	if (m_rcBigBitmap.PtInRect(point)){
		
		//����ڵ�ǰλͼ����
		if (point.x >= m_rcBigBitmap.left&&point.y >= m_rcBigBitmap.top&&
			point.x <= m_rcBigBitmap.left + m_nowBitmapInfo.bmWidth&&
			point.y <= m_rcBigBitmap.top + m_nowBitmapInfo.bmHeight)
		{
			//��ѡ�б�־��ΪTRUE
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

			//�������м�¼��x,y��ֵ�ü���ƫ����
			m_map[(m_iDestX+m_iXOffset) + (m_iDestY+m_iYOffset)*m_etCol] = m_iMapIDStart + m_iSourceX + m_iSourceY*m_iSourceCol;

			CDC memdc, bufferdc;
			memdc.CreateCompatibleDC(cdc);
			bufferdc.CreateCompatibleDC(cdc);
			HBITMAP hBitmap = CreateCompatibleBitmap(::GetDC(this->m_hWnd), m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT);
			HBITMAP oldBitmap = (HBITMAP)bufferdc.SelectObject(hBitmap);
			//�Ƚ�ԭͼ����
			memdc.SelectObject(m_updatedMap);
			bufferdc.BitBlt(0, 0, m_etCol*EACH_WIDTH, m_etRow*EACH_HEIGHT, &memdc, 0, 0, SRCCOPY);
			//�ڻ���λͼ�м���ƫ������λ������ͼƬ
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

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
	//������
	for (int i = 0; i <= m_etRow;++i)
	{
		memdc.MoveTo(0, i*EACH_HEIGHT);
		memdc.LineTo(m_etCol*EACH_WIDTH, i*EACH_HEIGHT);
	}
	//������
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
	//ƫ��������
	m_iXOffset = m_iYOffset = 0;
	//����ɾ��m_updatedMap������ᵼ��λͼ��ʧ
	//DeleteObject(m_updatedMap);
	m_updatedMap = (HBITMAP)memdc.SelectObject(oldBitmap);
	this->Invalidate();
}

//�����ͼ��ť
void CMapEditorDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_csMapName == L"")
	{
		MessageBox(L"��ͼ������Ϊ��", L"Error", MB_OK);
		return;
	}
	if (m_etRow <= 0 || m_etCol <= 0)
	{
		MessageBox(L"�л�����Ҫ����0");
		return;
	}
	if (FALSE == SaveMap())
	{
		return;
	}
	MessageBox(L"�����ͼ�ɹ�");
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

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
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
		MessageBox(L"λͼ�ļ�����ʧ��");
		return;
	}
	ZeroMemory(&m_nowBitmapInfo, sizeof(m_nowBitmapInfo));
	m_nowBitmap.GetBitmap(&m_nowBitmapInfo);

	m_iSourceCol = m_nowBitmapInfo.bmWidth / EACH_WIDTH;
	m_iSourceRow = m_nowBitmapInfo.bmHeight / EACH_HEIGHT;

	//���ѡ���ͼƬ��ȳ���Ĭ�����ƣ������m_rcMap��m_rcBigBitmap�߽�
	int tempX = m_rcBigBitmap.left + m_nowBitmapInfo.bmWidth;
	m_rcMap.left = m_rcBigBitmap.right = max(tempX, m_rcMap.left);
	//�߶�
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_etRow = m_etCol = 1;
	if (UpdateData(TRUE) == FALSE)
	{
		MessageBox(L"UpdataDataʧ��");
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
	//������
	for (int i = 0; i <= m_etRow; ++i)
	{
		memdc.MoveTo(0, i*EACH_HEIGHT);
		memdc.LineTo(m_etCol*EACH_WIDTH, i*EACH_HEIGHT);
	}
	//������
	for (int i = 0; i <= m_etCol; ++i)
	{
		memdc.MoveTo(i*EACH_WIDTH, 0);
		memdc.LineTo(i*EACH_WIDTH, m_etRow*EACH_HEIGHT);
	}

	//��ͼ
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

	//��û��õ�λͼ
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
	// TODO:  �ڴ���������������
	CDBSettingDlg dlg;
	dlg.DoModal();
}

BOOL CMapEditorDlg::ExportMapToBinary()
{
	CFile exportFile;
	if (exportFile.Open(FilePathName, CFile::modeRead))
	{
		exportFile.Close();
		MessageBox(L"�Ѵ���ͬ���ļ�������������");
		return FALSE;
	}
	if (FALSE == exportFile.Open(FilePathName, CFile::modeNoTruncate | CFile::modeCreate|CFile::modeWrite))
	{
		MessageBox(L"δ֪����");
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
	// TODO:  �ڴ���������������
	CFileDialog dlg(TRUE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //�ļ�����������FilePathName��
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
		MessageBox(L"���ļ�ʧ��");
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
		MessageBox(L"��ͼ������Ϊ��");
		return;
	}
	if (m_etCol <= 0 || m_etRow <= 0 || m_map == NULL)
	{
		MessageBox(L"�к�����ֵ���󣬵�ͼ����Ϊ��");
		return;
	}

	// TODO:  �ڴ���������������
	CFileDialog dlg(FALSE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //�ļ�����������FilePathName��
	}
	else
	{
		return;
	}
	if (TRUE == ExportMapToBinary())
	{
		MessageBox(L"�����ɹ�");
		return;
	}

}


void CMapEditorDlg::On32775()
{
	// TODO:  �ڴ���������������
	CMapListDlg mapDlg;
	mapDlg.SetMainDlg(this);
	mapDlg.DoModal();

}



void CMapEditorDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CMapEditorDlg::SetParentDlg(CDialog* dlg)
{
	m_parentDlg = dlg;
}

BOOL CMapEditorDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT3, m_csMapName);
	if (m_csMapName == L""){
		MessageBox(L"��ͼ������Ϊ��");
		return;
	}
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();

	if (dbHelper.DeleteMap(m_csMapName)){
		MessageBox(L"ɾ���ɹ�");
	}
	dbHelper.CoInitDBHelper();
}
