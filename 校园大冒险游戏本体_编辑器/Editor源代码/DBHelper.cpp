#include"stdafx.h"

CDBHelper::CDBHelper()
{
	this->m_pMyConnect = NULL;
	this->m_pRst = NULL;
}
CDBHelper::~CDBHelper()
{
	this->m_pMyConnect = NULL;
	this->m_pRst = NULL;
}


void CDBHelper::InitDBHelper()
{
	CoInitialize(NULL);//��ʼ��COM����
	_ConnectionPtr pMyConnect(__uuidof(Connection));//�������Ӷ���ʵ��������
	//_RecordsetPtr pRst(__uuidof(Recordset));//�����¼������ʵ��������
	_RecordsetPtr pRst;
	TCHAR connectionString[256];
	wsprintf(connectionString, L"Provider='%s';Data Source='%s';Database=%s;Integrated Security='%s';",
		global_provider, global_dataSource, global_database, global_integratedSecurity);
	try{
		//Initial Catalog='Game'Ҳ�ã�Integrated  Security='SSPI'���ɸ�Ϊtrue ��Ȼ����˵��һ���ģ�����߸�Ϊtrue�ͳ���
		pMyConnect->ConnectionString = connectionString;
		pMyConnect->Open("", "", "", ConnectModeEnum::adModeUnknown);
	}
	catch (_com_error& e){
		MessageBox(NULL, L"Init DBHelper failed", L"error", MB_OK);
		return;
	}
	this->m_pMyConnect = pMyConnect;
	pRst.CreateInstance(__uuidof(Recordset));
	this->m_pRst = pRst;
}


void CDBHelper::CoInitDBHelper()
{
	//�ر����ͷŵ�˳���ܵߵ�������rst����connect
	//Ҳ����rst��close��release����connect��close��release
	this->m_pRst->Close();
	this->m_pMyConnect->Close();
	this->m_pRst.Release();
	this->m_pMyConnect.Release();
	CoUninitialize();
}

int* CDBHelper::LoadMap(CString csMapName,int &row,int &col)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where %s='%s'", global_table, KEY_NAME, csMapName);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() == 0)
	{
		MessageBox(NULL,L"�����ڵĵ�ͼ",L"��ѯ����",MB_OK);
		return NULL;
	}
	row = (int)this->m_pRst->GetCollect(KEY_ROW);
	col = (int)this->m_pRst->GetCollect(KEY_COL);

	return GetMap(row, col, (CString)this->m_pRst->GetCollect(KEY_MAP));
}

int *CDBHelper::GetMap(int row, int col, CString cs_map)
{
	int temp_val = 0;
	int *map = new int[row*col];
	for (int i = 0, k = 0; i < cs_map.GetLength(); ++i)
	{
		if (cs_map[i] == ',')
		{
			map[k++] = temp_val;
			temp_val = 0;
			continue;
		}
		temp_val *= 10;
		temp_val += cs_map[i] - '0';
	}
	return map;
}
CMedicine* CDBHelper::LoadMedicine(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where %s='%s'", global_medicine_table, KEY_MEDI_NAME, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() == 0)
	{
		MessageBox(NULL, L"�����ڵ�ҩ��", L"��ѯ����", MB_OK);
		return NULL;
	}
	CMedicine* medicine = new CMedicine();
	medicine->m_bUnscramble = (int)this->m_pRst->GetCollect(KEY_MEDI_UNSCRAMBLE);
	lstrcpy(medicine->m_csIntro,((CString)this->m_pRst->GetCollect(KEY_MEDI_INTRODUCTION)).GetBuffer());
	lstrcpy(medicine->m_csName, ((CString)this->m_pRst->GetCollect(KEY_MEDI_NAME)).GetBuffer());
	medicine->m_iCount = (int)this->m_pRst->GetCollect(KEY_MEDI_QUANTITY);
	medicine->m_iExp = (int)this->m_pRst->GetCollect(KEY_MEDI_EXP);
	medicine ->m_iHP = (int)this->m_pRst->GetCollect(KEY_MEDI_HP);
	medicine ->m_iMaxHP = (int)this->m_pRst->GetCollect(KEY_MEDI_MAXHP);
	medicine ->m_iMaxMP = (int)this->m_pRst->GetCollect(KEY_MEDI_MAXMP);
	medicine ->m_iMP = (int)this->m_pRst->GetCollect(KEY_MEDI_MP);
	return medicine;
}
CEquipment* CDBHelper::LoadEquipment(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where %s='%s'", global_equipment_table, KEY_EQUI_NAME, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() == 0)
	{
		MessageBox(NULL, L"�����ڵ�װ��", L"��ѯ����", MB_OK);
		return NULL;
	}

	CEquipment *equipment = new CEquipment();
	lstrcpy(equipment->m_csIntro, ((CString)this->m_pRst->GetCollect(KEY_EQUI_INTRODUCTION)).GetBuffer());
	lstrcpy(equipment->m_csName, ((CString)this->m_pRst->GetCollect(KEY_EQUI_NAME)).GetBuffer());
	equipment->m_iActionSpeed = (int)this->m_pRst->GetCollect(KEY_EQUI_SPEED);
	equipment->m_iCount = (int)this->m_pRst->GetCollect(KEY_EQUI_QUANTITY);
	equipment->m_iCritChance = (int)this->m_pRst->GetCollect(KEY_EQUI_CRITCHANCE);
	equipment->m_iDeyu = (int)this->m_pRst->GetCollect(KEY_EQUI_DEYU);
	equipment->m_iEvdChance = (int)this->m_pRst->GetCollect(KEY_EQUI_EVDCHANCE);
	equipment->m_iMagicAttack = (int)this->m_pRst->GetCollect(KEY_EQUI_MATTACK);
	equipment->m_iMagicDefense = (int)this->m_pRst->GetCollect(KEY_EQUI_MDEFENSE);
	equipment->m_iMaxHP = (int)this->m_pRst->GetCollect(KEY_EQUI_MAXHP);
	equipment->m_iMaxMP = (int)this->m_pRst->GetCollect(KEY_EQUI_MAXMP);
	equipment->m_iPhysicalAttack = (int)this->m_pRst->GetCollect(KEY_EQUI_PATTACK);
	equipment->m_iPhysicalDefense = (int)this->m_pRst->GetCollect(KEY_EQUI_PDEFENSE);
	equipment->m_iTiyu = (int)this->m_pRst->GetCollect(KEY_EQUI_TIYU);
	equipment->m_iZhiyu = (int)this->m_pRst->GetCollect(KEY_EQUI_ZHIYU);

	switch ((int)this->m_pRst->GetCollect(KEY_EQUI_EQUIPMENTTYPE))
	{
	case 0:
		equipment->m_type = CEquipment::ET_WEAPON;
		break;
	case 1:
		equipment->m_type = CEquipment::ET_1;
		break;
	case 2:
		equipment->m_type = CEquipment::ET_2;
		break;
	case 3:
		equipment->m_type = CEquipment::ET_3;
		break;
	case 4:
		equipment->m_type = CEquipment::ET_4;
		break;
	case 5:
		equipment->m_type = CEquipment::ET_5;
		break;
	}
	return equipment;
}
CTool* CDBHelper::LoadTool(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where %s='%s'", global_tool_table, KEY_TOOL_NAME, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() == 0)
	{
		MessageBox(NULL, L"�����ڵĵ���", L"��ѯ����", MB_OK);
		return NULL;
	}
	CTool *tool = new CTool();
	lstrcpy(tool->m_csIntro, ((CString)this->m_pRst->GetCollect(KEY_TOOL_INTRODUCTION)).GetBuffer());
	lstrcpy(tool->m_csName, ((CString)this->m_pRst->GetCollect(KEY_TOOL_NAME)).GetBuffer());
	tool->m_iCount = (int)this->m_pRst->GetCollect(KEY_TOOL_QUANTITY);

	return tool;
}
BOOL CDBHelper::SaveMap(CString mapName, int row, int col, int *map)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_table, mapName);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL,L"�Ѵ��ڵĵ�ͼ��,ȷ��Ҫ����?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
		}
	}
	m_pRst->Close();

	wsprintf(query, L"SELECT * FROM %s", global_table);
	m_pRst->Open(query,
		_variant_t((IDispatch*)m_pMyConnect, true),
		adOpenStatic,
		adLockOptimistic,
		adCmdText);
	//pRst = pMyConnect->Execute("select * from tb_test", NULL, adCmdText);
	
	CString csmap = L"";
	for (int i = 0; i < row*col; ++i)
	{
		csmap.AppendFormat(L"%d,", map[i]);
		//wsprintf(temp, L"%d,",m_map[i]);
		//StrCat(tcmap, temp);
	}

	m_pRst->AddNew();
	m_pRst->PutCollect(KEY_NAME, _variant_t(mapName));
	m_pRst->PutCollect(KEY_ROW, _variant_t(row));
	m_pRst->PutCollect(KEY_COL, _variant_t(col));
	m_pRst->PutCollect(KEY_MAP, _variant_t(csmap));
	m_pRst->Update();

	return TRUE;
}

BOOL CDBHelper::GetMapNameList(vector<CString>& vec)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() > 0)
	{
		while (!m_pRst->adoEOF)
		{
			vec.push_back((CString)this->m_pRst->GetCollect(KEY_NAME));
			m_pRst->MoveNext();
		}
	}
	

	return TRUE;
}
BOOL CDBHelper::LoadMedicineNameList(vector<CString>& vec){
	TCHAR query[128];

	wsprintf(query, L"select * from %s", global_medicine_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() > 0)
	{
		while (!m_pRst->adoEOF)
		{
			vec.push_back((CString)this->m_pRst->GetCollect(KEY_MEDI_NAME));
			m_pRst->MoveNext();
		}
	}

	return TRUE;
}
BOOL CDBHelper::LoadEquipmentNameList(vector<CString>& vec){
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_equipment_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() > 0)
	{
		while (!m_pRst->adoEOF)
		{
			vec.push_back((CString)this->m_pRst->GetCollect(KEY_EQUI_NAME));
			m_pRst->MoveNext();
		}
	}

	return TRUE;
}
BOOL CDBHelper::LoadToolNameList(vector<CString>& vec){
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_tool_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	if (this->m_pRst->GetRecordCount() > 0)
	{
		while (!m_pRst->adoEOF)
		{
			vec.push_back((CString)this->m_pRst->GetCollect(KEY_TOOL_NAME));
			m_pRst->MoveNext();
		}
	}

	return TRUE;
}
BOOL CDBHelper::SaveTool(CTool* tool)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_tool_table, tool->m_csName);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"�Ѵ��ڵĵ���,ȷ��Ҫ�޸�?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
		}
	}
	m_pRst->Close();

	wsprintf(query, L"SELECT * FROM %s", global_tool_table);
	m_pRst->Open(query,
		_variant_t((IDispatch*)m_pMyConnect, true),
		adOpenStatic,
		adLockOptimistic,
		adCmdText);

	m_pRst->AddNew();
	m_pRst->PutCollect(KEY_TOOL_NAME, _variant_t(tool->m_csName));
	m_pRst->PutCollect(KEY_TOOL_INTRODUCTION, _variant_t(tool->m_csIntro));
	m_pRst->PutCollect(KEY_TOOL_QUANTITY, _variant_t(tool->m_iCount));
	m_pRst->Update();

	return TRUE;
}
BOOL CDBHelper::SaveMedicine(CMedicine* medicine)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_medicine_table, medicine->m_csName);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"�Ѵ��ڵ�ҩ��,ȷ��Ҫ�޸�?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
		}
	}
	m_pRst->Close();

	wsprintf(query, L"SELECT * FROM %s", global_medicine_table);
	m_pRst->Open(query,
		_variant_t((IDispatch*)m_pMyConnect, true),
		adOpenStatic,
		adLockOptimistic,
		adCmdText);

	m_pRst->AddNew();
	m_pRst->PutCollect(KEY_MEDI_NAME, _variant_t(medicine->m_csName));
	m_pRst->PutCollect(KEY_MEDI_INTRODUCTION, _variant_t(medicine->m_csIntro));
	m_pRst->PutCollect(KEY_MEDI_UNSCRAMBLE, _variant_t(medicine->m_bUnscramble));
	m_pRst->PutCollect(KEY_MEDI_QUANTITY, _variant_t(medicine->m_iCount));
	m_pRst->PutCollect(KEY_MEDI_EXP, _variant_t(medicine->m_iExp));
	m_pRst->PutCollect(KEY_MEDI_HP, _variant_t(medicine->m_iHP));
	m_pRst->PutCollect(KEY_MEDI_MAXHP, _variant_t(medicine->m_iMaxHP));
	m_pRst->PutCollect(KEY_MEDI_MAXMP, _variant_t(medicine->m_iMaxMP));
	m_pRst->PutCollect(KEY_MEDI_MP, _variant_t(medicine->m_iMP));
	m_pRst->Update();
	return TRUE;
}
BOOL CDBHelper::SaveEquipment(CEquipment* equipment)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_equipment_table, equipment->m_csName);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"�Ѵ��ڵ�װ��,ȷ��Ҫ�޸�?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
		}
	}
	m_pRst->Close();

	wsprintf(query, L"SELECT * FROM %s", global_equipment_table);
	m_pRst->Open(query,
		_variant_t((IDispatch*)m_pMyConnect, true),
		adOpenStatic,
		adLockOptimistic,
		adCmdText);

	m_pRst->AddNew();
	m_pRst->PutCollect(KEY_EQUI_NAME, _variant_t(equipment->m_csName));
	m_pRst->PutCollect(KEY_EQUI_INTRODUCTION, _variant_t(equipment->m_csIntro));
	m_pRst->PutCollect(KEY_EQUI_SPEED, _variant_t(equipment ->m_iActionSpeed));
	m_pRst->PutCollect(KEY_EQUI_QUANTITY, _variant_t(equipment ->m_iCount));
	m_pRst->PutCollect(KEY_EQUI_CRITCHANCE, _variant_t(equipment ->m_iCritChance));
	m_pRst->PutCollect(KEY_EQUI_DEYU, _variant_t(equipment ->m_iDeyu));
	m_pRst->PutCollect(KEY_EQUI_EVDCHANCE, _variant_t(equipment ->m_iEvdChance));
	m_pRst->PutCollect(KEY_EQUI_MATTACK, _variant_t(equipment ->m_iMagicAttack));
	m_pRst->PutCollect(KEY_EQUI_MDEFENSE, _variant_t(equipment ->m_iMagicDefense));
	m_pRst->PutCollect(KEY_EQUI_MAXHP, _variant_t(equipment ->m_iMaxHP));
	m_pRst->PutCollect(KEY_EQUI_MAXMP, _variant_t(equipment ->m_iMaxMP));
	m_pRst->PutCollect(KEY_EQUI_PATTACK, _variant_t(equipment ->m_iPhysicalAttack));
	m_pRst->PutCollect(KEY_EQUI_PDEFENSE, _variant_t(equipment ->m_iPhysicalDefense));
	m_pRst->PutCollect(KEY_EQUI_TIYU, _variant_t(equipment ->m_iTiyu));
	m_pRst->PutCollect(KEY_EQUI_ZHIYU, _variant_t(equipment ->m_iZhiyu));
	m_pRst->PutCollect(KEY_EQUI_EQUIPMENTTYPE, _variant_t(equipment->m_type));
	m_pRst->Update();
	return TRUE;
}

BOOL CDBHelper::DeleteTool(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_tool_table, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"ȷ��Ҫɾ���õ���?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
			return TRUE;
		}
	}
	MessageBox(NULL, L"�����ڸõ���", L"��ʾ", MB_OK);
	return FALSE;
}
BOOL CDBHelper::DeleteMedicine(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_medicine_table, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"ȷ��Ҫɾ����ҩ��?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
			return TRUE;
		}
	}
	MessageBox(NULL, L"�����ڸ�ҩ��", L"��ʾ", MB_OK);
	return FALSE;
}
BOOL CDBHelper::DeleteEquipment(CString name){
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_equipment_table, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"ȷ��Ҫɾ����װ��?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
			return TRUE;
		}
	}
	MessageBox(NULL, L"�����ڸ�װ��", L"��ʾ", MB_OK);
	return FALSE;
}
BOOL CDBHelper::DeleteMap(CString name)
{
	TCHAR query[128];
	wsprintf(query, L"select * from %s where name='%s'", global_table, name);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);

	if (this->m_pRst->GetRecordCount() > 0)
	{
		if (IDNO == MessageBox(NULL, L"ȷ��Ҫɾ���õ�ͼ?", L"��ʾ", MB_YESNO))
		{
			CoInitDBHelper();
			return FALSE;
		}
		else{
			m_pRst->Delete(adAffectCurrent);
			return TRUE;
		}
	}
	MessageBox(NULL, L"�����ڸõ�ͼ", L"��ʾ", MB_OK);
	return FALSE;
}
BOOL CDBHelper::OpenFileDlg(CString& path)
{
	CFileDialog dlg(FALSE, //TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
		NULL);
	CString pathName;
	if (dlg.DoModal() == IDOK)
	{
		pathName = dlg.GetPathName(); //�ļ�����������FilePathName��
	}
	else
	{
		return FALSE;
	}
	//2.�жϸ��ļ��Ƿ���ڣ�������ȡ�����������򴴽��ļ�
	CFile exportFile;
	if (exportFile.Open(pathName, CFile::modeRead))
	{
		exportFile.Close();
		MessageBox(NULL, L"�Ѵ���ͬ���ļ�������������", L"��ʾ", MB_OK);
		return FALSE;
	}
	path = pathName;
	return TRUE;
}
BOOL CDBHelper::ExportBinaryTool(){
	//1��2.ѡ���ļ�����·��������
	CString pathName;
	if (FALSE == OpenFileDlg(pathName))
	{
		return FALSE;
	}
	CFile exportFile;
	//3.�����ļ�
	if (FALSE == exportFile.Open(pathName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite))
	{
		MessageBox(NULL, L"δ֪����", L"��ʾ", MB_OK);
		return FALSE;
	}

	//4.�����ݿ�
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_tool_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	//5.�������ݣ�д���ļ�
	while (!m_pRst->adoEOF)
	{
		CTool tool;
		lstrcpy(tool.m_csIntro, ((CString)this->m_pRst->GetCollect(KEY_TOOL_INTRODUCTION)).GetBuffer());
		lstrcpy(tool.m_csName, ((CString)this->m_pRst->GetCollect(KEY_TOOL_NAME)).GetBuffer());
		tool.m_iCount = (int)this->m_pRst->GetCollect(KEY_TOOL_QUANTITY);

		exportFile.Write((char*)&tool, sizeof(tool));
		exportFile.Flush();
		//�ƶ�ָ��
		m_pRst->MoveNext();
	}
	exportFile.Close();
	return TRUE;
}
BOOL CDBHelper::ExportBinaryMedicine()
{
	//1��2.ѡ���ļ�����·��������
	CString pathName;
	if (FALSE == OpenFileDlg(pathName))
	{
		return FALSE;
	}
	//3.�����ļ�
	fstream fs(pathName, ios::out | ios::binary);
	fs.seekg(0, ios::beg);
	//4.�����ݿ�
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_medicine_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	//5.�������ݣ�д���ļ�
	while (!m_pRst->adoEOF)
	{
		CMedicine medicine;
		lstrcpy(medicine.m_csIntro, ((CString)this->m_pRst->GetCollect(KEY_MEDI_INTRODUCTION)).GetBuffer());
		lstrcpy(medicine.m_csName, ((CString)this->m_pRst->GetCollect(KEY_MEDI_NAME)).GetBuffer());
		medicine.m_iCount = (int)this->m_pRst->GetCollect(KEY_MEDI_QUANTITY);
		medicine.m_bUnscramble = (int)this->m_pRst->GetCollect(KEY_MEDI_UNSCRAMBLE);
		medicine.m_iExp = (int)this->m_pRst->GetCollect(KEY_MEDI_EXP);
		medicine.m_iHP = (int)this->m_pRst->GetCollect(KEY_MEDI_HP);
		medicine.m_iMaxHP = (int)this->m_pRst->GetCollect(KEY_MEDI_MAXHP);
		medicine.m_iMaxMP = (int)this->m_pRst->GetCollect(KEY_MEDI_MAXMP);
		medicine.m_iMP = (int)this->m_pRst->GetCollect(KEY_MEDI_MP);

		fs.write((char*)&medicine, sizeof(CMedicine));
		//�ƶ�ָ��
		m_pRst->MoveNext();
	}
	fs.close();

	return TRUE;
}
BOOL CDBHelper::ExportBinaryEquipment()
{
	//1��2.ѡ���ļ�����·��������
	CString pathName;
	if (FALSE == OpenFileDlg(pathName))
	{
		return FALSE;
	}
	CFile exportFile;
	//3.�����ļ�
	if (FALSE == exportFile.Open(pathName, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite))
	{
		MessageBox(NULL, L"δ֪����", L"��ʾ", MB_OK);
		return FALSE;
	}

	//4.�����ݿ�
	TCHAR query[128];
	wsprintf(query, L"select * from %s", global_equipment_table);
	this->m_pRst->Open(query, this->m_pMyConnect.GetInterfacePtr(),
		adOpenStatic, adLockOptimistic, adCmdText);// ִ��SQL��䣬�õ���¼��, connection�����Ѻ����ݿ�����
	//5.�������ݣ�д���ļ�
	while (!m_pRst->adoEOF)
	{
		CEquipment equipment;
		lstrcpy(equipment.m_csIntro, ((CString)this->m_pRst->GetCollect(KEY_EQUI_INTRODUCTION)).GetBuffer());
		lstrcpy(equipment.m_csName, ((CString)this->m_pRst->GetCollect(KEY_EQUI_NAME)).GetBuffer());
		equipment.m_iActionSpeed = (int)this->m_pRst->GetCollect(KEY_EQUI_SPEED);
		equipment.m_iCount = (int)this->m_pRst->GetCollect(KEY_EQUI_QUANTITY);
		equipment.m_iCritChance = (int)this->m_pRst->GetCollect(KEY_EQUI_CRITCHANCE);
		equipment.m_iDeyu = (int)this->m_pRst->GetCollect(KEY_EQUI_DEYU);
		equipment.m_iEvdChance = (int)this->m_pRst->GetCollect(KEY_EQUI_EVDCHANCE);
		equipment.m_iMagicAttack = (int)this->m_pRst->GetCollect(KEY_EQUI_MATTACK);
		equipment.m_iMagicDefense = (int)this->m_pRst->GetCollect(KEY_EQUI_MDEFENSE);
		equipment.m_iMaxHP = (int)this->m_pRst->GetCollect(KEY_EQUI_MAXHP);
		equipment.m_iMaxMP = (int)this->m_pRst->GetCollect(KEY_EQUI_MAXMP);
		equipment.m_iPhysicalAttack = (int)this->m_pRst->GetCollect(KEY_EQUI_PATTACK);
		equipment.m_iPhysicalDefense = (int)this->m_pRst->GetCollect(KEY_EQUI_PDEFENSE);
		equipment.m_iTiyu = (int)this->m_pRst->GetCollect(KEY_EQUI_TIYU);
		equipment.m_iZhiyu = (int)this->m_pRst->GetCollect(KEY_EQUI_ZHIYU);
		switch ((int)this->m_pRst->GetCollect(KEY_EQUI_EQUIPMENTTYPE))
		{
		case 0:
			equipment.m_type = CEquipment::ET_WEAPON;
			break;
		case 1:
			equipment.m_type = CEquipment::ET_1;
			break;
		case 2:
			equipment.m_type = CEquipment::ET_2;
			break;
		case 3:
			equipment.m_type = CEquipment::ET_3;
			break;
		case 4:
			equipment.m_type = CEquipment::ET_4;
			break;
		case 5:
			equipment.m_type = CEquipment::ET_5;
			break;
		}

		exportFile.Write((char*)&equipment, sizeof(equipment));
		exportFile.Flush();
		//�ƶ�ָ��
		m_pRst->MoveNext();
	}
	exportFile.Close();
	return TRUE;
}