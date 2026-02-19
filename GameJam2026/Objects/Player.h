#pragma once
#include "Player.h"
#include "QuizManager.h"
#include <DxLib.h>

Player::Player()
    : totalCorrect_(0),
    totalScore_(0)
{
}

void Player::AddFromQuiz(const QuizManager& quiz)
{
    // クイズ終了時にのみ呼ぶ前提（毎フレーム加算防止）
    totalCorrect_ += quiz.GetCorrectCount();
    totalScore_ += quiz.GetScore();
}

void Player::Draw(int x, int y) const
{
    const int color = GetColor(255, 255, 255);

    DrawFormatString(x, y, color, "累計正答数: %d", totalCorrect_);
    DrawFormatString(x, y + 30, color, "累計スコア: %d", totalScore_);
}
