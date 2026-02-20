#include "Player.h"

Player::Player()
    : totalCorrect_(0),
      totalScore_(0)
{
}

void Player::AddResult(int correct, int score)
{
    totalCorrect_ += correct;
    totalScore_ += score;
}

void Player::Reset()
{
    totalCorrect_ = 0;
    totalScore_ = 0;
}

int Player::GetTotalCorrect() const
{
    return totalCorrect_;
}

int Player::GetTotalScore() const
{
    return totalScore_;
}

void Player::Draw(int x, int y) const
{
    const int color = GetColor(255, 255, 255);

    DrawFormatString(x, y, color,
        "累計正答数: %d", totalCorrect_);

    DrawFormatString(x, y + 30, color,
        "累計スコア: %d", totalScore_);
}