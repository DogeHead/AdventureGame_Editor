#include"Background.h"

class CKickedOffBackground :public CBackground
{
private:
	int m_iAllFrame,
		m_iCurFrame;
public:
	CKickedOffBackground();

	void Init(int frame, TCHAR* name);
	void Paint(HDC hdc, RECT rc);
	void Update();
};