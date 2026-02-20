#include "Qizu.h"

Qizu::Qizu()
{
    Initialize();
}

void Qizu::Initialize()
{
    current = 0;

    // ³‰ðÝ’èi—áj
    answer[0] = 0;
    answer[1] = 1;
    answer[2] = 0;
    answer[3] = 0;
    answer[4] = 1;
    answer[5] = 0;
    answer[6] = 1;
    answer[7] = 1;
    answer[8] = 1;
    answer[9] = 0;

}

bool Qizu::CheckAnswer(int selectIndex) const
{
    return selectIndex == answer[current];
}

void Qizu::NextQuestion()
{
    current++;
}

bool Qizu::IsFinished() const
{
    return current >= QUESTION_MAX;
}

int Qizu::GetCurrentQuestion() const
{
    return current;
}