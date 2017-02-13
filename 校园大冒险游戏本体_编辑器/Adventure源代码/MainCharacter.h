#pragma once
#include<windows.h>
#include"GameUtil.h"
#include"Creature.h"
#include"Equipment.h"
#include"Medicine.h"
#include"ObjectManager.h"
#include"Monster.h"
#include"resource.h"
#pragma comment(lib, "Msimg32.lib")
#define MAX_MCCOUNT 3
class CMainCharacter :public CCreature{
	public:
	//职业类型
	enum PeopleCareer{PC_COMPUTER,PC_SPORTS,PC_FOOD};
	//动作类型
	enum ActionTypes{AT_NORMAL,AT_SKILL}m_actionTypes;

private:
	
	TCHAR m_csName[64];
	TCHAR m_csCareer[32];
	HBITMAP m_bitmapCharacter;
	HBITMAP m_bitmapFightCharacter;
	POINT m_ptPos;
	int m_hp, m_mp;
	int m_dir;//方向
	int m_action;//处于第几帧
	int m_maxAction;
	BOOL m_bIsWalk;
	int m_iHP, m_iMP;//当前HP与MP
	//主属性：等级、智育、体育、德育、经验值
	int m_iLevel,
		m_iZhiyu,
		m_iTiyu,
		m_iDeyu,
		m_iExp,
		m_iMoney;
	int m_iLevelUpExp;
	int m_iDamage;										//受到伤害，用来显示
	BOOL m_bShowDamage;
	//副属性：生命值、物理攻击、物理防御，（体育）
	//		魔法值、魔法攻击，（智育）
	//		暴击率（百分比）、闪避率（百分比）、魔法防御，（德育）
	//		速度，（体育、智育）
	int m_iMaxHP, m_iPhysicalAttack, m_iPhysicalDefense,
		m_iMaxMP, m_iMagicAttack,
		m_iCritChance, m_iEvdChance, m_iMagicDefense,
		m_iActionSpeed;
	//装备的信息
	struct{
		BOOL bIsExist[EQUIPMENT_COUNT];			//6格装备，是否有装备上
		CEquipment* equipment[EQUIPMENT_COUNT];	//装备信息
	}m_equipment;
public:
	int UseMedicine(CMedicine* medicine,CObjectManager* manager,TCHAR* resultStr);			//使用药物，返回剩余量
	void WearEquipment(CEquipment* equipment, CObjectManager* manager);
	void UnWearEquipment(int pos);
	

	void Init(PeopleCareer pc);
	void Paint(HDC hdc,int x,int y);
	void PaintFightMC(HDC hdc, int x, int y);
	void Update();
	void ChangeDir(int dir){ m_dir = dir; m_bIsWalk = TRUE; }
	void Attack(int monNum, CCreature *mon, int selMon);
	void BeAttacked(int damage);
	void GetExpAndMoney(int exp, int money){
		m_iExp += exp;
		m_iMoney += money;
	}
	void GainExp(int exp);
	
	
	
	//Get方法
	POINT GetPos(){ return m_ptPos; }
	TCHAR* GetName(){ return m_csName; }
	TCHAR* GetCareer(){ return m_csCareer; }
	int GetLevel(){ return m_iLevel; }
	int GetZhiyu(){ return m_iZhiyu; }
	int GetTiyu(){ return m_iTiyu; }
	int GetDeyu(){ return m_iDeyu; }
	int GetExp(){ return m_iExp; }
	int GetLevelUpExp(){ return m_iLevelUpExp; }
	int GetHP(){ return m_iMaxHP; }
	int GetPhysicalAttack(){ return m_iPhysicalAttack; }
	int GetPhysicalDefense(){ return m_iPhysicalDefense; }
	int GetMP(){ return m_iMaxMP; }
	int GetMagicAttack(){ return m_iMagicAttack; }
	int GetMagicDefense(){ return m_iMagicDefense; }
	int GetCritChance(){ return m_iCritChance; }
	int GetEvdChance(){ return m_iEvdChance; }
	int GetActionSpeed(){ return m_iActionSpeed; }
	int GetNowHP(){ return m_iHP; }
	int GetNowMP(){ return m_iMP; }

	//Set方法
	void SetNowHP(int i){ m_iHP = i; }
	void SetActionTypes(ActionTypes at){ m_actionTypes = at; }
	void SetShowDamage(BOOL b){ m_bShowDamage = b; }
	void SetName(TCHAR* name);
	void SetPos(int x, int y){ m_ptPos.x = x, m_ptPos.y = y; }
};