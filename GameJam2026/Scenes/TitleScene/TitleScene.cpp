#include "TitleScene.h"
#include "DxLib.h"

int title_image;
int choice_flag;

void TitleSceneInit(void)
{
    choice_flag = FALSE;
    title_image = LoadGraph("Resource/image/Title.png");
}

void TitleSceneUpdate(void)
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        choice_flag = TRUE;  // éüÇÃÉVÅ[ÉìÇ÷
    }
}

void TitleSceneDraw(void)
{
    DrawGraph(0, 0, title_image, TRUE);
}

void TitleSceneEnd(void)
{
    DeleteGraph(title_image);
}
