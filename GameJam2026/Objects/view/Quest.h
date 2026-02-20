#pragma once
#include "../GameObject.h"
#include <string>

/// <summary>
/// Quiz問題表示オブジェクト
/// </summary>
class Quest : public GameObject {
private:
    std::string question_text; // 表示する問題文

public:
    Quest() = default;
    virtual ~Quest() = default;

    /// <summary>
    /// 表示する問題文をセット
    /// </summary>
    void SetQuestion(const std::string& text) { question_text = text; }

    /// <summary>
    /// 初期化処理
    /// デフォルトの描画位置などを設定
    /// </summary>
    void Initialize() override;

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update(float delta_second) override;

    /// <summary>
    /// 描画処理
    /// 指定座標に問題文を描画
    /// </summary>
    void Draw(const Vector2D& screen_offset) const override;
};