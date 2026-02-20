#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include "../SceneBase.h"

eSceneType HelpScene::Update()
{
    InputManager* input = InputManager::GetInstance();

    // Bボタンでタイトルに戻る
    if (input->GetButtonDown(PAD_B))
    {
        return eSceneType::E_TITLE;
    }

    return GetNowScene();
}

void HelpScene::Draw() const
{
    SetFontSize(30);

    DrawString(200, 150, "=== HELP ===", 0xffffff);
    DrawString(200, 200, "Aボタン : ゲーム開始", 0xffffff);
    DrawString(200, 240, "Bボタン : 戻る", 0xffffff);
    DrawString(200, 280, "Xボタン : ヘルプ表示", 0xffffff);
}