#pragma once
#include "DxLib.h"

class Player
{
public:
    Player();

    void AddResult(int correct, int score);
    void Reset();

    void Draw(int x, int y) const;

    int GetTotalCorrect() const;
    int GetTotalScore() const;

private:
    int totalCorrect_;
    int totalScore_;
};