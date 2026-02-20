#include "ResultScene.h"
#include "../../Utility/InputManager.h"   

ResultScene::ResultScene()
    : background(-1)
    ,resultTitle(0)
    ,correctTitle(0)
    ,scoreTitle(0)
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
    correctTitle = LoadGraph("Resource/Image/Result1.png");
    scoreTitle = LoadGraph("Resource/Image/Result2.png");
    bgm = LoadSoundMem("Resource/sound/result_bgm.mp3");
    se = LoadSoundMem("Resource/sound/se.wav");

    // 読み込み失敗チェック
    if (background == -1) MessageBox(NULL, "result.pngがありません", "Error", MB_OK);
    if (resultTitle == -1) MessageBox(NULL, "ResultTitle.pngがありません", "Error", MB_OK);
    if (correctTitle == -1) MessageBox(NULL, "correctTitle.pngがありません", "Error", MB_OK);
    if (scoreTitle == -1) MessageBox(NULL, "sscoreTitle.pngがありません", "Error", MB_OK);
    if (bgm == -1)        MessageBox(NULL, "BGMがありません", "Error", MB_OK);

    // BGMをループ再生
    PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

eSceneType ResultScene::Update()
{
    InputManager* input = InputManager::GetInstance();

    if (input->GetButtonDown(PAD_B))
    {
        PlaySoundMem(se, DX_PLAYTYPE_BACK);
        StopSoundMem(bgm);
        return eSceneType::E_TITLE;
    }


    return GetNowScene();
}

void ResultScene::Draw() const
{
    // 背景画像の描画
    DrawGraph(0, 0, background, TRUE);
    //タイトル名
    DrawGraph(0, 0, resultTitle, TRUE);
    //正答数名
    DrawGraph(180, 180, correctTitle, TRUE);
    //スコア名
    DrawGraph(180, 350, scoreTitle, TRUE);

    //// 結果表示用のボックス
    //DrawBox(150, 150, 490, 330, GetColor(200, 100, 0), TRUE);

    //正答数の表示
    DrawFormatString(710, 180, 0xffffff, "%d", correct);

    //スコアの表示
    DrawFormatString(660, 350, 0xffffff, "%d", score);
}

void ResultScene::Finalize()
{
    // 読み込んだ画像・音声データを解放
    DeleteGraph(background);
    DeleteGraph(resultTitle);
    DeleteSoundMem(bgm);
    DeleteSoundMem(se);
}