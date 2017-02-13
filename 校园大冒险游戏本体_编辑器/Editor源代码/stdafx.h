
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
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


