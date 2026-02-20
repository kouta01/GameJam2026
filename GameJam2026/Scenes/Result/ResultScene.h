#pragma once
#include "DxLib.h"

// リザルト画面を管理するシーンクラス
class ResultScene
{
public:
    ResultScene();  // メンバ変数の初期化

    // スコアと正答数を受け取り、リザルト画面のリソースを読み込む
    void Initialize(int score, int correct);

    // 入力処理やシーン遷移の判定を行う
    void Update();

    // 背景・文字などリザルト画面の描画
    void Draw() const;

    // 読み込んだ画像・音声リソースの解放
    void Finalize();

private:
    // 画像・音声のハンドル
    int background_;  // リザルト背景画像
    int bgm_;         // リザルトBGM
    int se_;          // 決定音などの効果音

    // 表示するスコア情報
    int score_;       // スコア
    int correct_;     // 正答数
};