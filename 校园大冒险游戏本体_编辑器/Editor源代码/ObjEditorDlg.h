#pragma once
#include "afxwin.h"
#include"ObjectStruct.h"

// CObjEditorDlg �Ի���

class CObjEditorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CObjEditorDlg)

public:
	CObjEditorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CObjEditorDlg();

// �Ի�������
	enum { IDD = IDD_OBJEDITOR_DIALOG };

private:
	/*��Ʒ���������*/
	// ��Ʒ��
	CString m_etName;
	// ��Ʒ����
	int m_etCount;
	// ���
	CString m_etIntro;

	/*ҩ�����*/
	// ҩ��ָ�HP���ɸ�
	int m_etMediHP;
	// ҩ��ָ�MP���ɸ�
	int m_etMediMP;
	// ҩ�������������ֵ���ɸ�
	int m_etMediMaxHP;
	// �������MP���ɸ�
	int m_etMediMaxMP;
	// ���Ӿ���ֵ
	int m_etExp;

	/*װ�����*/
	// ����������ޣ��ɸ�
	int m_etEquiMaxHP;
	// ���ħ�����ޣ��ɸ�
	int m_etEquiMaxMP;
	int m_etZhiyu;
	int m_etTiyu;
	int m_etDeyu;
	int m_etSpeed;
	int m_etPhysicalAttack;
	int m_etPhysicalDefense;
	int m_etMagicAttack;
	int m_etMagicDefense;
	// ������
	int m_etCritChance;
	// ������
	int m_etEvdChance;

	// �����ݿ��ж�ȡ������
	CComboBox m_cbLoadType;
	
	void SelMedicine();									//����ѡ��ҩ��
	void SelEquipment();								//װ��	
	void SelTool();										//����
	void SetObject();
	void Clear();										//������

	void DisableMedicine();
	void DisableEquipment();
	void SetMedicineData(CMedicine* medicine);
	void SetEquipmentData(CEquipment* equipment);
	void SetToolData(CTool* tool);


	BOOL SaveTool();
	BOOL SaveMedicine();
	BOOL SaveEquipment();

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	// ��Ʒ����Combox
	CComboBox m_cbOBJType;
	// �Ƿ�ɽⶾCombox
	CComboBox m_cbUnscramble;
	// װ������Combox
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
