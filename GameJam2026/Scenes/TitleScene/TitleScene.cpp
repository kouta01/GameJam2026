#include "TitleScene.h"
#include "DxLib.h"

int x;
int y;

int title_image;
//int cursor_move_title;
//int title_buckground;
int help_image;
int end_image;
int start_sound_title;
//int choice_flag;//プレイ選択画面移行
//int cursor_move_title;
int setumei;

void TitleSceneInit(void)
{
	x = 400;
	y = 325;
	//choice_flag = FALSE;

	//必要な画像の読み込み
	title_image = 
	help_image =
	end_image =
	setumei =


	//必要な音源
    //cursor_move_title = LoadSoundMem
	start_sound_title = LoadSoundMem

	ChangeVolumeSoundMem(180, start_sound_title);
}
