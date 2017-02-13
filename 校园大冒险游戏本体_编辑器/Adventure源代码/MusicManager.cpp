#include"MusicManager.h"

void CMusicManager::PlayMusicLoop(int musicNum)
{
	TCHAR fileName[64];
	switch (musicNum)
	{
	case MS_BATTLE_C12:
		lstrcpy(fileName, L"battle");
		break;
	case MS_MAIN_C12:
		lstrcpy(fileName, L"map_c12");
		break;
	case MS_MENU:
	default:
		lstrcpy(fileName, L"menu");
	}
	TCHAR path[128];
	wsprintf(path,L"%s%s.wav",PATH_MUSIC, fileName);
	if (!PlaySound(path, GetModuleHandle(0), SND_ASYNC | SND_FILENAME | SND_LOOP))
	{
		MessageBox(NULL, L"fail", L"music", MB_OK);
	}
}

void CMusicManager::StopMusic()
{
	PlaySound(NULL, NULL, SND_PURGE);
}