#include"MenuScene.h"

void CMenuScene::Init(HWND hwnd, RECT& rect)
{
	CopyRect(&m_rcClient, &rect);
	this->hwnd = hwnd;
	m_maxRow = 3;
	m_choseRow = 0;
	lstrcpy(text[0], L"新的冒险");
	lstrcpy(text[1], L"继续冒险");
	lstrcpy(text[2], L"离开冒险");
	m_bg.Init(BG_MENU);
	//文本位置
	text_rect[0].left = 0;
	text_rect[0].top = WINHEIGHT/2+20;
	text_rect[0].right = WINWIDTH;
	text_rect[0].bottom = text_rect[0].top+50;
	CopyRect(&text_rect[1], &text_rect[0]);
	CopyRect(&text_rect[2], &text_rect[0]);
	text_rect[1].top = text_rect[0].bottom;
	text_rect[1].bottom = text_rect[1].top + 50;
	text_rect[2].top = text_rect[1].bottom;
	text_rect[2].bottom = text_rect[2].top + 50;

	color_selected = RGB(200,0,0);
	color_normal = RGB(255, 255, 255);
}

void CMenuScene::Paint(HDC hdc)
{
	m_bg.Paint(hdc, m_rcClient);
	SetBkMode(hdc, TRANSPARENT);
	for (int i = 0; i < m_maxRow; ++i)
	{
		if (i == m_choseRow)
		{
			SetTextColor(hdc, color_selected);
			DrawText(hdc, text[i], wcslen(text[i]), &text_rect[i], DT_CENTER);
		}
		else{
			SetTextColor(hdc, color_normal);
			DrawText(hdc, text[i], wcslen(text[i]), &text_rect[i], DT_CENTER);
		}
	}
}

void CMenuScene::Handle()
{
	
	if (GetAsyncKeyState(VK_UP) < 0)//按下上箭头
	{
		m_choseRow = max(m_choseRow - 1, 0);
	}
	else if (GetAsyncKeyState(VK_DOWN) < 0)//按下 下箭头
	{
		m_choseRow = min(m_choseRow + 1, m_maxRow-1);
	}
	else if (GetAsyncKeyState(VK_RETURN) < 0)//按下回车
	{
		if (m_choseRow == 0){
			SendMessage(hwnd, MSG_NEW_GAME, 0, 0);
		}
		else if (m_choseRow == 1){

		}
		else{
			PostQuitMessage(0);
		}
	}
}