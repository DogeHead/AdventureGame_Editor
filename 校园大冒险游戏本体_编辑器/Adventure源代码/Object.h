#pragma once
#include<windows.h>
#include<fstream>
using namespace std;
#include"GraphHelper.h"
#include"BinObjStruct.h"
class CMyObject{
protected:
	TCHAR m_csName[32];					//物品名
	TCHAR m_csIntro[256];				//物品介绍
	int m_iCount;						//数量
public:
	void SetName(TCHAR *name){ lstrcpy(m_csName, name); }
	void SetIntro(TCHAR *intro){ lstrcpy(m_csIntro, intro); }
	virtual TCHAR *GetName(){ return m_csName; }
	virtual TCHAR *GetIntro(){ return m_csIntro; }
	virtual int GetCount(){ return m_iCount; }

	virtual void Init(TCHAR *name)=0;							//通过名字初始化该物品
	virtual BOOL LoadData(TCHAR *name)=0;						//通过名字从文件获取物品数据
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy)=0;	//绘制
};