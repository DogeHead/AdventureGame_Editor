#include"ObjectPannel.h"

void CObjectPannel::Init(HWND hwnd, RECT client, CMainCharacter* mc, CObjectManager* objManager)
{
	m_hWnd = hwnd;
	CopyRect(&m_rcClient, &client);
	m_pMc = mc;
	m_iMcCount = 1;
	m_pObjManager = objManager;

	m_rcArea[0].left = m_rcClient.left;
	m_rcArea[0].right = m_rcClient.right / 6;
	m_rcArea[0].top = m_rcClient.top+25;
	m_rcArea[0].bottom = m_rcClient.bottom / 2;

	m_rcArea[1].left = m_rcClient.left;
	m_rcArea[1].right = m_rcClient.right / 6;
	m_rcArea[1].top = m_rcArea[0].bottom;
	m_rcArea[1].bottom = m_rcClient.bottom;

	m_rcArea[2].left = m_rcArea[0].right;
	m_rcArea[2].right = m_rcClient.right / 2;
	m_rcArea[2].top = m_rcArea[0].top;
	m_rcArea[2].bottom = m_rcClient.bottom;
	
	m_rcArea[3].left = m_rcArea[2].right;
	m_rcArea[3].right = m_rcClient.right;
	m_rcArea[3].top = m_rcArea[0].top;
	m_rcArea[3].bottom = m_rcClient.bottom;
	m_bg.Init(BG_ObjectPannel);

	lstrcpy(m_csOption[0], L"药物");
	lstrcpy(m_csOption[1], L"装备");
	lstrcpy(m_csOption[2], L"道具");
	lstrcpy(m_csOption[3], L"装备");
	lstrcpy(m_csOption[4], L"使用");
	//阶段初始化
	m_opState = OP_TYPESEL;
	//类型选择初始化
	m_typeSelState.choice = 0;
	m_typeSelState.maxChoice = 3;
	m_typeSelState.color_nor = RGB(255, 209, 194);
	m_typeSelState.color_sel = RGB(255, 0, 0);
	//物品选择初始化
	m_objSelState.curX = 0;
	m_objSelState.curY = 0;
	m_objSelState.maxCol = 8;
	m_objSelState.maxRow = 10;
	//使用阶段初始化
	m_useState.choice = 0;
	m_useState.maxChoice = 2;
	m_useState.color_nor = RGB(255, 209, 194);
	m_useState.color_sel = RGB(255, 0, 0);
	//作用角色阶段
	m_selMCState.choice = 0;
	m_selMCState.maxChoice = m_iMcCount;
	lstrcpy(m_selMCState.msg, L"");
	m_selMCState.showMsg = FALSE;
}

void CObjectPannel::Paint(HDC hdc)
{
	static HBRUSH hBrush[4];
	hBrush[0] = CreateSolidBrush(RGB(100, 100, 100));
	hBrush[1] = CreateSolidBrush(RGB(150, 150, 150));
	hBrush[2] = CreateSolidBrush(RGB(180, 180, 180));
	hBrush[3] = CreateSolidBrush(RGB(210, 210, 210));
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, pen);
	for (int i = 0; i < 4; ++i)
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush[i]);
		Rectangle(hdc, m_rcArea[i].left, m_rcArea[i].top, m_rcArea[i].right, m_rcArea[i].bottom);
		SelectObject(hdc, oldBrush);
	}
	SelectObject(hdc, oldPen);
	DeleteObject(pen);
	for (int i = 0; i < 4; ++i)
		DeleteObject(hBrush[i]);
	m_bg.Paint(hdc, m_rcClient);

	SetBkMode(hdc, TRANSPARENT);
	int eachHeight = (m_rcClient.bottom - m_rcClient.top) / (2 * m_typeSelState.maxChoice);//间距
	//类型选择
	for (int i = 0; i < m_typeSelState.maxChoice; ++i)
	{
		RECT tempRc;

		CopyRect(&tempRc, &m_rcArea[0]);
		tempRc.top = m_rcArea[0].top + i*eachHeight;
		tempRc.bottom = tempRc.top + eachHeight;
		if (i == m_typeSelState.choice)
			SetTextColor(hdc, m_typeSelState.color_sel);
		else
			SetTextColor(hdc, m_typeSelState.color_nor);
		DrawText(hdc, m_csOption[i], wcslen(m_csOption[i]), &tempRc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
	}
	//使用阶段
	if (m_opState == OP_USE||m_opState==OP_SELMC)
	{
		eachHeight = (m_rcClient.bottom - m_rcClient.top) / (2 * m_useState.maxChoice);
		for (int i = m_typeSelState.maxChoice; i < m_typeSelState.maxChoice + m_useState.maxChoice; ++i)
		{
			RECT tempRc;
			CopyRect(&tempRc, &m_rcArea[1]);
			tempRc.top = m_rcArea[1].top + (i - m_typeSelState.maxChoice) *eachHeight;
			tempRc.bottom = tempRc.top + eachHeight;
			if (i - m_typeSelState.maxChoice == m_useState.choice)
				SetTextColor(hdc, m_useState.color_sel);
			else
				SetTextColor(hdc, m_useState.color_nor);
			DrawText(hdc, m_csOption[i], wcslen(m_csOption[i]), &tempRc, DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}
	}
	//绘制物品栏与物品信息
	PaintObj(hdc);

	//如果处于选人状态，绘制选人界面
	if (m_opState == OP_SELMC)
		PaintMCSel(hdc);

	//显示使用信息
	if (m_selMCState.showMsg){
		SetTextColor(hdc, RGB(255, 0, 0));
		RECT temprc;
		temprc.left = 150;
		temprc.right = 350;
		temprc.top = 150;
		temprc.bottom = 300;
		CGraphHelper::MyRectangle(hdc, temprc);
		temprc.top += 10;
		temprc.left += 10;
		temprc.right -= 10;
		DrawText(hdc, m_selMCState.msg, wcslen(m_selMCState.msg), &temprc, DT_WORDBREAK | DT_CENTER);
	}
}
void CObjectPannel::PaintObj(HDC hdc)
{
	switch (m_typeSelState.choice)
	{
		//药物
	case 0:{
			   vector<CMedicine> vec = m_pObjManager->GetMedicineVec();
			   for (int i = 0; i < vec.size(); ++i)
			   {
				   vec[i].Paint(hdc, m_rcArea[3].left + EACH_WIDTH*(i%m_objSelState.maxCol),
					   m_rcArea[3].top + EACH_HEIGHT*(i/m_objSelState.maxCol),
					   EACH_WIDTH, EACH_HEIGHT);
			   }
	}
		break;
		//装备
	case 1:
	{
			  vector<CEquipment> vec = m_pObjManager->GetEquipmentVec();
			  for (int i = 0; i < vec.size(); ++i)
			  {
				  vec[i].Paint(hdc, m_rcArea[3].left + EACH_WIDTH*(i%m_objSelState.maxCol),
					  m_rcArea[3].top + EACH_HEIGHT*(i / m_objSelState.maxCol),
					  EACH_WIDTH, EACH_HEIGHT);
			  }
	}
		break;
		//道具
	case 2:
	{
			  vector<CTool> vec = m_pObjManager->GetToolVec();
			  for (int i = 0; i < vec.size(); ++i)
			  {
				  vec[i].Paint(hdc, m_rcArea[3].left + EACH_WIDTH*(i%m_objSelState.maxCol),
					  m_rcArea[3].top + EACH_HEIGHT*(i / m_objSelState.maxCol),
					  EACH_WIDTH, EACH_HEIGHT);
			  }
	}
		break;
	}

	//绘制网格
	HPEN pen1 = CreatePen(PS_SOLID, 4, RGB(255, 209, 194));
	HPEN oldPen1 = (HPEN)SelectObject(hdc, pen1);
	//横线
	for (int i = 0; i <= m_objSelState.maxRow; ++i)
	{
		MoveToEx(hdc, m_rcArea[3].left, m_rcArea[3].top + i*EACH_HEIGHT, NULL);
		LineTo(hdc, m_rcArea[3].left + EACH_WIDTH*m_objSelState.maxCol, m_rcArea[3].top + i*EACH_HEIGHT);
	}
	//竖线
	for (int i = 0; i <= m_objSelState.maxCol; ++i)
	{
		MoveToEx(hdc, m_rcArea[3].left + i*EACH_WIDTH, m_rcArea[3].top, NULL);
		LineTo(hdc, m_rcArea[3].left + i*EACH_WIDTH, m_rcArea[3].top + EACH_HEIGHT*m_objSelState.maxRow);
	}
	SelectObject(hdc, oldPen1);
	DeleteObject(pen1);

	//如果物品已选中，绘制选中框
	if (m_opState !=OP_TYPESEL)
	{
		HPEN pen2 = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		HPEN oldPen2 = (HPEN)SelectObject(hdc, pen2);
		int left = m_rcArea[3].left + m_objSelState.curX*EACH_WIDTH,
			top = m_rcArea[3].top + m_objSelState.curY*EACH_HEIGHT;
		for (int i = 0; i < 2; ++i)
		{
			MoveToEx(hdc, left, top + i*EACH_HEIGHT, NULL);
			LineTo(hdc, left + EACH_WIDTH, top + i*EACH_HEIGHT);

			MoveToEx(hdc, left + i*EACH_WIDTH, top, NULL);
			LineTo(hdc, left + i*EACH_WIDTH, top + EACH_HEIGHT);
		}
		SelectObject(hdc, oldPen2);
		DeleteObject(pen2);

		//绘制物品信息
		PaintObjData(hdc);
	}

	
}
void CObjectPannel::PaintObjData(HDC hdc)
{
	SetTextColor(hdc, RGB(255, 209, 194));
	TCHAR str[256];
	CMyObject* pObj;
	switch (m_typeSelState.choice)
		{
		//药物
	case 0:
		pObj = m_pObjManager->GetMedicine(m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol);
		break;
		//装备
	case 1:
		pObj = m_pObjManager->GetEquipment(m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol);
		break;
		//道具
	case 2:
		pObj = m_pObjManager->GetTool(m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol);
		break;
	}
	if (pObj == NULL)
		return;
	RECT temprc;
	temprc.left = m_rcArea[2].left;
	temprc.right = m_rcArea[2].right;
	temprc.top = m_rcArea[2].top;
	temprc.bottom = temprc.top + 30;
	//名称
	wsprintf(str, L"%s", pObj->GetName());
	DrawText(hdc, str, wcslen(str), &temprc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	//数量
	wsprintf(str, L"数量:    %d",pObj->GetCount());
	temprc.top = temprc.bottom;
	temprc.bottom = temprc.top + 30;
	DrawText(hdc, str, wcslen(str), &temprc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);

	//简介
	wsprintf(str, L"%s", pObj->GetIntro());
	temprc.top = temprc.bottom + 10;
	temprc.bottom = m_rcArea[2].bottom/2;
	temprc.left += 10;
	temprc.right -= 10;
	DrawText(hdc, str, wcslen(str), &temprc, DT_CENTER|DT_WORDBREAK);
	
	//属性列举
	temprc.top = temprc.bottom + 10;
	temprc.bottom = m_rcArea[2].bottom;
	switch (m_typeSelState.choice)
	{
		//药物
	case 0:
		((CMedicine*)pObj)->ListMoreInfo(str);
		break;
		//装备
	case 1:
		((CEquipment*)pObj)->ListMoreInfo(str);
		break;
		//道具
	case 2:
		lstrcpy(str, L"");
		break;
	}
	DrawText(hdc, str, wcslen(str), &temprc, DT_CENTER);
}
void CObjectPannel::PaintMCSel(HDC hdc)
{
	RECT temprc;
	temprc.left = m_rcClient.left + 40;
	temprc.right = temprc.left + 80;
	temprc.top = m_rcClient.bottom - 200;
	temprc.bottom = temprc.top + 30 * m_selMCState.maxChoice;

	CGraphHelper::MyRectangle(hdc, temprc);

	for (int i = 0; i < m_selMCState.maxChoice; ++i)
	{
		if (m_selMCState.choice == i)
			SetTextColor(hdc, RGB(255, 255, 255));
		else
			SetTextColor(hdc, RGB(0, 0, 0));
		temprc.bottom = temprc.top + 30;
		DrawText(hdc, m_pMc[i].GetName(), wcslen(m_pMc[i].GetName()), &temprc, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		temprc.top += 30;
	}
}

void CObjectPannel::Handle()
{
	if (GetAsyncKeyState(VK_ESCAPE) < 0||
		GetAsyncKeyState(VK_SPACE) < 0)
	{
		if (m_selMCState.showMsg)
		{
			m_selMCState.showMsg = FALSE;
			return;
		}
	}
	switch (m_opState)
	{
	case OP_TYPESEL:
		TypeSelHandle();
		break;
	case OP_OBJSEL:
		ObjSelHandle();
		break;
	case OP_USE:
		UseStateHandle();
		break;
	case OP_SELMC:
		SelMCHandle();
		break;
	}
	
}

void CObjectPannel::TypeSelHandle()
{
	if (GetAsyncKeyState(VK_ESCAPE)<0)
	{
		ExitTypeSelState();
	}
	else if (GetAsyncKeyState(VK_UP)<0)
	{
		if (--m_typeSelState.choice <0 )
		{
			m_typeSelState.choice = m_typeSelState.maxChoice - 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN)<0)
	{
		if (++m_typeSelState.choice >= m_typeSelState.maxChoice)
		{
			m_typeSelState.choice = 0;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE) < 0){
		TurnObjSelState();
	}
}
void CObjectPannel::ObjSelHandle()
{
	if (GetAsyncKeyState(VK_ESCAPE)<0)
	{
		ExitObjSelState();
	}
	else if (GetAsyncKeyState(VK_UP)<0)
	{
		if (--m_objSelState.curY <0)
		{
			m_objSelState.curY = m_objSelState.maxRow - 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN)<0)
	{
		if (++m_objSelState.curY >= m_objSelState.maxRow)
		{
			m_objSelState.curY = 0;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT)<0)
	{
		if (--m_objSelState.curX <0)
		{
			m_objSelState.curX = m_objSelState.maxCol - 1;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT)<0)
	{
		if (++m_objSelState.curX >= m_objSelState.maxCol)
		{
			m_objSelState.curX = 0;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE) < 0){
		int num = m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol;
		//如果该区域不存在物品
		switch (m_typeSelState.choice)
		{
		case CHOICE_MEDICINE:
			if (FALSE==m_pObjManager->IsExistObject(num, CObjectManager::OT_MEDI))
				return;
			break;
		case CHOICE_EQUIPMENT:
			if (FALSE == m_pObjManager->IsExistObject(num, CObjectManager::OT_EQUI))
				return;
			break;
		case CHOICE_TOOL:
			if (FALSE == m_pObjManager->IsExistObject(num, CObjectManager::OT_TOOL))
				return;
			break;
		}
		//存在，则进入角色使用选择
		TurnUseState();
	}
}
void CObjectPannel::UseStateHandle()
{
	if (GetAsyncKeyState(VK_ESCAPE) < 0){
		ExitUseState();
	}
	else if (GetAsyncKeyState(VK_UP)<0)
	{
		if (--m_useState.choice <0)
		{
			m_useState.choice = m_useState.maxChoice - 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN)<0)
	{
		if (++m_useState.choice >= m_useState.maxChoice)
		{
			m_useState.choice = 0;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE) < 0){
		TurnSelMCState();
	}
}
void CObjectPannel::SelMCHandle()
{
	if (GetAsyncKeyState(VK_ESCAPE) < 0){
		ExitSelMCState();
	}
	else if (GetAsyncKeyState(VK_UP)<0)
	{
		if (--m_selMCState.choice <0)
		{
			m_selMCState.choice = m_selMCState.maxChoice - 1;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN)<0)
	{
		if (++m_selMCState.choice >= m_selMCState.maxChoice)
		{
			m_selMCState.choice = 0;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE) < 0){
		//剩余量
		int remain = 0;
		switch (m_typeSelState.choice)
		{
			//药物使用
		case CHOICE_MEDICINE:
			switch (m_useState.choice)
			{
				//装备
			case 0:
				m_selMCState.showMsg = TRUE;
				lstrcpy(m_selMCState.msg, L"物品不可装备o(╯□╰)o");
				ExitSelMCState();
				break;
				//使用
			case 1:
				remain=m_pMc[m_selMCState.choice].UseMedicine(m_pObjManager->GetMedicine(m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol), m_pObjManager, m_selMCState.msg);
				m_selMCState.showMsg = TRUE;
				if (remain <= 0){
					ExitSelMCState();
					ExitUseState();
				}
				break;
			}
			break;
		case CHOICE_EQUIPMENT:
			switch (m_useState.choice)
			{
				//装备
			case 0:
				m_pMc[m_selMCState.choice].WearEquipment(m_pObjManager->GetEquipment(m_objSelState.curX + m_objSelState.curY*m_objSelState.maxCol), m_pObjManager);
				m_selMCState.showMsg = TRUE;
				lstrcpy(m_selMCState.msg, L"装备成功");
				ExitSelMCState();
				ExitUseState();
				break;
				//使用
			case 1:
				m_selMCState.showMsg = TRUE;
				lstrcpy(m_selMCState.msg, L"装备不可食用o(╯□╰)o");
				ExitSelMCState();
				break;
			}
			break;
		case CHOICE_TOOL:
			m_selMCState.showMsg = TRUE;
			lstrcpy(m_selMCState.msg, L"该物品用处不明");
			ExitSelMCState();
			ExitUseState();
			break;
		}
	}
}

void CObjectPannel::TurnTypeSelState()
{
	m_opState = OP_TYPESEL;
	m_typeSelState.choice = 0;
}
void CObjectPannel::TurnObjSelState()
{
	m_opState = OP_OBJSEL;
	m_objSelState.curX = m_objSelState.curY = 0;
}
void CObjectPannel::TurnUseState()
{
	m_opState = OP_USE;
	m_useState.choice = 0;
}
void CObjectPannel::TurnSelMCState()
{
	m_opState = OP_SELMC;
	m_selMCState.choice = 0;
}


void CObjectPannel::ExitTypeSelState()
{
	SendMessage(m_hWnd, MSG_TURN_MAIN, WPARAM_KEEP_MUSIC, 0);
}
void CObjectPannel::ExitObjSelState()
{
	m_opState = OP_TYPESEL;
}
void CObjectPannel::ExitUseState()
{
	m_opState = OP_OBJSEL;
}
void CObjectPannel::ExitSelMCState()
{
	m_opState = OP_USE;
}
	
