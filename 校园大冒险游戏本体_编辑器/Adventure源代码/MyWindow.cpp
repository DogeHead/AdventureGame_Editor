#include"MyWindow.h"


void MyWindow::Create(DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight)
{

	if (!hwnd) regist();
	hwnd = CreateWindowEx(dwExStyle, Class, Caption, dwStyle, x, y, nWidth, nHeight, hParent, NULL, GetModuleHandle(0), NULL);
	if (hwnd == 0)
		MessageBox(0, L"创建窗口失败", L"", 0);
	UpdateWindow(hwnd);
}
int  MyWindow::regist()
{
	WNDCLASSEX WndClass;
	if (hCur == NULL)hCur = LoadCursor(NULL, IDC_ARROW);
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = 0;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = NULL;
	WndClass.hCursor = hCur;
	WndClass.hbrBackground = hBrush;
	WndClass.lpszMenuName = 0;
	WndClass.lpszClassName = Class;
	WndClass.hIconSm = 0;
	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(0, L"注册窗口失败", L"错误信息", MB_ICONEXCLAMATION | MB_OK | MB_SYSTEMMODAL);
		return 0;
	}
	return 1;
}

