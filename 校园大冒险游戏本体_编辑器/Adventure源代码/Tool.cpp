#include"Tool.h"

void CTool::Init(TCHAR *name)
{
	m_iCount = 1;
	//m_objectType = OT_TOOL;
	lstrcpy(m_csName, name);
	lstrcpy(m_csIntro, L"不清楚用途的神秘之物");
}

BOOL CTool::LoadData(TCHAR* name)
{
	lstrcpy(m_csName, name);
	ifstream ifs;
	ifs.open(PATH_DAT_TOOL, ios::binary);
	ifs.seekg(0, ios::beg);
	while (!ifs.eof())
	{
		CTool_ tool;
		ifs.read((char*)&tool, sizeof(CTool_));
		if (lstrcmp(name, tool.m_csName) == 0)
		{
			lstrcpy(this->m_csIntro, tool.m_csIntro);
			lstrcpy(this->m_csName, tool.m_csName);
			this->m_iCount = tool.m_iCount;
			ifs.close();
			return TRUE;
		}
	}
	return FALSE;
}
void CTool::Paint(HDC hdc, int x, int y, int cx, int cy)
{
	static BOOL flag = TRUE;
	static HBITMAP m_bitmap;
	if (flag)
	{
		TCHAR str[128];
		wsprintf(str, L"%s%s.bmp", PATH_IMAGE_TOOL, m_csName);
		m_bitmap = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	if (m_bitmap != NULL)
		CGraphHelper::MyTransparentBlt(hdc, m_bitmap, x, y, cx, cy);
}