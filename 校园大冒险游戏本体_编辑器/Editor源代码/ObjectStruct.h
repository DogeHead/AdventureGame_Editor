#pragma once
#include<windows.h>
//����MFC����һ����ΪCObject���࣬��˴˴�ֻ�ܸ���ΪCMyObject
struct CMyObject{
	TCHAR m_csName[32];					//��Ʒ��
	TCHAR m_csIntro[256];				//��Ʒ����		
	int m_iCount;						//����
	
};
struct CEquipment:public CMyObject{
	enum EquipmentType{ ET_WEAPON, ET_1, ET_2, ET_3, ET_4, ET_5 };
	//����
	int m_iMaxHP,						//���HP
		m_iMaxMP,						//���MP
		m_iZhiyu,						//����
		m_iTiyu,						//����
		m_iDeyu,						//����
		m_iPhysicalAttack, 				//������
		m_iPhysicalDefense,				//�������
		m_iMagicAttack,					//ħ������
		m_iCritChance, 					//������
		m_iEvdChance, 					//������
		m_iMagicDefense,				//ħ������
		m_iActionSpeed;					//�ٶ�
	EquipmentType m_type;

};

struct CMedicine :public CMyObject{
	//����
	int m_iMaxHP,				//���HP
		m_iHP,					//HP
		m_iMaxMP,				//���MP
		m_iMP,					//MP
		m_iExp;					//����ֵ
	BOOL m_bUnscramble;			//�Ƿ�ⶾ

};
struct CTool :public CMyObject{
};