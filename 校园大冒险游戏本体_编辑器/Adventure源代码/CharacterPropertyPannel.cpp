#include"CharacterPropertyPannel.h"


void CCharacterPropertyPannel::Init(HWND hwnd, RECT* clientRc,CMainCharacter* mc)
{
	m_hWnd = hwnd;
	CopyRect(&m_rcClient, clientRc);
	m_mc = mc;
	m_iCurShow = 0;

	m_rcArea[0].left = 65;
	m_rcArea[0].top = 40;
	m_rcArea[0].right = m_rcArea[0].left + 300;
	m_rcArea[0].bottom = m_rcArea[0].top + 50;

	for (int i = 1; i <= 8; ++i)
	{
		m_rcArea[i].left = m_rcArea[0].left;
		m_rcArea[i].top = m_rcArea[i - 1].bottom;
		m_rcArea[i].right = m_rcArea[0].right;
		m_rcArea[i].bottom = m_rcArea[i].top + 50;
	}
	if (m_hBitmap != NULL)
		DeleteObject(m_hBitmap);
	m_hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP5));
	m_bg.Init(BG_1);
}

void CCharacterPropertyPannel::Paint(HDC hdc)
{
	//先绘制大背景
	HBRUSH brush = CreateSolidBrush(RGB(88, 88, 88));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	//绘制卷轴背景
	m_bg.Paint(hdc,m_rcClient);

	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
	SetBkMode(hdc, TRANSPARENT);
	TCHAR str[64];
	wsprintf(str, L"名字:  %s", m_mc[m_iCurShow].GetName());
	DrawText(hdc, str, wcslen(str), &m_rcArea[0], DT_VCENTER);

	RECT temprc;
	temprc.left = m_rcArea[0].left + (m_rcArea[0].right - m_rcArea[0].left) / 2;
	temprc.top = m_rcArea[0].top;
	temprc.right = m_rcArea[0].right;
	m_rcArea[0].bottom = m_rcArea[0].bottom;
	wsprintf(str, L"职业:  %s", m_mc[m_iCurShow].GetCareer());
	DrawText(hdc, str, wcslen(str), &temprc, DT_VCENTER|DT_LEFT);

	wsprintf(str, L"当前等级 %d 级   经验值  %d  /  %d  ", m_mc[m_iCurShow].GetLevel(), m_mc[m_iCurShow].GetExp(), m_mc[m_iCurShow].GetLevelUpExp());
	DrawText(hdc, str, wcslen(str), &m_rcArea[1], DT_VCENTER);

	wsprintf(str, L"HP: %d  /  %d    MP: %d  /  %d", m_mc[m_iCurShow].GetNowHP(), m_mc[m_iCurShow].GetHP(), m_mc[m_iCurShow].GetNowMP(), m_mc[m_iCurShow].GetMP());
	DrawText(hdc, str, wcslen(str), &m_rcArea[2], DT_VCENTER);

	wsprintf(str, L"体育: %d     智育: %d     德育: %d     ", m_mc[m_iCurShow].GetTiyu(), m_mc[m_iCurShow].GetZhiyu(), m_mc[m_iCurShow].GetDeyu());
	DrawText(hdc, str, wcslen(str), &m_rcArea[3], DT_VCENTER);

	wsprintf(str, L"物理攻击:%d     物理防御: %d      ", m_mc[m_iCurShow].GetPhysicalAttack(), m_mc[m_iCurShow].GetPhysicalDefense());
	DrawText(hdc, str, wcslen(str), &m_rcArea[4], DT_VCENTER);

	wsprintf(str, L"魔法攻击:%d     魔法防御: %d      ", m_mc[m_iCurShow].GetMagicAttack(), m_mc[m_iCurShow].GetMagicDefense());
	DrawText(hdc, str, wcslen(str), &m_rcArea[5], DT_VCENTER);

	wsprintf(str, L"闪避: %d %%     暴击: %d %%      ", m_mc[m_iCurShow].GetEvdChance(), m_mc[m_iCurShow].GetCritChance());
	DrawText(hdc, str, wcslen(str), &m_rcArea[6], DT_VCENTER);

	wsprintf(str, L"反应力: %d", m_mc[m_iCurShow].GetActionSpeed());
	DrawText(hdc, str, wcslen(str), &m_rcArea[7], DT_VCENTER);
	//画角色
	CGraphHelper::MyTransparentBlt(hdc, m_hBitmap, m_rcArea[0].right, m_rcArea[0].top, 106, 180);
}

void CCharacterPropertyPannel::Handle()
{
	if (GetAsyncKeyState(VK_ESCAPE)<0)
	{
		Exit();
	}

}
void CCharacterPropertyPannel::Exit()
{
	SendMessage(m_hWnd, MSG_TURN_MAIN, WPARAM_KEEP_MUSIC, 0);
}