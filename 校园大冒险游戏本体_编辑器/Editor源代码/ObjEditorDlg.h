#pragma once
#include "afxwin.h"
#include"ObjectStruct.h"

// CObjEditorDlg 对话框

class CObjEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CObjEditorDlg)

public:
	CObjEditorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CObjEditorDlg();

// 对话框数据
	enum { IDD = IDD_OBJEDITOR_DIALOG };

private:
	/*物品、道具相关*/
	// 物品名
	CString m_etName;
	// 物品数量
	int m_etCount;
	// 简介
	CString m_etIntro;

	/*药物相关*/
	// 药物恢复HP，可负
	int m_etMediHP;
	// 药物恢复MP，可负
	int m_etMediMP;
	// 药物增加最大生命值，可负
	int m_etMediMaxHP;
	// 增加最大MP，可负
	int m_etMediMaxMP;
	// 增加经验值
	int m_etExp;

	/*装备相关*/
	// 提高生命上限，可负
	int m_etEquiMaxHP;
	// 提高魔法上限，可负
	int m_etEquiMaxMP;
	int m_etZhiyu;
	int m_etTiyu;
	int m_etDeyu;
	int m_etSpeed;
	int m_etPhysicalAttack;
	int m_etPhysicalDefense;
	int m_etMagicAttack;
	int m_etMagicDefense;
	// 暴击率
	int m_etCritChance;
	// 闪避率
	int m_etEvdChance;

	// 从数据库中读取的类型
	CComboBox m_cbLoadType;
	
	void SelMedicine();									//类型选择：药物
	void SelEquipment();								//装备	
	void SelTool();										//道具
	void SetObject();
	void Clear();										//清空面板

	void DisableMedicine();
	void DisableEquipment();
	void SetMedicineData(CMedicine* medicine);
	void SetEquipmentData(CEquipment* equipment);
	void SetToolData(CTool* tool);


	BOOL SaveTool();
	BOOL SaveMedicine();
	BOOL SaveEquipment();

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// 物品类型Combox
	CComboBox m_cbOBJType;
	// 是否可解毒Combox
	CComboBox m_cbUnscramble;
	// 装备类型Combox
	CComboBox m_cbEquipmentType;
	afx_msg void OnCbnSelchangeCbObjtype();
	afx_msg void OnCbnSelchangeCbUnscramble();
	
	afx_msg void OnBnClickedButton2();
	
//	afx_msg void OnBnClickedBtLoad();
	CListBox m_listBox;
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
};
