#include"ObjectManager.h"

void CObjectManager::Init(){
	CMedicine temp;
	if (temp.LoadData(L"可乐"))
	{

	}
	else{
		temp.Init(L"测试");
	}
	m_vecMedicine.push_back(temp);

	CEquipment temp1;
	if (temp1.LoadData(L"钢笔"))
	{

	}
	else{
		temp1.Init(L"点击就送的屠龙宝刀");
	}
	m_vecEquipment.push_back(temp1);

	CTool temp2;
	if (temp2.LoadData(L"水瓶"))
	{
		
	}
	else{
		temp2.Init(L"不知名星星");
	}
	m_vecTool.push_back(temp2);
}
void CObjectManager::LoadData()
{

}
void CObjectManager::CheckObjectRunOut(TCHAR *name, ObjectType ot)
{
	switch (ot)
	{
	case OT_MEDI:
		for (vector<CMedicine>::iterator iter=m_vecMedicine.begin(); iter < m_vecMedicine.end(); ++iter)
		{
			if (lstrcmp(iter->GetName(), name)==0){
				if (iter->GetCount() == 0){
					m_vecMedicine.erase(iter);
					break;
				}
			}
		}
		break;
	case OT_EQUI:
		for (vector<CEquipment>::iterator iter = m_vecEquipment.begin(); iter < m_vecEquipment.end(); ++iter)
		{
			if (lstrcmp(iter->GetName(), name) == 0){
				if (iter->GetCount() == 0){
					m_vecEquipment.erase(iter);
					break;
				}
			}
		}
		break;
	case OT_TOOL:
		break;
	}
}
BOOL CObjectManager::IsExistObject(int num, ObjectType ot)
{
	switch (ot)
	{
	case OT_MEDI:
		return num < m_vecMedicine.size();
		break;
	case OT_EQUI:
		return num < m_vecEquipment.size();
		break;
	case OT_TOOL:
		return num < m_vecTool.size();
		break;
	}
	return FALSE;
}
void CObjectManager::GetNewObject(CMyObject* object, ObjectType ot)
{
	switch (ot)
	{
	case OT_MEDI:
		m_vecMedicine.push_back(*(CMedicine*)object);
		break;
	case OT_EQUI:
		m_vecEquipment.push_back(*(CEquipment*)object);
		break;
	case OT_TOOL:
		m_vecTool.push_back(*(CTool*)object);
		break;
	}
}