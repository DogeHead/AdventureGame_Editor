#pragma once
#include<windows.h>
#include<fstream>
using namespace std;
#include"GraphHelper.h"
#include"BinObjStruct.h"
class CMyObject{
protected:
	TCHAR m_csName[32];					//��Ʒ��
	TCHAR m_csIntro[256];				//��Ʒ����
	int m_iCount;						//����
public:
	void SetName(TCHAR *name){ lstrcpy(m_csName, name); }
	void SetIntro(TCHAR *intro){ lstrcpy(m_csIntro, intro); }
	virtual TCHAR *GetName(){ return m_csName; }
	virtual TCHAR *GetIntro(){ return m_csIntro; }
	virtual int GetCount(){ return m_iCount; }

	virtual void Init(TCHAR *name)=0;							//ͨ�����ֳ�ʼ������Ʒ
	virtual BOOL LoadData(TCHAR *name)=0;						//ͨ�����ִ��ļ���ȡ��Ʒ����
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy)=0;	//����
};