#pragma once
#include<windows.h>
//由于MFC中有一个名为CObject的类，因此此处只能改名为CMyObject
struct CMyObject{
	TCHAR m_csName[32];					//物品名
	TCHAR m_csIntro[256];				//物品介绍		
	int m_iCount;						//数量
	
};
struct CEquipment:public CMyObject{
	enum EquipmentType{ ET_WEAPON, ET_1, ET_2, ET_3, ET_4, ET_5 };
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

};

struct CMedicine :public CMyObject{
	//增益
	int m_iMaxHP,				//最大HP
		m_iHP,					//HP
		m_iMaxMP,				//最大MP
		m_iMP,					//MP
		m_iExp;					//经验值
	BOOL m_bUnscramble;			//是否解毒

};
struct CTool :public CMyObject{
};