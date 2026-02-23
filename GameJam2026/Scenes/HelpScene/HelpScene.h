#pragma once
#include "../../Scenes/SceneBase.h"

// ヘルプ画面を管理するシーンクラス
class HelpScene : public SceneBase
{
private:
    int background;  // ヘルプ画面の背景画像ハンドル
    int HelpTitle;
    int HelpFont1;
    int HelpFont2;

public:
    HelpScene();     // コンストラクタ
    ~HelpScene();    // デストラクタ

    void Initialize() override;   // 画像読み込みなどの初期化処理
    void Finalize() override;     // リソース解放処理

    eSceneType Update() override; // 入力処理・シーン遷移
    void Draw() const override;   // 背景・テキスト描画

    // 現在のシーン種別を返す
    eSceneType GetNowScene() const override
    {
        return eSceneType::E_HELP;
    }
};