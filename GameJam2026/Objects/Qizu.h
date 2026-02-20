#pragma once
//#include "DxLib.h"

#define QUESTION_MAX 10

class Qizu
{
public:
    Qizu();

    void Initialize();      //初期化処理

    bool CheckAnswer(int selectIndex) const; // 正誤判定
    void NextQuestion();                     // 次の問題へ
    bool IsFinished() const;                 // 全問題終了？

    int GetCurrentQuestion() const;          // 今何問目？

private:
    int answer[QUESTION_MAX]; // 正解番号
    int current;              // 現在の問題番号
};