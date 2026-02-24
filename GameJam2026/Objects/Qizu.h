#pragma once
//#include "DxLib.h"

#define QUESTION_MAX 10
/*例 列挙型で名前付け*/

//enum eQuestion {
//    question1,
//    question2,
//    question3,
//    question4,
//
//};

class Qizu
{
protected:
    //eQuestion type;       //オブジェクトの名前付け
public:
    Qizu();

    void Initialize();      //初期化処理

    bool CheckAnswer(int selectIndex) const; //正誤判定
    void NextQuestion();                     //次の問題へ
    bool IsFinished() const;                 //全問題終了？

    int GetCurrentQuestion() const;          //今何問目？

private:
    int answer[QUESTION_MAX]; //正解番号
    int current;              //現在の問題番号
};