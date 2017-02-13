#include"MainScene.h"





void CMainScene::Init(HWND hwnd, RECT clientRc,CMainCharacter* mc,int mcCount)
{
	m_hWnd = hwnd;
	
	CopyRect(&m_rcClient, &clientRc);
	//srand((unsigned)time(NULL));
	m_iShowRowCount = WINHEIGHT / EACH_HEIGHT;
	m_iShowColCount = WINWIDTH / EACH_WIDTH;
	m_ptCharacter.x = m_ptCharacter.y = 9;
	//功能区面板是否隐藏
	m_bIsFunctionHidden = TRUE;
	//地图偏移量
	m_idx = m_idy = 0;
	//读取地图
	m_iNowMapNum = MAP_C12;
	m_bIsMon = NULL;
	LoadMap();
	LoadMonster(m_iRowCount*m_iColCount);
	
	//获取角色信息
	m_iMCCount = mcCount;
	m_character = mc;
	m_character[0].SetPos(m_ptCharacter.x, m_ptCharacter.y);

	m_functionArea.Init(hwnd, clientRc,m_character);
}
void CMainScene::Paint(HDC hdc)
{
	if (m_iRowCount > 0 && m_iColCount > 0){
					int center_col = m_iShowColCount / 2 - 1, center_row = m_iShowRowCount / 2 - 1;
					//绘制地图
					//四周需多绘制一圈，行走过程中才不会出现黑边
					int left_remain = min(m_ptCharacter.x + 1, m_iShowColCount / 2+1),
						right_remain = min(m_iColCount - m_ptCharacter.x - 1, m_iShowColCount / 2+1),
						top_remain = min(m_ptCharacter.y + 1, m_iShowRowCount / 2+1),
						bottom_remain = min(m_iRowCount - m_ptCharacter.y - 1, m_iShowRowCount / 2+1);
					
					//暂
					//绘制地图上怪物
					HBITMAP tempBmp = (HBITMAP)LoadImage(NULL, L"./pic/monster.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
					HDC memdc = CreateCompatibleDC(hdc);
					SelectObject(memdc, tempBmp);
					BITMAP bitmap;
					GetObject(tempBmp, sizeof(BITMAP), &bitmap);

					//将地图拆成四部分绘制,实现移动时人物始终在屏幕中央效果
					/*
					左上
					*/
					int mapNum;
					for (int i = 0; i < left_remain; ++i)
					for (int j = 0; j < top_remain; ++j)
					{
						mapNum = (m_ptCharacter.y - j)*m_iColCount + m_ptCharacter.x - i;
						SwitchDraw(hdc, (center_col - i)*EACH_WIDTH+m_idx, (center_row - j)*EACH_HEIGHT+m_idy, EACH_WIDTH, EACH_HEIGHT,
							map[mapNum]);
						if (m_bIsMon[mapNum])
						{
							TransparentBlt(hdc, (center_col - i)*EACH_WIDTH + m_idx, (center_row - j)*EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
								memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 0));
						}
					}
					//右上

					for (int i = 0; i < right_remain; ++i)
					for (int j = 0; j < top_remain; ++j)
					{
						mapNum = (m_ptCharacter.y - j)*m_iColCount + m_ptCharacter.x + i + 1;
						SwitchDraw(hdc, (center_col + 1 + i)*EACH_WIDTH + m_idx, (center_row - j)*EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
							map[mapNum]);
						if (m_bIsMon[mapNum])
						{
							TransparentBlt(hdc, (center_col + 1 + i)*EACH_WIDTH + m_idx, (center_row - j)*EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
								memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 0));
						}
					}
					//左下
					for (int i = 0; i < left_remain; ++i)
					for (int j = 0; j < bottom_remain; ++j)
					{
						mapNum = (m_ptCharacter.y + 1 + j)*m_iColCount + m_ptCharacter.x - i;
						SwitchDraw(hdc, (center_col - i)*EACH_WIDTH + m_idx, (center_row + 1 + j) * EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
							map[mapNum]);
						if (m_bIsMon[mapNum])
						{
							TransparentBlt(hdc, (center_col - i)*EACH_WIDTH + m_idx, (center_row + 1 + j) * EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
								memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 0));
						}
					}
					//右下
					for (int i = 0; i < right_remain; ++i)
					for (int j = 0; j < bottom_remain; ++j)
					{
						mapNum = (m_ptCharacter.y + 1 + j)*m_iColCount + m_ptCharacter.x + i + 1;
						SwitchDraw(hdc, (center_col + i + 1)*EACH_WIDTH + m_idx, (center_row + 1 + j)*EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
							map[mapNum]);
						if (m_bIsMon[mapNum])
						{
							TransparentBlt(hdc, (center_col + i + 1)*EACH_WIDTH + m_idx, (center_row + 1 + j)*EACH_HEIGHT + m_idy, EACH_WIDTH, EACH_HEIGHT,
								memdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, RGB(0, 0, 0));
						}
					}
					
					//绘制功能区
					if (!m_bIsFunctionHidden)
						m_functionArea.Paint(hdc);
					//绘制人物
					m_character[0].Paint(hdc, center_col*EACH_WIDTH, center_row*EACH_HEIGHT);
					DeleteObject(memdc);
	}
}
void CMainScene::Handle()
{
	int tempx, tempy;
	if (m_bIsFunctionHidden)
	{
		if (GetAsyncKeyState(VK_UP) < 0)//上移
		{
			m_character[0].ChangeDir(DIR_UP);
			tempx = m_ptCharacter.x;
			tempy = m_ptCharacter.y - 1;
			if (CanWalk(tempx, tempy, map[tempy*m_iColCount + tempx]))
			{
				//如果此处存在怪物
				if (ExistMon(tempx, tempy)){
					m_iMonXPos = tempx;
					m_iMonYPos = tempy;
					Fight();
				}
				else{
					--m_ptCharacter.y;
					m_idy = -EACH_HEIGHT;
				}
			}
		}
		else if (GetAsyncKeyState(VK_DOWN) < 0)//下移
		{
			m_character[0].ChangeDir(DIR_DOWN);
			tempx = m_ptCharacter.x;
			tempy = m_ptCharacter.y + 1;
			if (CanWalk(tempx, tempy, map[tempy*m_iColCount + tempx]))
			{
				//如果此处存在怪物
				if (ExistMon(tempx, tempy)){
					m_iMonXPos = tempx;
					m_iMonYPos = tempy;
					Fight();
				}
				else{
					++m_ptCharacter.y;
					m_idy = EACH_HEIGHT;
				}
			}
		}
		else if (GetAsyncKeyState(VK_LEFT) < 0)//左移
		{
			m_character[0].ChangeDir(DIR_LEFT);
			tempx = m_ptCharacter.x - 1;
			tempy = m_ptCharacter.y;

			if (CanWalk(tempx, tempy, map[tempy*m_iColCount + tempx]))
			{
				//如果此处存在怪物
				if (ExistMon(tempx, tempy)){
					m_iMonXPos = tempx;
					m_iMonYPos = tempy;
					Fight();
				}
				else{
					--m_ptCharacter.x;
					m_idx = -EACH_WIDTH;
				}
			}
		}
		else if (GetAsyncKeyState(VK_RIGHT) < 0)//右移
		{
			m_character[0].ChangeDir(DIR_RIGHT);
			tempx = m_ptCharacter.x + 1;
			tempy = m_ptCharacter.y;

			if (CanWalk(tempx, tempy, map[tempy*m_iColCount + tempx]))
			{
				//如果此处存在怪物
				if (ExistMon(tempx, tempy)){
					m_iMonXPos = tempx;
					m_iMonYPos = tempy;
					Fight();
				}
				else{
					++m_ptCharacter.x;
					m_idx = EACH_WIDTH;
				}
			}
		}
		else if (GetAsyncKeyState('i') < 0 || GetAsyncKeyState('I')){
			SendMessage(m_hWnd, MSG_TURN_PROPERTY_PANNEL, DWORD(m_character), 0);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			m_bIsFunctionHidden = !m_bIsFunctionHidden;
		}

		//人物位置可能改变，需要更新
		m_character[0].SetPos(m_ptCharacter.x, m_ptCharacter.y);
	}
	else{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			m_bIsFunctionHidden = !m_bIsFunctionHidden;
		}
		else 
			m_functionArea.Handle();
	}
}
void CMainScene::Fight()
{
	SendMessage(m_hWnd, MSG_FIGHT, m_iNowMapNum, 0);
}
void CMainScene::WinFight()
{
	m_bIsMon[m_iMonYPos*m_iColCount + m_iMonXPos] = FALSE;
}
void CMainScene::SwitchDraw(HDC destHdc, int x1, int y1, int cx, int cy, int type)
{
	int image_num=1,
		map_start = type / MAP_DIVISION * MAP_DIVISION;//获得基准值，MAP_DIVISION的整数倍
	TCHAR str[128];
	switch (type / MAP_DIVISION)
	{
	case 1:
		image_num = IDB_BITMAP6;
		break;
	case 2:
		image_num = IDB_BITMAP7;
		break;
	case 3:
		image_num =IDB_BITMAP2;
		break;
	default:
		wsprintf(str, L"type=%d", type);
		MessageBox(m_hWnd, str, L"error", MB_OK);
	}
	HBITMAP temp_bitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(image_num));
	if (temp_bitmap == NULL)
	{
		MessageBox(m_hWnd,L"SwitchDraw():bitmap load fail",L"error",MB_OK);
		return;
	}
	BITMAP bitmap;
	GetObject(temp_bitmap, sizeof(bitmap), &bitmap);
	//获取素材图片的列数
	int temp_col = bitmap.bmWidth / EACH_WIDTH,
		real_num = type - map_start;//获得在图片中的编号
	BufferBitBltDraw(destHdc, x1, y1, cx, cy, temp_bitmap, real_num%temp_col*EACH_WIDTH, real_num / temp_col * EACH_HEIGHT);
	DeleteObject(temp_bitmap);
}

void CMainScene::Clear()
{
	if (map != NULL)
		delete[] map;
	//删除位图
}
BOOL CMainScene::CanWalk(int x, int y,int type)
{
	if (x >= 0 && y >= 0 && x < m_iColCount&&y < m_iRowCount&&
		(type==1503//表示MAP3  3,0
		||type==1516))//MAP3 0,2
		return TRUE;
	return FALSE;
}
BOOL CMainScene::ExistMon(int x,int y)
{
	if (m_bIsMon[x + y*m_iColCount])
		return TRUE;
	return FALSE;
}

void CMainScene::BufferBitBltDraw(HDC destHdc, int x1, int y1, int cx, int cy, HBITMAP sourceBitmap, int x2, int y2)
{
	HDC memHdc = CreateCompatibleDC(destHdc);
	SelectObject(memHdc, sourceBitmap);
	BitBlt(destHdc, x1, y1, cx, cy, memHdc, x2, y2, SRCCOPY);

	DeleteObject(memHdc);
}
void CMainScene::LoadMap()
{
	std::ifstream ifs;
	char mapfile_name[128];
	MapInfo mapInfo;
	switch (m_iNowMapNum)
	{
	case MAP_C12:
		sprintf(mapfile_name, "%s%s", PATH_MAPS, MAPNAME_C12);
		break;
	default:
		mapInfo.m_col = 20;
		mapInfo.m_row = 20;

		for (int i = 0; i < mapInfo.m_col; ++i)
		for (int j = 0; j < mapInfo.m_row; ++j)
		{
			if (rand() % 2 == 0){
				mapInfo.m_map[i*m_iColCount + j] = 1;
			}
			else {
				mapInfo.m_map[i*m_iColCount + j] = MAP_TEST_ROAD;
			}
		}
	}
	ifs.open(mapfile_name, ios::binary);
	ifs.seekg(0, ios::beg);
	ifs.read((char*)&mapInfo, sizeof(MapInfo));
	ifs.close();

	
	map = mapInfo.m_map;
	m_iColCount = mapInfo.m_col;
	m_iRowCount = mapInfo.m_row;
}
void CMainScene::Update()
{
	if (m_idx > 0)
	{
		m_idx -=8;
	}
	else if (m_idx < 0)
	{
		m_idx += 8;
	}

	if (m_idy>0)
	{
		m_idy -= 8;
	}
	else if (m_idy < 0)
	{
		m_idy += 8;
	}

	m_character[0].Update();
}

void CMainScene::LoadMonster(int size)
{
	if (m_bIsMon)
		delete[] m_bIsMon;
	m_bIsMon = new BOOL[size];
	for (int i = 0; i < size; ++i)
	{
		m_bIsMon[i] = FALSE;
	}
	for (int i = 0; i < 10; ++i)
	{
		int temp;
		do{
			temp = rand() % size;
		} while ((map[temp] != ROAD_1&&map[temp] != ROAD_2)||m_bIsMon[temp]==TRUE);
		m_bIsMon[temp] = TRUE;
	}
}