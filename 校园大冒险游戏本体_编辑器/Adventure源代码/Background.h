#pragma once
#include<windows.h>
#include<stdio.h>
#include"GameUtil.h"
#include"GraphHelper.h"
#include"resource.h"
#pragma comment(lib, "Msimg32.lib")

#define BG_0 L"bg"
#define BG_1 L"bg1"
#define KOBG_0 L"fight_pic1"
#define BG_ObjectPannel L"bg_obj"
#define BG_MENU L"bg_menu"

class CBackground{
protected:
	TCHAR m_csName[64];
	HBITMAP m_bitmap;
public:
	void Init(TCHAR* name);
	void Paint(HDC hdc,RECT rc);
};