#pragma once
#include "DxLib.h"

#define QUESTION_MAX 2

class Qizu
{
public:
    Qizu();
    void Load();
    void Update();
    void Draw();

private:
    int questionImg[QUESTION_MAX];
    int hintImg[QUESTION_MAX];
    int choiceImg[QUESTION_MAX][2];
    int answer[QUESTION_MAX];

    int current;        //‰½–â‚©
    int selectIndex;    //‘I‚ñ‚Å‚¢‚é‘I‘ðŽˆ
    bool answered;      //“š‚¦‚½‚©‚Ç‚¤‚©

};
