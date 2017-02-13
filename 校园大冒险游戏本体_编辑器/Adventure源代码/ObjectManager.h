#pragma once
#include<windows.h>
#include<vector>
#include"Equipment.h"
#include"Medicine.h"
#include"Tool.h"
using namespace std;
//��Ʒ��������������������������Ʒ��Ϣ
class CObjectManager{
private:
	vector<CEquipment> m_vecEquipment;
	vector<CMedicine> m_vecMedicine;
	vector<CTool> m_vecTool;


public:
	//��Ʒ���ͣ�ҩ�װ��������
	enum ObjectType{OT_MEDI,OT_EQUI,OT_TOOL};
	void Init();
	void LoadData();												//��ȡ�浵��Ϣ
	void CheckObjectRunOut(TCHAR *name,ObjectType ot);				//�����Ʒ�Ƿ����꣬����Ϊ0���vector�������
	BOOL IsExistObject(int num, ObjectType ot);						//����Ƿ���ڸñ�ŵ���Ʒ					
	void GetNewObject(CMyObject* object, ObjectType ot);				//����µ���Ʒ����ӽ���vector


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