// ObjEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MapEditor.h"
#include "ObjEditorDlg.h"
#include "afxdialogex.h"


// CObjEditorDlg 对话框

IMPLEMENT_DYNAMIC(CObjEditorDlg, CDialogEx)

CObjEditorDlg::CObjEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CObjEditorDlg::IDD, pParent)
	, m_etName(_T(""))
	, m_etCount(0)
	, m_etIntro(_T(""))
	, m_etMediHP(0)
	, m_etMediMP(0)
	, m_etMediMaxHP(0)
	, m_etMediMaxMP(0)
	, m_etExp(0)
	, m_etEquiMaxHP(0)
	, m_etEquiMaxMP(0)
	, m_etZhiyu(0)
	, m_etTiyu(0)
	, m_etDeyu(0)
	, m_etSpeed(0)
	, m_etPhysicalAttack(0)
	, m_etPhysicalDefense(0)
	, m_etMagicAttack(0)
	, m_etMagicDefense(0)
	, m_etCritChance(0)
	, m_etEvdChance(0)
{

}

CObjEditorDlg::~CObjEditorDlg()
{
}

void CObjEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CB_OBJTYPE, m_cbOBJType);
	DDX_Control(pDX, IDC_CB_Unscramble, m_cbUnscramble);
	DDX_Control(pDX, IDC_CB_EQUITYPE, m_cbEquipmentType);
	DDX_Text(pDX, IDC_ET_NAME, m_etName);
	DDX_Text(pDX, IDC_ET_COUNT, m_etCount);
	DDV_MinMaxInt(pDX, m_etCount, 1, 999);
	DDX_Text(pDX, IDC_ET_INTRO, m_etIntro);
	DDX_Text(pDX, IDC_ET_HP, m_etMediHP);
	DDX_Text(pDX, IDC_ET_MP, m_etMediMP);
	DDX_Text(pDX, IDC_ET_MEDIMAXHP, m_etMediMaxHP);
	DDX_Text(pDX, IDC_ET_MEDIMAXMP, m_etMediMaxMP);
	DDX_Text(pDX, IDC_ET_EXP, m_etExp);
	DDX_Text(pDX, IDC_ET_EQUIMAXHP, m_etEquiMaxHP);
	DDX_Text(pDX, IDC_ET_EQUIMAXMP, m_etEquiMaxMP);
	DDX_Text(pDX, IDC_ET_ZHIYU, m_etZhiyu);
	DDX_Text(pDX, IDC_ET_TIYU, m_etTiyu);
	DDX_Text(pDX, IDC_ET_DEYU, m_etDeyu);
	DDX_Text(pDX, IDC_ET_SPEED, m_etSpeed);
	DDX_Text(pDX, IDC_ET_PATTACK, m_etPhysicalAttack);
	DDX_Text(pDX, IDC_ET_PDEFENSE, m_etPhysicalDefense);
	DDX_Text(pDX, IDC_ET_MATTACK, m_etMagicAttack);
	DDX_Text(pDX, IDC_ET_MDEFENSE, m_etMagicDefense);
	DDX_Text(pDX, IDC_ET_CRITCHANCE, m_etCritChance);
	DDX_Text(pDX, IDC_ET_EVDCHANCE, m_etEvdChance);
	DDX_Control(pDX, IDC_COMBO1, m_cbLoadType);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
}


BEGIN_MESSAGE_MAP(CObjEditorDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_CB_OBJTYPE, &CObjEditorDlg::OnCbnSelchangeCbObjtype)
	ON_CBN_SELCHANGE(IDC_CB_Unscramble, &CObjEditorDlg::OnCbnSelchangeCbUnscramble)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjEditorDlg::OnBnClickedButton2)
//	ON_BN_CLICKED(IDC_BT_LOAD, &CObjEditorDlg::OnBnClickedBtLoad)
	ON_LBN_DBLCLK(IDC_LIST1, &CObjEditorDlg::OnLbnDblclkList1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CObjEditorDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON7, &CObjEditorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjEditorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CObjEditorDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CObjEditorDlg 消息处理程序


BOOL CObjEditorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	vector<CString> vec;
	//数据库中读取类型combox初始化
	vec.push_back(L"药物");
	vec.push_back(L"装备");
	vec.push_back(L"道具");

	for (int i = 0; i < vec.size(); ++i)
	{
		m_cbLoadType.AddString(vec[i]);
	}
	//物品类型Combox初始化
	for (int i = 0; i < vec.size(); ++i)
	{
		m_cbOBJType.AddString(vec[i]);
	}

	//是否可解毒初始化
	vec.clear();
	vec.push_back(L"否");
	vec.push_back(L"是");
	for (int i = 0; i < vec.size(); ++i)
	{
		m_cbUnscramble.AddString(vec[i]);
	}

	//装备类型初始化
	vec.clear();
	vec.push_back(L"武器");
	vec.push_back(L"头部");
	vec.push_back(L"身体");
	vec.push_back(L"足部");
	vec.push_back(L"手部");
	vec.push_back(L"配饰");
	for (int i = 0; i < vec.size(); ++i)
	{
		m_cbEquipmentType.AddString(vec[i]);
	}

	m_cbOBJType.SetCurSel(0);
	m_cbUnscramble.SetCurSel(0);
	SelMedicine();

	Clear();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
void CObjEditorDlg::SetObject(){
	GetDlgItem(IDC_ET_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_COUNT)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_INTRO)->EnableWindow(TRUE);
}
void CObjEditorDlg::SelMedicine(){
	DisableEquipment();
	GetDlgItem(IDC_ET_HP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_MP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_MEDIMAXHP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_MEDIMAXMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_EXP)->EnableWindow(TRUE);
	GetDlgItem(IDC_CB_Unscramble)->EnableWindow(TRUE);
}
void CObjEditorDlg::SelEquipment(){
	DisableMedicine();
	GetDlgItem(IDC_ET_EQUIMAXHP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_EQUIMAXMP)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_ZHIYU)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_DEYU)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_TIYU)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_PATTACK)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_PDEFENSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_MATTACK)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_MDEFENSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_SPEED)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_CRITCHANCE)->EnableWindow(TRUE);
	GetDlgItem(IDC_ET_EVDCHANCE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CB_EQUITYPE)->EnableWindow(TRUE);
}
void CObjEditorDlg::SelTool(){
	DisableEquipment();
	DisableMedicine();
}
void CObjEditorDlg::DisableMedicine()
{
	GetDlgItem(IDC_ET_HP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_MP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_MEDIMAXHP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_MEDIMAXMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_EXP)->EnableWindow(FALSE);
	GetDlgItem(IDC_CB_Unscramble)->EnableWindow(FALSE);
}
void CObjEditorDlg::DisableEquipment()
{
	GetDlgItem(IDC_ET_EQUIMAXHP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_EQUIMAXMP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_ZHIYU)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_DEYU)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_TIYU)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_PATTACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_PDEFENSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_MATTACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_MDEFENSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_SPEED)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_CRITCHANCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_ET_EVDCHANCE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CB_EQUITYPE)->EnableWindow(FALSE);
}

void CObjEditorDlg::OnCbnSelchangeCbObjtype()
{
	// TODO:  在此添加控件通知处理程序代码
	const int index = m_cbOBJType.GetCurSel();
	switch (index)
	{
		//药物
	case 0:
		SelMedicine();
		break;
		//装备
	case 1:
		SelEquipment();
		break;
		//道具
	case 2:
		SelTool();
		break;
	}
}


void CObjEditorDlg::OnCbnSelchangeCbUnscramble()
{
	// TODO:  在此添加控件通知处理程序代码
	const int index = m_cbUnscramble.GetCurSel();
	switch (index)
	{
		//否
	case 0:
		
		break;
		//是
	case 1:
		
		break;
	}
}


void CObjEditorDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	switch (m_cbOBJType.GetCurSel())
	{
		//药物
	case 0:
		if(SaveMedicine())
			MessageBox(L"保存药物数据成功");
		break;
		//装备
	case 1:
		if (SaveEquipment())
			MessageBox(L"保存装备数据成功");
		break;
	case 2:
		if (SaveTool())
			MessageBox(L"保存道具数据成功");
		break;
	}
}

BOOL CObjEditorDlg::SaveTool()
{
	
	if (FALSE == UpdateData(TRUE))
		return FALSE;
	if (m_etName == L"")
	{
		MessageBox(L"物品名不可为空");
		return FALSE;
	}
	CTool tool;
	lstrcpy(tool.m_csName, m_etName);
	lstrcpy(tool.m_csIntro, m_etIntro);
	tool.m_iCount = m_etCount;

	CDBHelper dbhelper;
	dbhelper.InitDBHelper();
	if(!dbhelper.SaveTool(&tool))
		return FALSE;
	dbhelper.CoInitDBHelper();
	return TRUE;
}
BOOL CObjEditorDlg::SaveMedicine()
{
	if (FALSE == UpdateData(TRUE))
		return FALSE;
	if (m_etName == L"")
	{
		MessageBox(L"物品名不可为空");
		return FALSE;
	}
	CMedicine medicine;
	medicine.m_bUnscramble = m_cbUnscramble.GetCurSel();			//0为不可解毒，1为可解毒
	
	lstrcpy(medicine.m_csIntro, m_etIntro);
	lstrcpy(medicine.m_csName, m_etName);
	medicine.m_iCount = m_etCount;
	medicine.m_iExp = m_etExp;
	medicine.m_iHP = m_etMediHP;
	medicine.m_iMaxHP = m_etMediMaxHP;
	medicine.m_iMaxMP = m_etMediMaxMP;
	medicine.m_iMP = m_etMediMP;


	CDBHelper dbhelper;
	dbhelper.InitDBHelper();
	if (!dbhelper.SaveMedicine(&medicine))
		return FALSE;
	dbhelper.CoInitDBHelper();
	return TRUE;
}
BOOL CObjEditorDlg::SaveEquipment()
{
	if (FALSE== UpdateData(TRUE))
		return FALSE;
	if (m_etName == L"")
	{
		MessageBox(L"物品名不可为空");
		return FALSE;
	}
	
	CEquipment equipment;
	lstrcpy(equipment.m_csIntro, m_etIntro);
	lstrcpy(equipment.m_csName, m_etName);
	equipment.m_iActionSpeed = m_etSpeed;
	equipment.m_iCount = m_etCount;
	equipment.m_iCritChance = m_etCritChance;
	equipment.m_iDeyu = m_etDeyu;
	equipment.m_iEvdChance = m_etEvdChance;
	equipment.m_iMagicAttack = m_etMagicAttack;
	equipment.m_iMagicDefense = m_etMagicDefense;
	equipment.m_iMaxHP = m_etEquiMaxHP;
	equipment.m_iMaxMP = m_etEquiMaxMP;
	equipment.m_iPhysicalAttack = m_etPhysicalAttack;
	equipment.m_iPhysicalDefense = m_etPhysicalDefense;
	equipment.m_iTiyu = m_etTiyu;
	equipment.m_iZhiyu = m_etZhiyu;
	switch (m_cbEquipmentType.GetCurSel())
	{
	case 0:
		equipment.m_type = CEquipment::ET_WEAPON;					//种类为武器
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

	CDBHelper dbhelper;
	dbhelper.InitDBHelper();
	if (!dbhelper.SaveEquipment(&equipment))
		return FALSE;
	dbhelper.CoInitDBHelper();
	return TRUE;
}
void CObjEditorDlg::Clear()
{
	m_etName = L"";
	m_etCount = 1;
	m_etIntro = L"";
	m_etMediHP = 0;
	m_etMediMP = 0;
	m_etMediMaxHP=0;
	m_etMediMaxMP=0;
	m_etExp=0;
	m_etEquiMaxHP=0;
	m_etEquiMaxMP=0;
	m_etZhiyu=0;
	m_etTiyu=0;
	m_etDeyu=0;
	m_etSpeed=0;
	m_etPhysicalAttack=0;
	m_etPhysicalDefense=0;
	m_etMagicAttack=0;
	m_etMagicDefense=0;
	m_etCritChance=0;
	m_etEvdChance=0;
	
	m_cbUnscramble.SetCurSel(0);
	m_cbEquipmentType.SetCurSel(0);
	m_cbOBJType.SetCurSel(0);
	
	UpdateData(FALSE);
}

void CObjEditorDlg::OnLbnDblclkList1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (m_listBox.GetCurSel() >= 0)
	{
		CString name;
		m_listBox.GetText(m_listBox.GetCurSel(), name);
		CDBHelper dbHelper;
		dbHelper.InitDBHelper();
		switch (m_cbLoadType.GetCurSel())
		{
			//药物
		case 0:
		{
					CMedicine* medicine = dbHelper.LoadMedicine(name);
					if (medicine == NULL)
						break;
					SetMedicineData(medicine);
		}
			break;
			//装备
		case 1:
		{
				  CEquipment* equipment = dbHelper.LoadEquipment(name);
				  if (equipment == NULL)
					  break;
				  SetEquipmentData(equipment);
		}
			break;
			//道具
		case 2:
		{
				  CTool* tool = dbHelper.LoadTool(name);
				  if (tool == NULL)
					  break;
				  SetToolData(tool);
		}
			break;
		}
		dbHelper.CoInitDBHelper();
	}
}


void CObjEditorDlg::OnCbnSelchangeCombo1()
{
	// TODO:  在此添加控件通知处理程序代码
	vector<CString> vec;
	CDBHelper dbhelper;
	dbhelper.InitDBHelper();
	m_listBox.ResetContent();

	switch (m_cbLoadType.GetCurSel())
	{
		//药物
	case 0:
		if (!dbhelper.LoadMedicineNameList(vec))
			MessageBox(L"读取药物信息失败");
		break;
		//装备
	case 1:
		if (!dbhelper.LoadEquipmentNameList(vec))
			MessageBox(L"读取装备信息失败");
		break;
		//道具
	case 2:
		if (!dbhelper.LoadToolNameList(vec))
			MessageBox(L"读取道具信息失败");
		break;
	}
	dbhelper.CoInitDBHelper();

	for (int i = 0; i < vec.size(); ++i)
	{
		m_listBox.AddString(vec[i]);
	}
}
void CObjEditorDlg::SetMedicineData(CMedicine* medicine)
{
	SelMedicine();
	m_cbOBJType.SetCurSel(0);
	m_etName = medicine->m_csName;
	m_etIntro = medicine->m_csIntro;
	m_etCount = medicine->m_iCount;
	m_etMediHP = medicine->m_iHP;
	m_etMediMaxHP = medicine->m_iMaxHP;
	m_etMediMP = medicine->m_iMP;
	m_etMediMaxMP = medicine->m_iMaxMP;
	m_etExp = medicine->m_iExp;
	m_cbUnscramble.SetCurSel(medicine->m_bUnscramble);
	UpdateData(FALSE);
}
void CObjEditorDlg::SetEquipmentData(CEquipment* equipment){
	SelEquipment();
	m_cbOBJType.SetCurSel(1);
	switch (equipment->m_type){
		case CEquipment::ET_WEAPON:
			m_cbEquipmentType.SetCurSel(0);
			break;
		default:
			m_cbEquipmentType.SetCurSel((int)equipment->m_type);
	}
	m_etName = equipment->m_csName;
	m_etIntro = equipment->m_csIntro;
	m_etCount = equipment->m_iCount;
	m_etEquiMaxHP = equipment->m_iMaxHP;
	m_etEquiMaxMP = equipment->m_iMaxMP;
	m_etZhiyu = equipment->m_iZhiyu;
	m_etTiyu = equipment->m_iTiyu;
	m_etDeyu = equipment->m_iDeyu;
	m_etSpeed = equipment->m_iActionSpeed;
	m_etPhysicalAttack = equipment->m_iPhysicalAttack;
	m_etPhysicalDefense = equipment->m_iPhysicalDefense;
	m_etMagicAttack = equipment->m_iMagicAttack;
	m_etMagicDefense = equipment->m_iMagicDefense;
	m_etCritChance = equipment->m_iCritChance;
	m_etEvdChance = equipment->m_iEvdChance;
	UpdateData(FALSE);
}
void CObjEditorDlg::SetToolData(CTool* tool)
{
	SelTool();
	m_cbOBJType.SetCurSel(2);
	m_etName = tool->m_csName;
	m_etIntro = tool->m_csIntro;
	m_etCount = tool->m_iCount;
	UpdateData(FALSE);
}

void CObjEditorDlg::OnBnClickedButton7()
{
	// TODO:  在此添加控件通知处理程序代码
	GetDlgItemText(IDC_ET_NAME, m_etName);
	if (m_etName == L""){
		MessageBox(L"物品名不可为空");
		return;
	}
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();

	switch (m_cbOBJType.GetCurSel())
	{
		//药物
	case 0:
		if (dbHelper.DeleteMedicine(m_etName))
			MessageBox(L"删除成功");
		
		break;
		//装备
	case 1:
		if (dbHelper.DeleteEquipment(m_etName))
			MessageBox(L"删除成功");
		break;
		//道具
	case 2:
		if (dbHelper.DeleteTool(m_etName))
			MessageBox(L"删除成功");
		break;
	}
	OnCbnSelchangeCombo1();
	dbHelper.CoInitDBHelper();
}


void CObjEditorDlg::OnBnClickedButton6()
{
	CDBHelper dbHelper;
	dbHelper.InitDBHelper();
	// TODO:  在此添加控件通知处理程序代码
	switch (m_cbLoadType.GetCurSel())
	{
		//药物
	case 0:
		if (dbHelper.ExportBinaryMedicine())
		{
			MessageBox(L"导出药物二进制文件成功");
			dbHelper.CoInitDBHelper();
		}break;
		//装备
	case 1:
		if (dbHelper.ExportBinaryEquipment())
		{
			MessageBox(L"导出装备二进制文件成功");
			dbHelper.CoInitDBHelper();
		}
		break;
		//道具
	case 2:
		if (dbHelper.ExportBinaryTool())
		{
			MessageBox(L"导出道具二进制文件成功");
			dbHelper.CoInitDBHelper();
		}
		break;
	default:
		MessageBox(L"请先选择一个类型");
		return;
	}
}


void CObjEditorDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	Clear();
}
