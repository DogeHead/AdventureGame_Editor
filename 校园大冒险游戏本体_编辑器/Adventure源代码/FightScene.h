#include<windows.h>
#include<time.h>
#include"Background.h"
#include"KickedOffBackground.h"
#include"MainCharacter.h"
#include"Monster.h"
#include"SkillAnime.h"
#include"GameUtil.h"
class CFightScene
{
private:
	//ս��״̬:ս��������ս���У�ս������
	enum FightState{FS_OVER,FS_FIGHT,FS_LOADING};
	
	FightState m_fsState;			//��ǰ״̬
	RECT m_rcClient;				//��Ļ����
	int m_iFrame;					//��ǰ֡
	int m_iMapNum;					//��ǰ��ͼ���
	//ָ������
	enum CmdState{CS_CMD,CS_SELMON,};

	const int maxMonNum = MAX_MONCOUNT;//����������
	CMonster m_mon[MAX_MONCOUNT];	//����ս��������Ϣ
	CMainCharacter* m_mc;			//����ս��������Ϣ
	int m_iMcCount;					//����ս����������

	CBackground m_bg;				//����
	CSkillAnime m_skillAnime;		//���ܶ���
	//��ȡ�׶�
	CKickedOffBackground m_koBg;	//�ҿ���Ļ�ı���
	int m_iLoadingFrame;			//��ȡ֡��

	//ս���н׶�
	int m_iActionTurn[MAX_MONCOUNT + MAX_MCCOUNT];		//����˳��
	int m_iMonCount;				//����ս����������
	POINT m_ptMonPos[5];			//��������λ��
	RECT m_rcChaPos[5];				//���ǵ����λ��
	int m_iFrameNum;				//��ǰλ�ڵڼ�֡
	int m_iCurActionNum;			//��ǰ�ֵ��ڼ�������

	//ָ��׶�
	CmdState m_cmdState;			//����ָ��
	BOOL m_bIsCmd;					//����ָ��׶�
	int m_iCurCmd;					//��ǰѡ��ָ��
	RECT m_rcCmd;					//ָ������
	TCHAR m_csCmd[4][16];			//ָ��
	RECT m_rcEachCmd[4];			//����ָ������
	RECT m_rcMcState[5];			//����״̬�������
	int m_iSelMon;					//��ǰѡ������

	//�����׶�
	int money,
		exp;


	HWND m_hWnd;
	
	void paintLoading(HDC hdc);		//���ƶ�ȡ����
	void paintGameOver(HDC hdc);
	void paintFight(HDC hdc);

	void upateLoading();
	void upateGameOver();
	void upateFight();

	void handleLoading();
	void handleGameOver();
	void handleFight();

	void Exit();					//����
	void WinFight();				//Ӯ��ս��
	void InitActionTurn();			//��ʼ������˳��
	BOOL IsGameOver();
	void ClearShow();				//����ܵ��˺���ʾ
public:
	void Init(HWND hwnd,RECT* rc,int mapNum,CMainCharacter* mc);
	
	void Paint(HDC hdc);
	void Handle();
	void Update();
	void randMon(int mapNum);//����m_iMapNum���ɹ���
};