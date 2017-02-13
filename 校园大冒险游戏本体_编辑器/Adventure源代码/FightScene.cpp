#include"FightScene.h"

void CFightScene::Init(HWND hwnd,RECT* rc, int mapNum,CMainCharacter* mc)
{

	m_iFrame = 0;
	m_iMapNum = mapNum;
	m_hWnd = hwnd;
	m_fsState = FS_LOADING;

	CopyRect(&m_rcClient,rc);
	m_mc = mc;
	m_iMcCount = 1;

	srand((unsigned)time(NULL));

	//FS_FIGHT�ĳ�ʼ��
	m_bIsCmd = TRUE;
	m_iCurCmd = 0;
	
	m_bg.Init(BG_0);
	//���ɹ���
	randMon(mapNum);
	//��ʼ������˳��
	m_iCurActionNum=0;
	InitActionTurn();
	//����λ�ó�ʼ��
	m_ptMonPos[0].x = 40;
	m_ptMonPos[0].y = 10;
	for (int i = 1; i < m_iMonCount; ++i)
	{
		m_ptMonPos[i].x = m_ptMonPos[i-1].x;
		m_ptMonPos[i].y = m_ptMonPos[i-1].y + 50;
		if (i == 2)
			m_ptMonPos[i].x -= 30;
	}

	//FS_LOADING�ĳ�ʼ��
	m_iLoadingFrame = GAME_FRAME;
	m_koBg.Init(m_iLoadingFrame, KOBG_0);
	
	//ָ��׶γ�ʼ��
	m_cmdState = CS_CMD;
	m_iSelMon = 0;

	m_rcCmd.top = m_rcClient.bottom - 100;
	m_rcCmd.left = 0;
	m_rcCmd.bottom = m_rcClient.bottom;
	m_rcCmd.right = m_rcClient.right;

	wsprintf(m_csCmd[0], L"����");
	wsprintf(m_csCmd[1], L"����");
	wsprintf(m_csCmd[2], L"����");
	wsprintf(m_csCmd[3], L"����");

	int width = 100;
	int height = 50;
	for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2; ++j)
	{
		int num = i * 2 + j;
		m_rcEachCmd[num].left = j * width;
		m_rcEachCmd[num].right = (j + 1) * width;
		m_rcEachCmd[num].top = m_rcCmd.top + i*height;
		m_rcEachCmd[num].bottom = m_rcEachCmd[num].top + height;
	}
	m_rcMcState[0].left = m_rcEachCmd[1].right;
	m_rcMcState[0].top = m_rcCmd.top + 10;
	m_rcMcState[0].bottom = m_rcCmd.bottom;
	m_rcMcState[0].right = m_rcMcState[0].left + 100;
	//�����׶�
	m_iFrameNum = 0;


	//��ʱ

	money = 0,
		exp = 0;
	for (int i = 0; i < m_iMonCount; ++i){
		money += m_mon[i].GetMoney();
		exp += m_mon[i].GetExp();
	}
}

void CFightScene::Paint(HDC hdc)
{
	switch (m_fsState)
	{
	case FS_LOADING:
		paintLoading(hdc);
		break;
	case FS_OVER:
		paintGameOver(hdc);
		break;
	case FS_FIGHT:
		paintFight(hdc);
		break;
	}
}

void CFightScene::Update()
{
	switch (m_fsState)
	{
	case FS_LOADING:
		upateLoading();
		break;
	case FS_OVER:
		upateGameOver();
		break;
	case FS_FIGHT:
		upateFight();
		break;
	}
}

void CFightScene::Handle()
{
	switch (m_fsState)
	{
	case FS_LOADING:
		break;
	case FS_OVER:
		handleGameOver();
		break;
	case FS_FIGHT:
		handleFight();
		break;
	}
}



void CFightScene::randMon(int mapNum)
{
	m_iMonCount = rand() % maxMonNum + 1;
	int lev;
	switch (mapNum)
	{
	case MAP_C12:
		lev = 1;
		break;
	default:
		lev = 1;
	}

	for (int i = 0; i < m_iMonCount; ++i)
	{
		m_mon[i].Init(L"monster",5*lev,5 * lev, 2 * lev, 1 * lev);
	}
}

//paint����
void CFightScene::paintLoading(HDC hdc)
{
	//��ս���б���
	m_bg.Paint(hdc, m_rcClient);

	//��������Ļ�Ķ�������
	m_koBg.Paint(hdc, m_rcClient);

}
void CFightScene::paintGameOver(HDC hdc)
{
	if (m_mc[0].GetNowHP() > 0){
		HDC memdc = CreateCompatibleDC(hdc);
		HBITMAP bitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), L"./pic/victory.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		HBITMAP oldBitmap = (HBITMAP)SelectObject(memdc, bitmap);
		BITMAP bitmapInfo;
		GetObject(bitmap, sizeof(BITMAP), &bitmapInfo);
		TransparentBlt(hdc, 0, 0, m_rcClient.right-m_rcClient.left,m_rcClient.bottom-m_rcClient.top ,
			memdc, 0, 0,bitmapInfo.bmWidth,bitmapInfo.bmHeight, SRCCOPY);

		SelectObject(memdc, oldBitmap);
		DeleteObject(memdc);

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);

		TCHAR str[64];
		wsprintf(str, L"��þ��� %d", exp);
		RECT tempRc;
		CopyRect(&tempRc, &m_rcClient);
		DrawText(hdc, str, wcslen(str), &tempRc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		tempRc.top -= 30;
		wsprintf(str, L"��ý�Ǯ %d", money);
		DrawText(hdc, str, wcslen(str), &tempRc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}
void CFightScene::paintFight(HDC hdc)
{
	
	SetBkMode(hdc, TRANSPARENT);
	//������
	m_bg.Paint(hdc,m_rcClient);
	//������
	for (int i = 0; i < m_iMonCount; ++i)
	{
		int size = 2;
		if (2 == i)
			size = 3;
		if (FALSE==m_mon[i].GetIsDead())
			m_mon[i].Paint(hdc,m_ptMonPos[i].x,m_ptMonPos[i].y,size);
			
	}
	
	//������
	for (int i = 0; i < m_iMcCount; ++i)
		m_mc[0].PaintFightMC(hdc, m_rcClient.right - 100, m_rcClient.top + 150+i*EACH_HEIGHT);

	if (m_bIsCmd)
	{
		//�������������
		HBRUSH hBrush = CreateSolidBrush(RGB(111, 111, 111));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Rectangle(hdc, m_rcCmd.left, m_rcCmd.top, m_rcCmd.right, m_rcCmd.bottom);
		
		
		//��ָ��
		for (int i = 0; i < 4; ++i)
		{
			if (i == m_iCurCmd){
				SetTextColor(hdc, RGB(255, 255, 255));
			}
			else {
				SetTextColor(hdc, RGB(0, 0, 0));
			}
			DrawText(hdc, m_csCmd[i], wcslen(m_csCmd[i]), &m_rcEachCmd[i], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}

		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);

		//������״̬
		SetTextColor(hdc,RGB(0, 0, 0));
		HPEN pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, pen);
		MoveToEx(hdc, m_rcEachCmd[1].right, m_rcCmd.top, NULL);
		LineTo(hdc, m_rcEachCmd[1].right, m_rcCmd.bottom);
		SelectObject(hdc, oldPen);
		DeleteObject(pen);
		TCHAR tempStr[128];
		wsprintf(tempStr, L"%s\nHP: %d / %d\n\nMP: %d / %d", 
			m_mc[0].GetName(),m_mc[0].GetNowHP(), m_mc[0].GetHP(), m_mc[0].GetNowMP(), m_mc[0].GetMP());
		DrawText(hdc, tempStr, wcslen(tempStr), &m_rcMcState[0], DT_CENTER);

		switch (m_cmdState){
		case CS_SELMON:
		{
						  while (m_mon[m_iSelMon].GetIsDead() == TRUE)
						  {
							  if (++m_iSelMon >= m_iMonCount){
								  m_iSelMon = 0;
							  }
						  }
						  //��ѡ�б�־
						  TCHAR tempStr[16];
						  wsprintf(tempStr, L"X");
						  SetTextColor(hdc, RGB(255, 0, 0));
						  RECT tempRc;
						  tempRc.left = m_ptMonPos[m_iSelMon].x;
						  tempRc.right = tempRc.left + 2 * EACH_WIDTH;
						  tempRc.top = m_ptMonPos[m_iSelMon].y;
						  tempRc.bottom = tempRc.top + 2 * EACH_HEIGHT;
						  if (2 == m_iSelMon){
							  tempRc.right += EACH_WIDTH;
							  tempRc.bottom += EACH_HEIGHT;
						  }
						  DrawText(hdc, tempStr, wcslen(tempStr), &tempRc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		}
			break;
		case CS_CMD:
			break;
		}
	}
	else{

		SetTextColor(hdc, RGB(0, 0, 255));
		//���ֵ�Ϊ����
		if (m_iActionTurn[m_iCurActionNum] < 3){
			//��ʾ���ﶯ��
			if (m_iFrameNum >= 5 && m_iFrameNum <= 25){
				if (m_mc[m_iActionTurn[m_iCurActionNum]].m_actionTypes==CMainCharacter::ActionTypes::AT_SKILL)
					m_skillAnime.Paint(hdc, 190, 140, 200, 180);
			}
		}
		//���ֵ�Ϊ����
		else
		{
			//��ʾboss����
			if (m_iFrameNum >= 5 && m_iFrameNum <= 25){
				/*
				TCHAR str[128];
				if (m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].m_actionTypes == CMonster::AT_ATTACK){
					wsprintf(str, L"%s %d�ŷ��� %s,�ܵ� 1 ���˺�", m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].GetName(),
						(m_iCurActionNum - m_iMcCount), L"����");
					if(m_iFrameNum==25)
						m_mc[0].SetNowHP(m_mc[0].GetNowHP() - 1);
				}
				else{
					wsprintf(str, L"%s %d�ŷ��� %s,�ܵ� 5 ���˺�", m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].GetName(),
						(m_iCurActionNum - m_iMcCount), L"����");
					if (m_iFrameNum == 25)
						m_mc[0].SetNowHP(m_mc[0].GetNowHP() - 5);
				}
				DrawText(hdc, str, wcslen(str), &m_rcClient, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				*/
			}
		}
		
	}
}

//update����
void CFightScene::upateLoading()
{
	m_koBg.Update();

	if (++m_iFrame >= m_iLoadingFrame)
	{
		//MessageBox(m_hWnd, L"Loading Over",L"",MB_OK);
		m_iFrame = 0;
		m_fsState = FS_FIGHT;
	}
}
void  CFightScene::upateGameOver()
{

}
void  CFightScene::upateFight()
{
	//ָ��׶�
	if (m_bIsCmd)
	{

	}//�����׶�
	else
	{
		++m_iFrameNum;
		//��26֡��һ�����ֻغϽ���
		if (m_iFrameNum == 26)
		{
			ClearShow();
			if (IsGameOver()){
				m_fsState = FS_OVER;
			}
			if (++m_iCurActionNum >= m_iMcCount + m_iMonCount){
				m_iCurActionNum = 0;
			}
			m_iFrameNum = 0;
			//�¸�������Ϊ���
			if (m_iActionTurn[m_iCurActionNum] < MAX_MCCOUNT){
				m_bIsCmd = TRUE;
			}
			//�¸�����Ϊ������¹����߼�
			else
			{
				if (FALSE==m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].GetIsDead())
					m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].Update();
			}
		}//�˺������ڵ�16��֡
		else if (m_iFrameNum == 5){
			//������й���
			if (m_iActionTurn[m_iCurActionNum] < MAX_MCCOUNT){
				m_mc[m_iActionTurn[m_iCurActionNum]].Attack(m_iMonCount, m_mon, m_iSelMon);
			}
			//������й���
			else{
				if (FALSE == m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].GetIsDead())
					m_mon[m_iActionTurn[m_iCurActionNum] - MAX_MCCOUNT].Attack(m_mc, m_iMcCount);
			}
		}
	}
}

//handle����
void CFightScene::handleLoading()
{

}
void CFightScene::handleGameOver()
{
	if (m_mc[0].GetNowHP() > 0){
		if (GetAsyncKeyState(VK_SPACE) < 0){
			for (int i = 0; i < m_iMcCount;++i)
				m_mc[i].GetExpAndMoney(exp, money);
			WinFight();
		}
	}
}
void CFightScene::handleFight()
{
	//ָ��׶�
	if (m_bIsCmd)
	{
		switch (m_cmdState)
		{
			//ѡ��ָ��
		case CS_CMD:
			if (GetAsyncKeyState(VK_RIGHT) < 0)
			{
				if (++m_iCurCmd >= 4){
					m_iCurCmd = 0;
				}
			}
			else if (GetAsyncKeyState(VK_LEFT) < 0)
			{
				if (--m_iCurCmd < 0){
					m_iCurCmd = 3;
				}
			}
			else if (GetAsyncKeyState(VK_SPACE) < 0)
			{
				switch (m_iCurCmd){
					//����
				case 0:
					m_mc[m_iActionTurn[m_iCurActionNum]].SetActionTypes(CMainCharacter::AT_NORMAL);
					m_cmdState = CS_SELMON;
					break;
					//����
				case 1:
					m_mc[m_iActionTurn[m_iCurActionNum]].SetActionTypes(CMainCharacter::AT_SKILL);
					m_cmdState = CS_SELMON;
					m_skillAnime.Init(L"����", 8, 20);
					break;
				case 2:
					break;
				case 3:
					Exit();
					break;
				}
			}
			break;
			//ѡ�����
		case CS_SELMON:
			if (GetAsyncKeyState(VK_DOWN) < 0)
			{
				if (++m_iSelMon >= m_iMonCount){
					m_iSelMon = 0;
				}
				while (m_mon[m_iSelMon].GetIsDead() == TRUE)
				{
					if (++m_iSelMon >= m_iMonCount){
						m_iSelMon = 0;
					}
				}
			}
			else if (GetAsyncKeyState(VK_UP) < 0)
			{
				if (--m_iSelMon < 0){
					m_iSelMon = m_iMonCount - 1;
				}
				while (m_mon[m_iSelMon].GetIsDead() == TRUE)
				{
					if (--m_iSelMon < 0){
						m_iSelMon = m_iMonCount - 1;
					}
				}
			}
			else if (GetAsyncKeyState(VK_SPACE) < 0)
			{
				m_bIsCmd = FALSE;
				m_cmdState = CS_CMD;
			}
			else if (GetAsyncKeyState(VK_ESCAPE)<0){
				m_cmdState = CS_CMD;
			}
			break;
		}
	}
}

void CFightScene::Exit()
{
	SendMessage(m_hWnd, MSG_TURN_MAIN, 0, 0);
}

void CFightScene::InitActionTurn()
{
	//˼·���������������ĸ������������ٶȽ��������پ���˳�������鴢�����˳���ţ�value<3λ���value>=3λ�������ǰ�˵��ȳ���
	m_iActionTurn[0] = 0;
	for (int i = 0; i < m_iMonCount; ++i)
		m_iActionTurn[m_iMcCount + i] = MAX_MCCOUNT + i;
}
BOOL CFightScene::IsGameOver(){
	BOOL flag1 = TRUE;
	for (int i = 0; i < m_iMonCount; ++i){
		if (FALSE == m_mon[i].GetIsDead())
			flag1 = FALSE;
	}
	/*
	for (int i = 0; i < m_iMcCount; ++i){
		if (m_mc[i].GetNowHP()<=0)
			flag2 = FALSE;
	}*/
	return flag1;
}
void CFightScene::ClearShow()
{
	for (int i = 0; i < m_iMcCount; ++i)
		m_mc[i].SetShowDamage(FALSE);

	for (int i = 0; i < m_iMonCount; ++i)
		m_mon[i].SetShowDamage(FALSE);
}
void CFightScene::WinFight()
{
	SendMessage(m_hWnd, MSG_WIN_FIGHT, 0, 0);
}