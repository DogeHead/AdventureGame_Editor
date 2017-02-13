#pragma once
#include"Object.h"
#include"GameUtil.h"
class CMedicine :public CMyObject{
private:
	//����
	int m_iMaxHP,				//���HP
		m_iHP,					//HP
		m_iMaxMP,				//���MP
		m_iMP,					//MP
		m_iExp;					//����ֵ
	BOOL m_bUnscramble;			//�Ƿ�ⶾ
public:
	

	virtual void Init(TCHAR *name);
	virtual BOOL LoadData(TCHAR *name);
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy);
	void BeUsed();
	void ListMoreInfo(TCHAR *str);									//�о���ϸ��Ϣ
	//��Ԫ������
	friend class CMainCharacter;
};