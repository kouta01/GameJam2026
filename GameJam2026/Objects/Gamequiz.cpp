#include "Gamequiz.h"
#include "DxLib.h"

static int selectIndex;   //‘I‘ğ‚µ‚Ä‚¢‚é”Ô†
static int correctIndex;  //³‰ğ‚Ì”Ô†
static bool answered;     //‰ñ“š
static bool isCorrect;    //³‰ğ”»’è

void QuizSceneInit(void)
{
    selectIndex = 0;
    correctIndex = 0;     //0 = ‚ª³‰ğ
    answered = false;
    isCorrect = false;
}

void QuizSceneUpdate(void)
{
    if (answered) return;

    if(CheckHitKey(KEY_INPUT_LEFT))
        selectIndex = 0;

    if (CheckHitKey(KEY_INPUT_RIGHT))
        selectIndex = 1;
}

void QuizSceneDraw(void)
{
    DrawString(400, 150, "y–â‘èz³‚µ‚¢Š¿š‚Í‚Ç‚Á‚¿H", GetColor(255, 255, 255));

    DrawString(50, 400, "", GetColor(255, 255, 255));
    DrawString(-450, 400, "", GetColor(255, 255, 255));

    if (answered)
    {
        if (isCorrect)
            DrawString(0, 0, "³‰ğ", GetColor(0, 255, 0));
        else
            DrawString(0, 0, "•s³‰ğ", GetColor(255, 0, 0));
    }
}

bool QuizSceneIsEnd(void)
{
    return answered;
}

bool QuizSceneIsCorrect(void)
{
    return isCorrect;
}