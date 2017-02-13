#pragma once
#include"Object.h"
#include"GameUtil.h"
#define EQUIPMENT_COUNT 6
class CEquipment :public CMyObject{
public:
	//��������
	enum EquipmentType{ ET_WEAPON, ET_1, ET_2, ET_3, ET_4, ET_5 };
private:
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
public:

	virtual void Init(TCHAR *name);
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy);
	virtual BOOL LoadData(TCHAR *name);

	void ListMoreInfo(TCHAR* str);
	//��Ԫ������
	friend class CMainCharacter;
};