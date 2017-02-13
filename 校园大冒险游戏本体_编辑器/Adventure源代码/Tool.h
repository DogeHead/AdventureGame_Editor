#pragma once
#include"Object.h"
#include"GameUtil.h"
class CTool :public CMyObject{
private:

	
public:

	virtual void Init(TCHAR *name);
	virtual BOOL LoadData(TCHAR *name);
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy);
};