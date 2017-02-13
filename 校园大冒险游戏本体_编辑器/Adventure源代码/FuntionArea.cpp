#include"FunctionArea.h"


void CFunctionArea::Init(HWND hwnd, RECT clientRc, CMainCharacter* character)
{
	m_hWnd = hwnd;
	CopyRect(&m_rcClient, &clientRc);
	
	m_character = character;
	//功能数目
	m_iFunctionCount = 3;
	m_iCurSelect = 0;
	//属性
	wsprintf(m_csFunction[0], L"属性(I)");
	wsprintf(m_csFunction[1], L"物品");
	wsprintf(m_csFunction[2], L"退出游戏");
	m_rcFunction[0].left = AREA_SPACE;
	m_rcFunction[0].top = clientRc.top + AREA_SPACE;
	m_rcFunction[0].bottom = m_rcFunction[0].top + AREA_SPACE;
	m_rcFunction[0].right = m_rcFunction[0].left + 140;
	for (int i = 1; i < m_iFunctionCount; ++i)
	{
		m_rcFunction[i].left = m_rcFunction[i-1].left;
		m_rcFunction[i].top = m_rcFunction[i - 1].top + AREA_SPACE;
		m_rcFunction[i].right = m_rcFunction[i - 1].right;
		m_rcFunction[i].bottom = m_rcFunction[i - 1].bottom + AREA_SPACE;
	}

	m_colorSelect = RGB(255, 255, 255);
	m_colorNoSelect = RGB(0, 0, 0);
}

void CFunctionArea::Paint(HDC hdc)
{
	//绘制矩形区域
	HBRUSH brush = CreateSolidBrush(RGB(125, 125, 125));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
	Rectangle(hdc, m_rcFunction[0].left, m_rcFunction[0].top, m_rcFunction[0].right, m_rcFunction[0].top+m_iFunctionCount*AREA_SPACE);
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);

	for (int i = 0; i < m_iFunctionCount; ++i)
	{

		SetBkMode(hdc, TRANSPARENT);
		COLORREF oldColor;
		if(m_iCurSelect==i)
			oldColor=SetTextColor(hdc, m_colorSelect);
		else
			oldColor = SetTextColor(hdc, m_colorNoSelect);
		//绘制属性区域
		DrawText(hdc, m_csFunction[i], wcslen(m_csFunction[i]), &m_rcFunction[i], DT_CENTER | DT_VCENTER);
		//绘制分割线
		//SetTextColor(hdc, RGB(0, 0, 0));
		//MoveToEx(hdc, m_rcFunction[i].left, m_rcFunction[i].top,NULL);
		//LineTo(hdc, m_rcFunction[i].right, m_rcFunction[i].top);
		SetTextColor(hdc, oldColor);
	}

	
}

void CFunctionArea::Handle()
{
	if (GetAsyncKeyState(VK_UP) < 0){
		if (--m_iCurSelect < 0)
			m_iCurSelect = m_iFunctionCount - 1;
	}
	else if (GetAsyncKeyState(VK_DOWN)<0)
	{
		m_iCurSelect = (m_iCurSelect + 1) % m_iFunctionCount;
	}
	else if (GetAsyncKeyState(VK_SPACE) < 0){
		switch (m_iCurSelect)
		{
		case 0:
			SendMessage(m_hWnd, MSG_TURN_PROPERTY_PANNEL, WPARAM(m_character), 0);
			break;
		case 1:
			SendMessage(m_hWnd, MSG_TURN_OBJ_PANNEL, 0, 0);
			break;
		case 2:
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);
			break;
		}
		
	}
}