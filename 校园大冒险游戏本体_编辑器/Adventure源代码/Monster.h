#pragma once
#include<windows.h>
#include<stdio.h>
#include"GameUtil.h"
#include"Creature.h"
#include"MainCharacter.h"
#include"resource.h"
#pragma comment(lib, "Msimg32.lib")
#define MAX_MONCOUNT 5
class CMonster:public CCreature
{
public:
	enum ActionTypes{AT_NORMAL,AT_SKILL}m_actionTypes;
private:
	enum MonsterType {MT_};
	TCHAR m_csName[32];
	BOOL m_bIsDead;					//是否死亡
	int m_iMaxHP,
		m_iHP,
		m_iPhysicalAttack,
		m_iMagicAttack,
		m_iPhysicalDefense,
		m_iMagicDefense,
		m_iActionSpeed;				//出手速度
	int m_iDamage;					//受到伤害，用来显示
	BOOL m_bShowDamage;				//是否展示受到伤害
	int m_iMoney,
		m_iExp;						//掉落金钱与经验
public:
	void Init(TCHAR* name, int maxHP, int hp, int atk, int dfs);
	void SetName(TCHAR* name){ lstrcpy(m_csName, name); }
	void SetMaxHP(int maxHP){ m_iMaxHP = maxHP; }
	void SetHP(int hp){ m_iHP = hp; }
	void SetPhysicalAttack(int atk){ m_iPhysicalAttack = atk; }
	void SetMagicAttack(int atk){ m_iMagicAttack = atk; }
	void SetPhysicalDefense(int dfs){ m_iPhysicalDefense = dfs; }
	void SetMagicDefense(int mdfs){ m_iMagicDefense = mdfs; }
	void SetShowDamage(BOOL show){ m_bShowDamage = show; }
	void BeAttacked(int damage);
	void Attack(CCreature* mc, int mcCount);

	void Paint(HDC hdc,int x,int y,int size);
	void Update();

	TCHAR *GetName(){ return m_csName; }
	int GetMaxHP(){ return m_iMaxHP; }
	int GetHP(){ return m_iHP; }
	int GetPhysicalAttack(){ return m_iPhysicalAttack; }
	int GettMagicAttack(){ return m_iMagicAttack; }
	int GetPhysicalDefense(){ return m_iPhysicalAttack; }
	int GetMagicDefense(){ return m_iMagicDefense; }
	int GetActionSpeed(){ return m_iActionSpeed; }
	int GetMoney(){ return m_iMoney; }
	int GetExp(){ return m_iExp; }
	BOOL GetIsDead(){ return m_bIsDead; }
};