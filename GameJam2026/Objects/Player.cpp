#include "Player.h"

Player::Player() :totalCorrect_(0), totalScore_(0)
{
}

void Player::AddCorrent()
{
	totalCorrect_++;
}

void Player::AddScore(int score)
{
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