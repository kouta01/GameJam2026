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
    SetFontSize(30);

    // ヘルプ画面の説明テキストを表示
    DrawString(200, 150, "=== HELP ===", 0xffffff);
    DrawString(200, 200, "AボタンでTITLE", 0xffffff);
    DrawString(200, 260, "ゲーム説明", 0xffffff);
    DrawString(200, 300, "このゲームは2択クイズです。", 0xffffff);
    DrawString(200, 340, "正しいと思うボタンを押してください。", 0xffffff);
    DrawString(200, 380, "全10問の正解数で結果が決まります。", 0xffffff);
}