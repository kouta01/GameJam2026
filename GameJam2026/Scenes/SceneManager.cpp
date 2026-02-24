#include "SceneManager.h"
#include "../Utility/InputManager.h"
#include "DxLib.h"
#include "../Scenes/GameMainScene/GameMainScene.h"
#include "../Scenes/TitleScene/TitleScene.h"
#include "../Scenes/Result/ResultScene.h"
#include "../Scenes/HelpScene/HelpScene.h"

//----------------------------------------
// コンストラクタ：現在シーンを未設定に
//----------------------------------------
SceneManager::SceneManager() : current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

//----------------------------------------
// シーンマネージャー：初期化処理
// ・ウィンドウ設定
// ・DXライブラリ初期化
// ・最初のシーンをタイトルに設定
//----------------------------------------
void SceneManager::Initialize()
{
    // ウィンドウタイトル設定
    SetMainWindowText("quiz");

    // ウィンドウモードで起動
    if (ChangeWindowMode(TRUE) != DX_CHANGESCREEN_OK)
    {
        throw("ウィンドウモードで起動できませんでした\n");
    }

    // 解像度設定
    if (SetGraphMode(1280, 720, 32) == -1)
    {
        throw("解像度の設定に失敗しました\n");
    }

    // DXライブラリ初期化
    if (DxLib_Init() == -1)
    {
        throw("Dxライブラリが初期化できませんでした\n");
    }

    // 描画先を裏画面に設定
    if (SetDrawScreen(DX_SCREEN_BACK) == -1)
    {
        throw("指定先の指定ができませんでした\n");
    }

    // 最初はタイトルシーンから開始
    ChangeScene(eSceneType::E_TITLE);
}

//----------------------------------------
// シーンマネージャー：更新処理
// ・フレーム管理
// ・入力更新
// ・シーン更新
// ・シーン遷移
//----------------------------------------
void SceneManager::Update()
{
    // フレーム開始時間（マイクロ秒）
    LONGLONG start_time = GetNowHiPerformanceCount();

    // メインループ
    while (ProcessMessage() != -1)
    {
        // 現在時間
        LONGLONG now_time = GetNowHiPerformanceCount();

        // 1フレーム分の時間が経過したら更新処理
        if ((now_time - start_time) >= DELTA_SECOND)
        {
            start_time = now_time;

            // 入力更新
            InputManager::GetInstance()->Update();

            // シーン更新（戻り値は次のシーン）
            eSceneType next = current_scene->Update();

            // 描画処理
            Draw();

            // END が返されたらゲーム終了
            if (next == eSceneType::E_END)
            {
                break;
            }

            // シーンが変わる場合は切り替え
            if (next != current_scene->GetNowScene())
            {
                ChangeScene(next);
            }
        }

        // ESCキー or BACKボタンで終了
        if (CheckHitKey(KEY_INPUT_ESCAPE) ||
            InputManager::GetInstance()->GetButtonUp(XINPUT_BUTTON_BACK))
        {
            break;
        }
    }
}

//----------------------------------------
// シーンマネージャー：終了処理
// ・現在シーンの削除
// ・DXライブラリ終了
//----------------------------------------
void SceneManager::Finalize()
{
    if (current_scene != nullptr)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = nullptr;
    }

    // DXライブラリ終了
    DxLib_End();
}

//----------------------------------------
// 描画処理
// ・画面クリア
// ・シーン描画
// ・裏画面反映
//----------------------------------------
void SceneManager::Draw() const
{
    ClearDrawScreen();      // 画面初期化
    current_scene->Draw();  // シーン描画
    ScreenFlip();           // 表画面へ反映
}

//----------------------------------------
// シーン切り替え処理
// ・新シーン生成
// ・必要ならデータ受け渡し
// ・旧シーン破棄
// ・新シーン初期化
//----------------------------------------
void SceneManager::ChangeScene(eSceneType scene_type)
{
    // 新しいシーンを生成
    SceneBase* new_scene = CreateScene(scene_type);

    if (new_scene == nullptr)
    {
        throw("シーンが生成できませんでした。\n");
    }

    // GameMainScene → ResultScene の場合、結果を渡す
    if (scene_type == eSceneType::E_RESULT)
    {
        GameMainScene* mainScene = dynamic_cast<GameMainScene*>(current_scene);
        ResultScene* resultScene = dynamic_cast<ResultScene*>(new_scene);

        if (mainScene && resultScene)
        {
            resultScene->SetResult(mainScene->GetCorrectCount(), mainScene->GetScore());
        }
    }

    // シーンの終了処理
    if (current_scene != nullptr)
    {
        current_scene->Finalize();
        delete current_scene;
    }

    // シーン初期化
    new_scene->Initialize();

    // 現在シーン更新
    current_scene = new_scene;
}

//----------------------------------------
// シーン生成処理
//----------------------------------------
SceneBase* SceneManager::CreateScene(eSceneType scene_type)
{
    switch (scene_type)
    {
    case eSceneType::E_TITLE:
        return new TitleScene;

    case eSceneType::E_MAIN:
        return new GameMainScene;

    case eSceneType::E_RESULT:
        return new ResultScene;

    case eSceneType::E_HELP:
        return new HelpScene;

    default:
        return nullptr;
    }
}