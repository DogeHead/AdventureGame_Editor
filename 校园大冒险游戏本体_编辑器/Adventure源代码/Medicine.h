#pragma once
#include"Object.h"
#include"GameUtil.h"
class CMedicine :public CMyObject{
private:
	//增益
	int m_iMaxHP,				//最大HP
		m_iHP,					//HP
		m_iMaxMP,				//最大MP
		m_iMP,					//MP
		m_iExp;					//经验值
	BOOL m_bUnscramble;			//是否解毒
public:
	

	virtual void Init(TCHAR *name);
	virtual BOOL LoadData(TCHAR *name);
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy);
	void BeUsed();
	void ListMoreInfo(TCHAR *str);									//列举详细信息
	//友元类声明
	friend class CMainCharacter;
};