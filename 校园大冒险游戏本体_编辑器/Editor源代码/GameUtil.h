#pragma once
#include<windows.h>

#define MAX_BUFF 5000

#define EACH_WIDTH 32
#define EACH_HEIGHT 32

#define MAP_DIVISION	500
#define MAP1_START		500
#define MAP2_START		1000
#define MAP3_START		1500

#define MAP_BLACK 0

struct MapInfo
{
	int m_row, m_col;
	TCHAR m_mapName[64];
	int m_map[10001];
};