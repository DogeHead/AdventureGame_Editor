#pragma once
#include<windows.h>
#include<vector>
#include"Equipment.h"
#include"Medicine.h"
#include"Tool.h"
using namespace std;
//物品管理器，用来管理主角身上物品信息
class CObjectManager{
private:
	vector<CEquipment> m_vecEquipment;
	vector<CMedicine> m_vecMedicine;
	vector<CTool> m_vecTool;


public:
	//物品类型：药物，装备，道具
	enum ObjectType{OT_MEDI,OT_EQUI,OT_TOOL};
	void Init();
	void LoadData();												//读取存档信息
	void CheckObjectRunOut(TCHAR *name,ObjectType ot);				//检查物品是否用完，数量为0则从vector中清除，
	BOOL IsExistObject(int num, ObjectType ot);						//检查是否存在该编号的物品					
	void GetNewObject(CMyObject* object, ObjectType ot);				//获得新的物品，添加进入vector


	vector<CMedicine>& GetMedicineVec(){ return m_vecMedicine; }
	vector<CEquipment>& GetEquipmentVec(){ return m_vecEquipment; }
	vector<CTool>& GetToolVec(){ return m_vecTool; }

	CMedicine* GetMedicine(int num){ 
		if (num<m_vecMedicine.size())
		return &m_vecMedicine[num];
		else return NULL;
	}
	CEquipment* GetEquipment(int num){
		if (num<m_vecEquipment.size())
		return &m_vecEquipment[num];
		else return NULL;
	}
	CTool* GetTool(int num){
		if (num<m_vecTool.size()) return &m_vecTool[num];
		else return NULL;
	}
};