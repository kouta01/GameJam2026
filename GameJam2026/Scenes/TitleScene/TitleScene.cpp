#include "TitleScene.h"
#include "DxLib.h"

int x;
int y;

int title_image;
int choice_flag;

//int title_bgm;
//int decision_se;

void TitleSceneInit(void)
{
    choice_flag = FALSE;
    title_image = LoadGraph("Resource/image/Title.png");

    //title_bgm = LoadSoundMem("Resource/sound/");
    //decision_se = LoadSoundMem("Resource/sound/");

    // 音量設定
    //ChangeVolumeSoundMem(180, title_bgm);
    //ChangeVolumeSoundMem(255, decision_se);

    // BGM再生（ループ）
    //PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP);
}

/*void TitleSceneUpdate(void)
{
    if (choice_flag == TRUE)
    {
        //Bボタンが押された場合
        if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
        {

        }
        if (y == -10)
        {
            //Aボタンが押された場合
            if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
            {

            }
        }
        else if (y == 200)
        {
            //Aボタンが押された場合
            if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
            {

            }
        }
    }
}*/

void TitleSceneDraw(void)
{
    DrawGraph(0, 0, title_image, TRUE);
}

void TitleSceneEnd(void)
{
    //StopSoundMem(title_bgm);

    DeleteGraph(title_image);
    //DeleteSoundMem(title_bgm);
    //DeleteSoundMem(decision_se);

}
