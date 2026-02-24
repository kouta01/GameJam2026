#include "HelpScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"
#include "../SceneBase.h"

//----------------------------------------
// コンストラクタ：背景画像ハンドル初期化
//----------------------------------------
HelpScene::HelpScene()
    : background(-1)
{
}

HelpScene::~HelpScene()
{
}

//----------------------------------------
// 更新処理
// ・Aボタンでタイトルへ戻る
//----------------------------------------
eSceneType HelpScene::Update()
{
    InputManager* input = InputManager::GetInstance();

    //Aボタンが押されたらタイトルへ戻る
    if (input->GetButtonDown(PAD_A))
    {
        // 決定音を再生（多重再生防止）
        if (CheckSoundMem(selectbgm) != TRUE)
        {
            PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
        }
        return eSceneType::E_TITLE;
    }

    //何もなければ現在のシーンを維持
    return GetNowScene();
}

//----------------------------------------
// 描画処理
// ・背景画像
// ・ヘルプテキスト
//----------------------------------------
void HelpScene::Draw() const
{
    //背景描画
    DrawGraph(0, 0, background, TRUE);

    unsigned int yellow = GetColor(255, 255, 0);

    //タイトル
    DrawStringToHandle(180, 90, "=== HELP ===", yellow, HelpTitle);

    //見出し
    DrawStringToHandle(400, 260, "ゲーム説明", yellow, HelpFont1);

    //説明文
    DrawStringToHandle(400, 340, "このゲームは2択クイズです。", yellow, HelpFont2);
    DrawStringToHandle(400, 390, "正しいと思うボタンを押してください。", yellow, HelpFont2);
    DrawStringToHandle(400, 440, "全10問の正解数で結果が決まります。", yellow, HelpFont2);

    //操作説明
    DrawStringToHandle(400, 670, "AボタンでTITLE", yellow, HelpFont2);
}

//----------------------------------------
// 初期化処理
// ・背景画像読み込み
// ・フォント作成
//----------------------------------------
void HelpScene::Initialize()
{
    //決定音
    selectbgm = LoadSoundMem("Resource/Sounds/maou_se_system27.mp3");

    //背景画像読み込み
    background = LoadGraph("Resource/Image/QuizHelp.png");

    if (background == -1)
    {
        throw("Resource/Image/QuizHelp_bg.png がありません\n");
    }

    // フォント作成
    HelpTitle = CreateFontToHandle("BIZ UDPゴシック", 110, 10, DX_FONTTYPE_EDGE,
        -1, -1, FALSE, GetColor(0, 0, 0));

    HelpFont1 = CreateFontToHandle("BIZ UDPゴシック", 50, 10, DX_FONTTYPE_EDGE,
        -1, -1, FALSE, GetColor(0, 0, 0));

    HelpFont2 = CreateFontToHandle("BIZ UDPゴシック", 30, 10, DX_FONTTYPE_EDGE,
        -1, -1, FALSE, GetColor(0, 0, 0));
}

//・背景画像の削除
void HelpScene::Finalize()
{
    DeleteGraph(background);
}