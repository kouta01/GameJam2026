#include "Player.h"
#include "QuizManager.h"

Player::Player()
    : totalCorrect_(0),
    totalScore_(0)
{
    // 明示的初期化：将来的な未初期化バグ防止
}

void Player::AddFromQuiz(const QuizManager& quiz)
{
    // クイズ終了時にのみ呼ぶ前提
    // 毎フレーム呼ぶとスコアが無限加算されるため注意
    totalCorrect_ += quiz.GetCorrectCount();
    totalScore_ += quiz.GetScore();
}

void Player::Draw(int x, int y) const
{
    // 描画色を固定（将来テーマ変更時はここを変更すれば良い）
    const int color = GetColor(255, 255, 255);

    // UI位置を引数化しているため、画面レイアウト変更に強い
    DrawFormatString(x, y, color, "累計正答数: %d", totalCorrect_);
    DrawFormatString(x, y + 30, color, "累計スコア: %d", totalScore_);
}
