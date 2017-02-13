
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include<windows.h>

#import "msado15.dll" \
	no_namespace \
	rename("EOF","adoEOF")

#include<vector>
using namespace std;
#include"GameUtil.h"
#include"ObjectStruct.h"
#include"resource.h"
//#include "afxwin.h"

#include"DBHelper.h"
#include"DBSettingDlg.h"
#include"MainDlg.h"
#include "MapEditor.h"
#include"MapListDlg.h"
#include"MapEditorDlg.h"


/*
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#endif
*/
#define DEFAULT_PROVIDER L"SQLOLEDB"
#define DEFAULT_DATASOURCE L"LENOVO-PC"
#define DEFAULT_DATABASE L"Game"
#define DEFAULT_IS L"SSPI"
#define DEFAULT_TB L"tb_map"
#define DEFAULT_TOOL_TB L"tb_tool"
#define DEFAULT_EQUIPMENT_TB L"tb_equipment"
#define DEFAULT_MEDICINE_TB L"tb_medicine"

#define KEY_PROVIDER L"Provider"
#define KEY_DATASOURCE L"DataSource"
#define KEY_DATABASE L"DataBase"
#define KEY_IS L"Integrated Security"


#define DATABASE_INI_PATH L".\\DataBaseSetting.ini"
#define INI_NAME L"Setting"

extern CString global_provider;
extern CString global_dataSource;
extern CString global_database;
extern CString global_integratedSecurity;
extern CString global_table;
extern CString global_tool_table;
extern CString global_equipment_table;
extern CString global_medicine_table;


