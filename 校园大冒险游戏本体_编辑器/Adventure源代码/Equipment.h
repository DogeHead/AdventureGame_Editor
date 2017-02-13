#pragma once
#include"Object.h"
#include"GameUtil.h"
#define EQUIPMENT_COUNT 6
class CEquipment :public CMyObject{
public:
	//武器、等
	enum EquipmentType{ ET_WEAPON, ET_1, ET_2, ET_3, ET_4, ET_5 };
private:
	//增益
	int m_iMaxHP,						//最大HP
		m_iMaxMP,						//最大MP
		m_iZhiyu,						//智育
		m_iTiyu,						//体育
		m_iDeyu,						//德育
		m_iPhysicalAttack, 				//物理攻击
		m_iPhysicalDefense,				//物理防御
		m_iMagicAttack,					//魔法攻击
		m_iCritChance, 					//暴击率
		m_iEvdChance, 					//闪避率
		m_iMagicDefense,				//魔法防御
		m_iActionSpeed;					//速度
	EquipmentType m_type;
public:

	virtual void Init(TCHAR *name);
	virtual void Paint(HDC hdc, int x, int y, int cx, int cy);
	virtual BOOL LoadData(TCHAR *name);

	void ListMoreInfo(TCHAR* str);
	//友元类声明
	friend class CMainCharacter;
};