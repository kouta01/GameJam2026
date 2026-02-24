#include "Quest.h"
#include <DxLib.h>
#include "../../Utility/Vector2D.h"
#include "../GameObjectBase.h"
#include"../../Scenes/GameMainScene/GameMainScene.h"
//<summary>
//初期化
//デフォルトの描画位置を設定
//</summary>
void Quest::Initialize()
{
    GameObjectBase::location = Vector2D(200.0f, 100.0f); // 画面中央付近
}

//<summary>
//更新処理
//表示専用なので特に処理なし
//</summary>
void Quest::Update(float delta_second)
{
    // Quiz用表示オブジェクトなので更新不要
}

//<summary>
//描画処理
//指定した座標に問題文を描画
//</summary>
void Quest::Draw(const Vector2D& screen_offset) const
{
    //カメラオフセットを考慮して描画
    Vector2D draw_pos = location + screen_offset;

    SetFontSize(24); //フォントサイズ設定
    DrawString(static_cast<int>(draw_pos.x),
        static_cast<int>(draw_pos.y),
        question_text.c_str(),
        GetColor(255, 255, 255)); //文字色(白)
}

