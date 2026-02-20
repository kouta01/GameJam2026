#include "Qizu.h"

Qizu::Qizu()
{
    Initialize();
}
//初期化処理
void Qizu::Initialize()
{
    current = 0;

    // 正解設定
    int temp[QUESTION_MAX] = { 0,1,0,0,1,0,1,1,1,0 };

    for (int i = 0; i < QUESTION_MAX; i++)
    {
        answer[i] = temp[i];
    }

}

//解答チェック処理
bool Qizu::CheckAnswer(int selectIndex) const
{
    return selectIndex == answer[current];
}

//次の問題へ
void Qizu::NextQuestion()
{
    current++;
}

//終了時処理
bool Qizu::IsFinished() const
{
    return current >= QUESTION_MAX;
}

//現在の問題を確認
int Qizu::GetCurrentQuestion() const
{
    return current;
}