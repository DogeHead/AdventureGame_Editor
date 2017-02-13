#include<windows.h>
#include"GraphHelper.h"
#include"GameUtil.h"
class CSkillAnime{
private:
	TCHAR m_csName[64];									//技能图片名
	int m_iPicCount;								//图片数量
	int m_iAllFrame;								//技能总帧数
	int m_iCurFrame;								//当前帧数
	int m_iEachPicFrame;							//每张图片帧数
public:
	void Init(TCHAR* name, int picCount, int allFrame);
	void Paint(HDC hdc, int x, int y,int cx,int cy);
};