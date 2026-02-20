// ResultScene.cpp
#include "ResultScene.h"

ResultScene::ResultScene()
    : background_(-1),
      bgm_(-1),
      se_(-1),
      score_(0),
      correct_(0)
{
}

void ResultScene::Initialize(int score, int correct)
{
    score_   = score;
    correct_ = correct;

    background_ = LoadGraph("Resource/images/result.png");
    bgm_ = LoadSoundMem("Resource/sound/result_bgm.mp3");
    se_  = LoadSoundMem("Resource/sound/se.wav");

    if (background_ == -1) MessageBox(NULL, "result.pngがありません", "Error", MB_OK);
    if (bgm_ == -1) MessageBox(NULL, "BGMがありません", "Error", MB_OK);

    PlaySoundMem(bgm_, DX_PLAYTYPE_LOOP);
}

void ResultScene::Update()
{
    // Bボタンでタイトルへ
    if (CheckHitKey(KEY_INPUT_B))
    {
        PlaySoundMem(se_, DX_PLAYTYPE_BACK);
        StopSoundMem(bgm_);
        // SceneManagerでタイトルに切替
    }
}

void ResultScene::Draw() const
{
    DrawGraph(0, 0, background_, TRUE);

    DrawBox(150,150,490,330, GetColor(200,100,0), TRUE);

    DrawString(200, 100, "RESULT", 0xffffff);

    DrawFormatString(200, 200, 0xffffff,
        "正答数 : %d", correct_);

    DrawFormatString(200, 230, 0xffffff,
        "スコア : %d", score_);
}

void ResultScene::Finalize()
{
    DeleteGraph(background_);
    DeleteSoundMem(bgm_);
    DeleteSoundMem(se_);
}