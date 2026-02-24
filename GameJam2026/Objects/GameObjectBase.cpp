#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"
#include <DxLib.h>

//----------------------------------------
// GameObjectBase
// ・ゲーム内オブジェクトの基底クラス
// ・位置、画像、描画、所属シーンなど共通機能
//----------------------------------------
GameObjectBase::GameObjectBase()
    : owner_scene(nullptr),          // 所属シーン
    location(0.0f, 0.0f),          // 座標
    image(-1),                     // 画像ハンドル（未設定は -1）
    z_layer(0),                    // 描画順
    mobility(eMobilityType::Stationary), // 移動タイプ
    flip_flag(false)               // 左右反転フラグ
{
}

GameObjectBase::~GameObjectBase() {}

//----------------------------------------
// 初期化処理（必要に応じて派生クラスで実装）
//----------------------------------------
void GameObjectBase::Initialize() {}

//----------------------------------------
// 更新処理（delta_second：経過時間）
//----------------------------------------
void GameObjectBase::Update(float delta_second) {}

//----------------------------------------
// 描画処理
// ・image が設定されている場合のみ描画
// ・screen_offset はカメラ補正値
//----------------------------------------
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
    if (image != -1) {
        Vector2D draw_pos = location + screen_offset;
        DrawGraph(static_cast<int>(draw_pos.x),
            static_cast<int>(draw_pos.y),
            image,
            TRUE);
    }
}

//----------------------------------------
// 終了処理（必要に応じて派生クラスで実装）
//----------------------------------------
void GameObjectBase::Finalize() {}

//----------------------------------------
// 所属シーンの設定
//----------------------------------------
void GameObjectBase::SetOwnerScene(SceneBase* scene) { owner_scene = scene; }

//----------------------------------------
// 位置情報の取得 / 設定
//----------------------------------------
const Vector2D& GameObjectBase::GetLocation() const { return location; }
void GameObjectBase::SetLocation(const Vector2D& loc) { location = loc; }

//----------------------------------------
// Zレイヤー（描画順）の取得
//----------------------------------------
int GameObjectBase::GetZLayer() const { return z_layer; }

//----------------------------------------
// 移動タイプの取得
//----------------------------------------
eMobilityType GameObjectBase::GetMobility() const { return mobility; }