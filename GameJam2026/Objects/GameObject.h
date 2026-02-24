#pragma once
#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"

// ============================
// GameObject
// ・汎用ゲームオブジェクトクラス
// ・GameObjectBase を継承
// ・シーンとの連携、生成・破棄が可能
// ============================
class GameObject : public GameObjectBase
{
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    //----------------------------------------
    // 初期化処理（派生クラスで必要に応じて実装）
    //----------------------------------------
    void Initialize() override;

    //----------------------------------------
    // 更新処理（delta_second：経過時間）
    //----------------------------------------
    void Update(float delta_second) override;

    //----------------------------------------
    // 描画処理（screen_offset：カメラ補正値）
    //----------------------------------------
    void Draw(const Vector2D& screen_offset) const override;

    //----------------------------------------
    // 終了処理（派生クラスで必要に応じて実装）
    //----------------------------------------
    void Finalize() override;

    //----------------------------------------
    // オブジェクト生成
    // ・指定座標に新しい OBJECT を生成
    // ・SceneBase 側の管理に渡す前提
    //----------------------------------------
    template <class OBJECT>
    OBJECT* CreateObject(const Vector2D& generate_location);

    //----------------------------------------
    // オブジェクト破棄
    // ・SceneBase 側の管理対象から削除する
    //----------------------------------------
    void DestroyObject(GameObjectBase* target);

    //----------------------------------------
    // カメラ補正値の取得
    //----------------------------------------
    Vector2D GetScreenOffset() const;
};