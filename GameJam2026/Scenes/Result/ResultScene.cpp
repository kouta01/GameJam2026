// ResultScene.cpp
#include "ResultScene.h"

ResultScene::ResultScene()
    : background_(-1),
    bgm_(-1),
    se_(-1),
    score_(0),
    correct_(0)
{
    // メンバ変数の初期化
}

void ResultScene::Initialize(int score, int correct)
{
    // 前シーンから受け取ったスコアと正答数を保存
    score_ = score;
    correct_ = correct;

    // リザルト画面の背景画像・BGM・効果音を読み込み
    background_ = LoadGraph("Resource/images/result.png");
    bgm_ = LoadSoundMem("Resource/sound/result_bgm.mp3");
    se_ = LoadSoundMem("Resource/sound/se.wav");

    // 読み込み失敗チェック
    if (background_ == -1) MessageBox(NULL, "result.pngがありません", "Error", MB_OK);
    if (bgm_ == -1)        MessageBox(NULL, "BGMがありません", "Error", MB_OK);

    // BGMをループ再生
    PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
}

eSceneType ResultScene::Update()
{
    // Bボタンが押されたらタイトルへ戻る処理
    if (CheckHitKey(KEY_INPUT_B))
    {
        PlaySoundMem(se_, DX_PLAYTYPE_BACK); // 決定音
        StopSoundMem(bgm_);                  // BGM停止

        // SceneManagerでタイトルシーンへ切り替える処理をここに書く
    }

    return GetNowScene();
}

void ResultScene::Draw() const
{
    // 背景画像の描画
    DrawGraph(0, 0, background_, TRUE);

    // 結果表示用のボックス
    DrawBox(150, 150, 490, 330, GetColor(200, 100, 0), TRUE);

    // タイトル文字
    DrawString(200, 100, "RESULT", 0xffffff);

    // 正答数とスコアの表示
    DrawFormatString(200, 200, 0xffffff,
        "正答数 : %d", correct_);

    DrawFormatString(200, 230, 0xffffff,
        "スコア : %d", score_);
}

void ResultScene::Finalize()
{
    // 読み込んだ画像・音声データを解放
    DeleteGraph(background_);
    DeleteSoundMem(bgm_);
    DeleteSoundMem(se_);
}