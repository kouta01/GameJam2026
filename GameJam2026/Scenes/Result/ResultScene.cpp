#include "ResultScene.h"
#include"../../Scenes/GameMainScene/GameMainScene.h"
#include "../../Utility/InputManager.h"   

ResultScene::ResultScene()
    : background(-1)
    ,resultTitle(0)
    ,correctTitle(0)
    ,Remainingtime(0)
    ,scoreTitle(0)
    ,bgm(0)
    ,se(-1)
    ,resultTimer(0)
    ,resultPhase(-1)
    ,displayScore(0.0f)
    ,isEndSePlayed(false)
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
    //background = LoadGraph("Resource/images/result.png");
    resultTitle = LoadGraph("Resource/Image/Result.png");
    correctTitle = LoadGraph("Resource/Image/Result1.png");
    scoreTitle = LoadGraph("Resource/Image/Result2.png");
    Remainingtime =LoadGraph("Resource/Image/Result3.png");
    bgm = LoadSoundMem("Resource/Sounds/nc260619.mp3");
    se = LoadSoundMem("Resource/sound/se.wav");
    newSe = LoadSoundMem("Resource/Sounds/score.mp3");
    backSe = LoadSoundMem("Resource/Sounds/kuizuend.mp3");

    // 読み込み失敗チェック
    //if (background == -1) MessageBox(NULL, "result.pngがありません", "Error", MB_OK);
    if (resultTitle == -1) MessageBox(NULL, "ResultTitle.pngがありません", "Error", MB_OK);
    if (correctTitle == -1) MessageBox(NULL, "correctTitle.pngがありません", "Error", MB_OK);
    if(Remainingtime == -1) MessageBox(NULL, "Remainingtime.pngがありません", "Error", MB_OK);
    if (scoreTitle == -1) MessageBox(NULL, "sscoreTitle.pngがありません", "Error", MB_OK);
    if (bgm == -1)        MessageBox(NULL, "BGMがありません", "Error", MB_OK);

}

eSceneType ResultScene::Update()
{
    // InputManagerのインスタンスを取得
    InputManager* input = InputManager::GetInstance();

    resultTimer++;

    //60フレームごとに次の次の段階へ(１秒)
    //正答数、残り時間だけスムーズに実行
    if (resultPhase < 2)
    {
        if (resultTimer > 60)
        {
                resultPhase++;
                resultTimer = 0;

                //SEを鳴らす
                PlaySoundMem(newSe, DX_PLAYTYPE_BACK);

        }
    }

    
    //スコア表示タイミグでカウントアップ演出をはさむ
    if (resultPhase == 2)
    {
        float target = GameMainScene::GetFinalScore();

        if (displayScore < target)
        {
            PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
            displayScore += 0.1f;   // 増えるスピード調整可
            

            if (displayScore > target)
                displayScore = target;
        }
        else
        {

            resultPhase = 3;
            //PlaySoundMem(newSe, DX_PLAYTYPE_BACK);
            
        }
    }
    // 「Bボタンでタイトルへ」が表示される段階
    if (resultPhase >= 3 && !isEndSePlayed)
    {
        PlaySoundMem(backSe, DX_PLAYTYPE_BACK);  // 音を鳴らす
        isEndSePlayed = true;                   // 鳴らした記録を残す
    }
    // Bボタンが押された瞬間を検出
    if (input->GetButtonDown(PAD_B))
    {
        // タイトルシーンへ遷移する
        return eSceneType::E_TITLE;
    }

    // 何も押されていない場合は
    // 現在のResultシーンを維持する
    return GetNowScene();
}

void ResultScene::Draw() const
{
    // 背景画像の描画
    DrawGraph(0, 0, background, TRUE);
    //タイトル名
    DrawGraph(0, 0, resultTitle, TRUE);
    //正答数名
    DrawGraph(180, 166, correctTitle, TRUE);
    //残り時間
    DrawGraph(180, 339, Remainingtime, TRUE);
    //スコア名
    DrawGraph(180, 485, scoreTitle, TRUE);

    //// 結果表示用のボックス
    //DrawBox(150, 150, 490, 330, GetColor(200, 100, 0), TRUE);

    if (resultPhase >= 0)//正答数の表示
    {
        DrawFormatString(590, 180, 0xffffff, "%d", correct);

    }

    if (resultPhase >= 1)//残り時間
    {
        DrawFormatString(590, 360, 0xffffff, "%d", 
         GameMainScene::GetFinalRemainingSeconds());
    }

    if (resultPhase >= 2) //スコアの表示
    {
        DrawFormatString(550, 500, 0xffffff, "%.1f", 
         displayScore);
    }

    if (resultPhase >= 3)
    {
        if (GameMainScene::IsNewRecord())
        {
            if ((GetNowCount() / 500) % 2 == 0)
            {
                DrawString(760, 500, "NEW RECORD!", 0xffd700);
            }
        }
        DrawString(250, 610, "Bボタンでタイトルへ", 0xdc143c);
    
    }
}

void ResultScene::Finalize()
{
    // 読み込んだ画像・音声データを解放
    DeleteGraph(background);
    DeleteGraph(resultTitle);
    DeleteGraph(correctTitle);
    DeleteGraph(scoreTitle);
    DeleteGraph(Remainingtime);
    DeleteSoundMem(bgm);
    DeleteSoundMem(se);
    DeleteSoundMem(newSe);
    DeleteSoundMem(backSe);
    
}