#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include "../SceneBase.h"

HelpScene::HelpScene()
    : background(-1)
{
}

HelpScene::~HelpScene()
{
}

eSceneType HelpScene::Update()
{
    InputManager* input = InputManager::GetInstance();

    // Aボタンが押されたらタイトルへ戻る
    if (input->GetButtonDown(PAD_A))
    {
        return eSceneType::E_TITLE;
    }

    // 何もなければ現在のシーンを維持
    return GetNowScene();
}

void HelpScene::Draw() const
{
    //背景描画
    DrawGraph(0, 0, background, TRUE);

    // ヘルプ画面の説明テキストを表示
    SetFontSize(110);
    DrawString(300, 150, "=== HELP ===", 0xffffff);

    SetFontSize(50);
    DrawString(400, 260, "ゲーム説明", 0xffffff);

    SetFontSize(30);
    DrawString(400, 340, "このゲームは2択クイズです。", 0xffffff);
    DrawString(400, 390, "正しいと思うボタンを押してください。", 0xffffff);
    DrawString(400, 440, "全10問の正解数で結果が決まります。", 0xffffff);
    DrawString(400, 670, "AボタンでTITLE", 0xffffff);
}

void HelpScene::Initialize()
{
    //ヘルプ画面の背景画像を読み込む
    background = LoadGraph("Resource/Image/QuizHelp.png");

    if (background == -1)
    {
        throw("Resource/Image/QuizHelp_bg.png がありません\n");
    }
}

void HelpScene::Finalize()
{
    // 読み込んだ背景画像を削除
    DeleteGraph(background);
}