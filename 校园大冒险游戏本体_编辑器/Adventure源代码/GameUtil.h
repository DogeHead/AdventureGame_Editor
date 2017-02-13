#pragma once
#include<windows.h>
#include"MapUtil.h"

#define WINWIDTH 595
#define WINHEIGHT 480
#define GAME_FRAME 40

#define EACH_WIDTH 32
#define EACH_HEIGHT 32

//图片路径
#define PATH_IMAGE L"./pic/"
//背景图片路径
#define PATH_BG L"./pic/bg/"
//技能图片路径
#define PATH_SKILL L"./pic/skill/"
//音频文件路径
#define PATH_MUSIC L"./wav/"
//角色图片路径
#define PATH_IMAGE_CHARACTER L"./pic/character/"
//装备图片路径
#define PATH_IMAGE_EQUIPMENT L"./pic/equipment/"
//药物图片路径
#define PATH_IMAGE_MEDICINE L"./pic/medicine/"
//道具图片路径
#define PATH_IMAGE_TOOL L"./pic/tool/"
//道具、药物、装备信息文件路径
#define PATH_DAT_TOOL L"./dat/tool.dat"
#define PATH_DAT_MEDICINE L"./dat/medicine.dat"
#define PATH_DAT_EQUIPMENT L"./dat/equipment.dat"

//各种MSG
#define MSG_TURN_MAIN WM_USER+1000						//切换到游戏主界面
#define MSG_TURN_PROPERTY_PANNEL WM_USER+1001			//切换到人物属性面板
#define MSG_NEW_GAME WM_USER+1002						//开始新的游戏
#define MSG_FIGHT WM_USER+1003							//进入战斗
#define MSG_WIN_FIGHT WM_USER+1004						//取得战斗胜利
#define MSG_TURN_OBJ_PANNEL WM_USER+1005				//切换到物品面板

#define WPARAM_KEEP_MUSIC 10

#define MAP_CHARACTER 101
//方向
#define CHARACTER_ACTION 4
#define DIR_DOWN 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3

#define MAP_DIVISION	500
#define MAP1_START		500
#define MAP2_START		1000
#define MAP3_START		1500

//数据库
#define DB_GAME		L"Game"
#define TB_MAP		L"tb_map"
#define KEY_NAME	L"name"
#define KEY_ROW		L"map_row"
#define KEY_COL		L"map_col"
#define KEY_MAP		L"map"

#define MAX_BUFF 5000

#define MAP_BLACK 0
struct MapInfo
{
	int m_row, m_col;
	TCHAR m_mapName[64];
	int m_map[10001];
};