#pragma once

class Player
{
public:
    Player();

    void AddCorrent();      //‚P–â³‰ğ
    void AddScore(int score);   //³“š”

    void Reset();

    int GetTotalCorrect() const;
    int GetTotalScore() const;

private:
    int totalCorrect_;
    int totalScore_;
};