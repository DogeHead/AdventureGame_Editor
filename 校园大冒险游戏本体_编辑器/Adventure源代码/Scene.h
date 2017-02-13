#include<windows.h>

class CScene{
public:
	virtual void Init(HWND hwnd,RECT& rect)=0;
	virtual void Paint(HDC hdc)=0;
	virtual void Handle()=0;
};