#include<windows.h>
#include"GraphHelper.h"
#include"GameUtil.h"
class CSkillAnime{
private:
	TCHAR m_csName[64];									//����ͼƬ��
	int m_iPicCount;								//ͼƬ����
	int m_iAllFrame;								//������֡��
	int m_iCurFrame;								//��ǰ֡��
	int m_iEachPicFrame;							//ÿ��ͼƬ֡��
public:
	void Init(TCHAR* name, int picCount, int allFrame);
	void Paint(HDC hdc, int x, int y,int cx,int cy);
};