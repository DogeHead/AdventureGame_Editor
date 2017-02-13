#pragma once
#include<windows.h>
#include"MapUtil.h"

#define WINWIDTH 595
#define WINHEIGHT 480
#define GAME_FRAME 40

#define EACH_WIDTH 32
#define EACH_HEIGHT 32

//ͼƬ·��
#define PATH_IMAGE L"./pic/"
//����ͼƬ·��
#define PATH_BG L"./pic/bg/"
//����ͼƬ·��
#define PATH_SKILL L"./pic/skill/"
//��Ƶ�ļ�·��
#define PATH_MUSIC L"./wav/"
//��ɫͼƬ·��
#define PATH_IMAGE_CHARACTER L"./pic/character/"
//װ��ͼƬ·��
#define PATH_IMAGE_EQUIPMENT L"./pic/equipment/"
//ҩ��ͼƬ·��
#define PATH_IMAGE_MEDICINE L"./pic/medicine/"
//����ͼƬ·��
#define PATH_IMAGE_TOOL L"./pic/tool/"
//���ߡ�ҩ�װ����Ϣ�ļ�·��
#define PATH_DAT_TOOL L"./dat/tool.dat"
#define PATH_DAT_MEDICINE L"./dat/medicine.dat"
#define PATH_DAT_EQUIPMENT L"./dat/equipment.dat"

//����MSG
#define MSG_TURN_MAIN WM_USER+1000						//�л�����Ϸ������
#define MSG_TURN_PROPERTY_PANNEL WM_USER+1001			//�л��������������
#define MSG_NEW_GAME WM_USER+1002						//��ʼ�µ���Ϸ
#define MSG_FIGHT WM_USER+1003							//����ս��
#define MSG_WIN_FIGHT WM_USER+1004						//ȡ��ս��ʤ��
#define MSG_TURN_OBJ_PANNEL WM_USER+1005				//�л�����Ʒ���

#define WPARAM_KEEP_MUSIC 10

#define MAP_CHARACTER 101
//����
#define CHARACTER_ACTION 4
#define DIR_DOWN 0
#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3

#define MAP_DIVISION	500
#define MAP1_START		500
#define MAP2_START		1000
#define MAP3_START		1500

//���ݿ�
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