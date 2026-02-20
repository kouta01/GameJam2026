#pragma once
#include "../../Scenes/SceneBase.h"

class HelpScene : public SceneBase
{
public:
    HelpScene() {}
    ~HelpScene() {}

    void Initialize() override {}   // ヘルプ画面は特に初期化なし
    void Finalize() override {}     // 終了処理も特になし

    eSceneType Update() override;   // 入力受付（戻るボタン）
    void Draw() const override;     // ヘルプ内容の描画

    // このシーンが HELP であることを返す
    eSceneType GetNowScene() const override
    {
        return eSceneType::E_HELP;
    }
};