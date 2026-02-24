#pragma once

#include "Vector2D.h"

// ===============================
// ボタン番号定義
// ===============================
#define PAD_A       (0)   // Aボタン
#define PAD_B       (1)   // Bボタン
#define PAD_X       (2)   // Xボタン
#define PAD_Y       (3)
#define PAD_START   (4) 

// 十字キー
#define D_PAD_UP    (12)
#define D_PAD_DOWN  (13)
#define D_PAD_LEFT  (14)
#define D_PAD_RIGHT (15)

// 最大入力数
#define D_KEYCODE_MAX (256)
#define D_BUTTON_MAX  (16)

// ========================================
// InputManager
// キーボード・コントローラー入力を管理するクラス
// ========================================
class InputManager
{
private:
    //シングルトンインスタンス
    static InputManager* instance;

    //キーボード入力（現在・前フレーム）
    char now_key[D_KEYCODE_MAX] = {};
    char old_key[D_KEYCODE_MAX] = {};

    //コントローラーボタン入力（現在・前フレーム）
    bool now_button[D_BUTTON_MAX] = {};
    bool old_button[D_BUTTON_MAX] = {};

    //トリガー入力（0.0～1.0）
    float trigger[2] = {};

    //スティック入力（-1.0～1.0）
    Vector2D stick[2] = {};

    //コンストラクタはprivate
    InputManager() = default;

    //コピー禁止
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

public:
    ~InputManager() = default;

    //インスタンス取得
    static InputManager* GetInstance();

    //インスタンス削除
    static void DeleteInstance();

    // 入力更新（毎フレーム呼ぶ）
    void Update();

    // ===============================
    // キーボード関連
    // ===============================
    bool GetKey(int key_code) const;        // 押している間
    bool GetKeyDown(int key_code) const;    // 押した瞬間
    bool GetKeyUp(int key_code) const;      // 離した瞬間

    // ===============================
    // コントローラー関連
    // ===============================
    bool GetButton(int button) const;       // 押している間
    bool GetButtonDown(int button) const;   // 押した瞬間
    bool GetButtonUp(int button) const;     // 離した瞬間

    float GetLeftTrigger() const;
    float GetRightTrigger() const;

    Vector2D GetLeftStick() const;
    Vector2D GetRightStick() const;

private:
    // 入力値の正規化処理
    float TriggerNormalization(unsigned char value);
    float StickNormalization(short value);

    // 範囲チェック
    bool CheckKeyCodeRange(int key_code) const;
    bool CheckButtonRange(int button) const;
};