#pragma once
#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"

// ============================
// 汎用ゲームオブジェクトクラス
// Scene連携・生成・破棄が可能
// ============================
class GameObject : public GameObjectBase
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    void Initialize() override;
    void Update(float delta_second) override;
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;

    template <class OBJECT>
    OBJECT* CreateObject(const Vector2D& generate_location);

    void DestroyObject(GameObjectBase* target);
    Vector2D GetScreenOffset() const;
};