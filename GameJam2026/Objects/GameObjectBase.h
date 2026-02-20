#pragma once
#include "../Utility/Vector2D.h"

class SceneBase; // 前方宣言

// 可動性（固定 / 移動可能）
enum class eMobilityType { Stationary, Movable };

// ============================
// ゲームオブジェクト基底クラス
// ============================
class GameObjectBase {
protected:
    SceneBase* owner_scene;   // 所属シーン
    Vector2D location;        // 座標
    int image;                // 描画用画像ハンドル
    int z_layer;              // 描画順序
    eMobilityType mobility;   // 可動性
    bool flip_flag;           // 描画反転フラグ

public:
    GameObjectBase();
    virtual ~GameObjectBase();

    virtual void Initialize();
    virtual void Update(float delta_second);
    virtual void Draw(const Vector2D& screen_offset) const;
    virtual void Finalize();

    void SetOwnerScene(SceneBase* scene);
    const Vector2D& GetLocation() const;
    void SetLocation(const Vector2D& loc);
    int GetZLayer() const;
    eMobilityType GetMobility() const;

    template <typename T>
    bool IsKindOf() const { return dynamic_cast<const T*>(this) != nullptr; }
};