#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include "../SceneBase.h"


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
    // ヘルプ画面の説明テキストを表示
    SetFontSize(110);
    DrawString(300, 150, "=== HELP ===", 0xffffff);

    SetFontSize(50);
    DrawString(200, 260, "ゲーム説明", 0xffffff);

    SetFontSize(30);
    DrawString(200, 340, "このゲームは2択クイズです。", 0xffffff);
    DrawString(200, 390, "正しいと思うボタンを押してください。", 0xffffff);
    DrawString(200, 440, "全10問の正解数で結果が決まります。", 0xffffff);
    DrawString(100, 600, "AボタンでTITLE", 0xffffff);
}