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
        if (CheckSoundMem(selectbgm) != TRUE)
        {
            PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
        }
        return eSceneType::E_TITLE;
    }

    // 何もなければ現在のシーンを維持
    return GetNowScene();
}

void HelpScene::Draw() const
{
    //背景描画
    DrawGraph(0, 0, background, TRUE);

    unsigned int yellow = GetColor(255, 255, 0);

    // ヘルプ画面の説明テキストを表示
    /*SetFontSize(110);*/
    /*DrawString(300, 150, "=== HELP ===", 0xffffff);*/
    DrawStringToHandle(180, 90, "=== HELP ===", yellow, HelpTitle);

    /*SetFontSize(50);*/
    /*DrawString(400, 260, "ゲーム説明", 0xffffff);*/
    DrawStringToHandle(400, 260, "ゲーム説明", yellow, HelpFont1);

    /*SetFontSize(30);*/
    /*DrawString(400, 340, "このゲームは2択クイズです。", 0xffffff);*/
    DrawStringToHandle(400, 340, "このゲームは2択クイズです。", yellow, HelpFont2);
    /*DrawString(400, 390, "正しいと思うボタンを押してください。", 0xffffff);*/
    DrawStringToHandle(400, 390, "正しいと思うボタンを押してください。", yellow, HelpFont2);
    /*DrawString(400, 440, "全10問の正解数で結果が決まります。", 0xffffff);*/
    DrawStringToHandle(400, 440, "全10問の正解数で結果が決まります。", yellow, HelpFont2);
    /*DrawString(400, 670, "AボタンでTITLE", 0xffffff);*/
    DrawStringToHandle(400, 670, "AボタンでTITLE", yellow, HelpFont2);
}

void HelpScene::Initialize()
{
    selectbgm = LoadSoundMem("Resource/Sounds/maou_se_system27.mp3");
    //ヘルプ画面の背景画像を読み込む
    background = LoadGraph("Resource/Image/QuizHelp.png");

    if (background == -1)
    {
        throw("Resource/Image/QuizHelp_bg.png がありません\n");
    }

    HelpTitle = CreateFontToHandle("BIZ UDPゴシック", 110, 10, DX_FONTTYPE_EDGE, -1, -1, FALSE, GetColor(0,0,0));
    HelpFont1 = CreateFontToHandle("BIZ UDPゴシック", 50, 10, DX_FONTTYPE_EDGE, -1, -1, FALSE, GetColor(0, 0, 0));
    HelpFont2 = CreateFontToHandle("BIZ UDPゴシック", 30, 10, DX_FONTTYPE_EDGE, -1, -1, FALSE, GetColor(0, 0, 0));
}

void HelpScene::Finalize()
{
    // 読み込んだ背景画像を削除
    DeleteGraph(background);
}