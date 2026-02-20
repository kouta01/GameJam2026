#include "ResultScene.h"

ResultScene::ResultScene()
    : background(-1)
    ,resultTitle(0)
    ,bgm(-1)
    ,se(-1)
{
    // メンバ変数の初期化
}

void ResultScene::SetResult(int correctCount, int scoreValue)
{
    correct = correctCount;
    score = scoreValue;
}

void ResultScene::Initialize()
{
    // 前シーンから受け取ったスコアと正答数を保存


    // リザルト画面の背景画像・BGM・効果音を読み込み
    background = LoadGraph("Resource/images/result.png");
    resultTitle = LoadGraph("Resource/Image/ResultTitle.png");
    bgm = LoadSoundMem("Resource/sound/result_bgm.mp3");
    se = LoadSoundMem("Resource/sound/se.wav");

    // 読み込み失敗チェック
    if (background == -1) MessageBox(NULL, "result.pngがありません", "Error", MB_OK);
    if (resultTitle == -1) MessageBox(NULL, "ResultTitle.pngがありません", "Error", MB_OK);
    if (bgm == -1)        MessageBox(NULL, "BGMがありません", "Error", MB_OK);

    // BGMをループ再生
    PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

eSceneType ResultScene::Update()
{
    // Bボタンが押されたらタイトルへ戻る処理
    if (CheckHitKey(KEY_INPUT_B))
    {
        PlaySoundMem(se, DX_PLAYTYPE_BACK); // 決定音
        StopSoundMem(bgm);                  // BGM停止

        // SceneManagerでタイトルシーンへ切り替える処理をここに書く
    }

    return GetNowScene();
}

void ResultScene::Draw() const
{
    // 背景画像の描画
    DrawGraph(0, 0, background, TRUE);

    DrawGraph(0, 0, resultTitle, TRUE);

    // 結果表示用のボックス
    DrawBox(150, 150, 490, 330, GetColor(200, 100, 0), TRUE);

    //正答数の表示
    DrawFormatString(180, 180, 0xffffff, "正当数 : %d", correct);

    //スコアの表示
    DrawFormatString(180, 350, 0xffffff, "スコア : %d", score);
}

void ResultScene::Finalize()
{
    // 読み込んだ画像・音声データを解放
    DeleteGraph(background);
    DeleteGraph(resultTitle);
    DeleteSoundMem(bgm);
    DeleteSoundMem(se);
}