#pragma once
#include "../Utility/Vector2D.h"

class SceneBase; // 前方宣言（循環参照防止）

//----------------------------------------
// 可動性（Stationary = 固定 / Movable = 移動可能）
//----------------------------------------
enum class eMobilityType { Stationary, Movable };

// ============================
// ■ GameObjectBase
//    ゲーム内オブジェクトの基底クラス
//    ・位置情報
//    ・画像ハンドル
//    ・描画処理
//    ・所属シーン
//    ・Zレイヤー（描画順）
//    ・可動性（固定/移動）
// ============================
class GameObjectBase {
protected:
    SceneBase* owner_scene;   // 所属シーン
    Vector2D   location;      // 座標
    int        image;         // 描画用画像ハンドル（-1 = 未設定）
    int        z_layer;       // 描画順序（小さいほど手前）
    eMobilityType mobility;   // 可動性（固定 or 移動）
    bool       flip_flag;     // 描画反転フラグ

public:
    GameObjectBase();
    virtual ~GameObjectBase();

    //----------------------------------------
    // 初期化処理（派生クラスで必要に応じて実装）
    //----------------------------------------
    virtual void Initialize();

    //----------------------------------------
    // 更新処理（delta_second：経過時間）
    //----------------------------------------
    virtual void Update(float delta_second);

    //----------------------------------------
    // 描画処理（screen_offset：カメラ補正値）
    //----------------------------------------
    virtual void Draw(const Vector2D& screen_offset) const;

    //----------------------------------------
    // 終了処理（派生クラスで必要に応じて実装）
    //----------------------------------------
    virtual void Finalize();

    //----------------------------------------
    // 所属シーンの設定
    //----------------------------------------
    void SetOwnerScene(SceneBase* scene);

    //----------------------------------------
    // 位置情報の取得 / 設定
    //----------------------------------------
    const Vector2D& GetLocation() const;
    void SetLocation(const Vector2D& loc);

    //----------------------------------------
    // Zレイヤー（描画順）の取得
    //----------------------------------------
    int GetZLayer() const;

    //----------------------------------------
    // 可動性の取得（固定 or 移動）
    //----------------------------------------
    eMobilityType GetMobility() const;

    //----------------------------------------
    // 型判定（T 型にキャスト可能か）
    //----------------------------------------
    template <typename T>
    bool IsKindOf() const { return dynamic_cast<const T*>(this) != nullptr; }
};