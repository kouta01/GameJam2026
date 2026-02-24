#pragma once
#include "../SceneBase.h"
#include "DxLib.h"

// リザルト画面を管理するシーンクラス
class ResultScene : public SceneBase
{
private:
    // 画像・音声のハンドル
    int background;    // リザルト背景画像
    int resultTitle;   //リザルト名
    int correctTitle;  //正答数名
    int Remainingtime; //残り時間
    int scoreTitle;    //スコア名
    int bgm;           // リザルトBGM
    int se;            // 決定音などの効果音
    int selectbgm;
    int resultTimer;   //経過フレーム
    int resultPhase;   //表示段階
    int newSe;          //正解SE
    int backSe;         //リザルトBボタンSE
    float displayScore; //演出用スコア
    bool isEndSePlayed;  //終了SEを鳴らしたかどうか
    int resultFont;     //リザルト用フォント
    int bigFont;        //黒淵用フォント

    // 表示するスコア情報
    int score;       // スコア
    int correct;     // 正答数

public:
    ResultScene();  // メンバ変数の初期化
    void SetResult(int correctCount, int scoreValue);

private:

    virtual void Initialize() override;    // スコアと正答数を受け取り、リザルト画面のリソースを読み込む
    virtual eSceneType Update() override;  // 入力処理やシーン遷移の判定を行う
    virtual void Draw() const override;    // 背景・文字などリザルト画面の描画
    virtual void Finalize() override;      // 読み込んだ画像・音声リソースの解放

public:
    virtual eSceneType GetNowScene() const override
    {
        return eSceneType::E_RESULT;
    }
};