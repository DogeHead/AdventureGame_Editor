
// MapEditor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMapEditorApp: 
// �йش����ʵ�֣������ MapEditor.cpp
//

class CMapEditorApp : public CWinApp
{
public:
	CMapEditorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMapEditorApp theApp;