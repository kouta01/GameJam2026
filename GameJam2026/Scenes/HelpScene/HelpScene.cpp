#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include "../SceneBase.h"

eSceneType HelpScene::Update()
{
    InputManager* input = InputManager::GetInstance();

    // Bボタンが押されたらタイトルへ戻る
    if (input->GetButtonDown(PAD_B))
    {
        return eSceneType::E_TITLE;
    }

    // 何もなければ現在のシーンを維持
    return GetNowScene();
}

void HelpScene::Draw() const
{
    SetFontSize(30);

    // ヘルプ画面の説明テキストを表示
    DrawString(200, 150, "=== HELP ===", 0xffffff);
    DrawString(200, 200, "Aボタン : ゲーム開始", 0xffffff);
    DrawString(200, 240, "Bボタン : 戻る", 0xffffff);
    DrawString(200, 280, "Xボタン : ヘルプ表示", 0xffffff);
}