#include<windows.h>
#include <mmsystem.h>
#include"GameUtil.h"
#pragma comment(lib, "WINMM.LIB")
#define MS_BATTLE_C12 1
#define MS_MENU 2
#define MS_MAIN_C12	3

class CMusicManager{


public:
	void PlayMusicLoop(int musicNum);

	void StopMusic();
};