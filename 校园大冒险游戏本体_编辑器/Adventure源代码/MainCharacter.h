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
	//ְҵ����
	enum PeopleCareer{PC_COMPUTER,PC_SPORTS,PC_FOOD};
	//��������
	enum ActionTypes{AT_NORMAL,AT_SKILL}m_actionTypes;

private:
	
	TCHAR m_csName[64];
	TCHAR m_csCareer[32];
	HBITMAP m_bitmapCharacter;
	HBITMAP m_bitmapFightCharacter;
	POINT m_ptPos;
	int m_hp, m_mp;
	int m_dir;//����
	int m_action;//���ڵڼ�֡
	int m_maxAction;
	BOOL m_bIsWalk;
	int m_iHP, m_iMP;//��ǰHP��MP
	//�����ԣ��ȼ�������������������������ֵ
	int m_iLevel,
		m_iZhiyu,
		m_iTiyu,
		m_iDeyu,
		m_iExp,
		m_iMoney;
	int m_iLevelUpExp;
	int m_iDamage;										//�ܵ��˺���������ʾ
	BOOL m_bShowDamage;
	//�����ԣ�����ֵ���������������������������
	//		ħ��ֵ��ħ����������������
	//		�����ʣ��ٷֱȣ��������ʣ��ٷֱȣ���ħ����������������
	//		�ٶȣ���������������
	int m_iMaxHP, m_iPhysicalAttack, m_iPhysicalDefense,
		m_iMaxMP, m_iMagicAttack,
		m_iCritChance, m_iEvdChance, m_iMagicDefense,
		m_iActionSpeed;
	//װ������Ϣ
	struct{
		BOOL bIsExist[EQUIPMENT_COUNT];			//6��װ�����Ƿ���װ����
		CEquipment* equipment[EQUIPMENT_COUNT];	//װ����Ϣ
	}m_equipment;
public:
	int UseMedicine(CMedicine* medicine,CObjectManager* manager,TCHAR* resultStr);			//ʹ��ҩ�����ʣ����
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
	
	
	
	//Get����
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

	//Set����
	void SetNowHP(int i){ m_iHP = i; }
	void SetActionTypes(ActionTypes at){ m_actionTypes = at; }
	void SetShowDamage(BOOL b){ m_bShowDamage = b; }
	void SetName(TCHAR* name);
	void SetPos(int x, int y){ m_ptPos.x = x, m_ptPos.y = y; }
};