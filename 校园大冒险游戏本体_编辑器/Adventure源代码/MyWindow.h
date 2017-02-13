#include<windows.h>


class MyWindow
{
public:
	HWND hwnd;
	HWND hParent;
	LPCWSTR Class;
	HINSTANCE hInstance;
	HCURSOR hCur;
	HBRUSH hBrush;
	WNDPROC WndProc;
	LPCWSTR Caption;
	LPWSTR szWindowName;
	int iWidth, iHeight;
	void Create(DWORD, DWORD, int, int, int, int);
private:
	int regist();
};

