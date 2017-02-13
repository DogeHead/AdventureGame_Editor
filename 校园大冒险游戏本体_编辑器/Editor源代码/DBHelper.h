#include"stdafx.h"
#include<fstream>
using namespace std;
//���ݿ�
#define DB_GAME		L"Game"
//��
#define TB_MAP		L"tb_map"

//��ͼ��
#define KEY_NAME	L"name"
#define KEY_ROW		L"map_row"
#define KEY_COL		L"map_col"
#define KEY_MAP		L"map"

//���߱�
#define KEY_TOOL_NAME L"name"
#define KEY_TOOL_INTRODUCTION L"introduction"
#define KEY_TOOL_QUANTITY L"quantity"
//ҩ���
#define KEY_MEDI_NAME L"name"
#define KEY_MEDI_INTRODUCTION L"introduction"
#define KEY_MEDI_QUANTITY L"quantity"
#define KEY_MEDI_MAXHP L"maxHP"
#define KEY_MEDI_MAXMP L"maxMP"
#define KEY_MEDI_HP L"HP"
#define KEY_MEDI_MP L"MP"
#define KEY_MEDI_EXP L"experience"
#define KEY_MEDI_UNSCRAMBLE L"unscramble"


//װ����
#define KEY_EQUI_NAME L"name"
#define KEY_EQUI_INTRODUCTION L"introduction"
#define KEY_EQUI_QUANTITY L"quantity"
#define KEY_EQUI_EQUIPMENTTYPE L"equipmentType"
#define KEY_EQUI_MAXHP L"maxHP"
#define KEY_EQUI_MAXMP L"maxMP"
#define KEY_EQUI_ZHIYU L"zhiyu"
#define KEY_EQUI_TIYU L"tiyu"
#define KEY_EQUI_DEYU L"deyu"
#define KEY_EQUI_PATTACK L"physicalAttack"
#define KEY_EQUI_PDEFENSE L"physicalDefense"
#define KEY_EQUI_MATTACK L"magicAttack"
#define KEY_EQUI_MDEFENSE L"magicDefense"
#define KEY_EQUI_CRITCHANCE L"critChance"
#define KEY_EQUI_EVDCHANCE L"evdChance"
#define KEY_EQUI_SPEED L"speed"
class CDBHelper
{
private:
	_ConnectionPtr m_pMyConnect;
	_RecordsetPtr m_pRst;

public:
	CDBHelper();
	~CDBHelper();
	void InitDBHelper();												//�������ݿ�ǰ����
	void CoInitDBHelper();												//�����ϲ�����Ϻ����

	//�������ݵ����ݿ�
	BOOL SaveMap(CString mapName, int row, int col, int *map);			//�����ͼ
	BOOL SaveTool(CTool* tool);
	BOOL SaveMedicine(CMedicine* medicine);
	BOOL SaveEquipment(CEquipment* equipment);

	//�����ݿ��ж�ȡ����
	BOOL GetMapNameList(vector<CString>& vec);
	BOOL LoadMedicineNameList(vector<CString>& vec);
	BOOL LoadEquipmentNameList(vector<CString>& vec);
	BOOL LoadToolNameList(vector<CString>& vec);

	CMedicine* LoadMedicine(CString name);
	CEquipment* LoadEquipment(CString name);
	CTool* LoadTool(CString name);
	int* LoadMap(CString csMapName,int &row, int &col);					//�Ե�ͼ��Ϊ��־�����ݿ��ж�ȡ��ͼ.����һά����
	int *GetMap(int row, int col, CString cs_map);						//���ַ�����ʾ�ĵ�ͼת��Ϊһά����

	//�����ݿ���ɾ������
	BOOL DeleteMap(CString name);
	BOOL DeleteTool(CString name);
	BOOL DeleteMedicine(CString name);
	BOOL DeleteEquipment(CString name);

	BOOL ExportBinaryTool();
	BOOL ExportBinaryMedicine();
	BOOL ExportBinaryEquipment();
	BOOL OpenFileDlg(CString& path);
};