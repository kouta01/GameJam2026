#include "InputManager.h"
#include "DxLib.h"

// ===============================
// 静的メンバー変数の定義
// ===============================
InputManager* InputManager::instance = nullptr;

// ===============================
// インスタンス取得（シングルトン）
// ===============================
InputManager* InputManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new InputManager();
    }
    return instance;
}

// ===============================
// インスタンス削除
// ===============================
void InputManager::DeleteInstance()
{
    delete instance;
    instance = nullptr;
}

// ===============================
// 入力更新（毎フレーム呼ぶ）
// ===============================
void InputManager::Update()
{
    // 前フレームのキー状態を保存
    memcpy(old_key, now_key, sizeof(now_key));

    // 現在のキーボード入力取得
    GetHitKeyStateAll(now_key);

    // 前フレームのボタン状態保存
    memcpy(old_button, now_button, sizeof(now_button));

    // XInput状態取得
    XINPUT_STATE dxInput = {};
    GetJoypadXInputState(DX_INPUT_PAD1, &dxInput);

    // ボタン状態取得
    unsigned int state = GetJoypadInputState(DX_INPUT_PAD1);

    // 十字キー
    now_button[D_PAD_UP] = (state & PAD_INPUT_UP) != 0;
    now_button[D_PAD_DOWN] = (state & PAD_INPUT_DOWN) != 0;
    now_button[D_PAD_LEFT] = (state & PAD_INPUT_LEFT) != 0;
    now_button[D_PAD_RIGHT] = (state & PAD_INPUT_RIGHT) != 0;

    // 通常ボタン
    now_button[PAD_A] = (state & PAD_INPUT_1) != 0;
    now_button[PAD_B] = (state & PAD_INPUT_2) != 0;
    now_button[PAD_X] = (state & PAD_INPUT_3) != 0;

    // トリガー値正規化
    trigger[0] = TriggerNormalization(dxInput.LeftTrigger);
    trigger[1] = TriggerNormalization(dxInput.RightTrigger);

    // スティック値正規化
    stick[0].x = StickNormalization(dxInput.ThumbLX);
    stick[0].y = StickNormalization(dxInput.ThumbLY);
    stick[1].x = StickNormalization(dxInput.ThumbRX);
    stick[1].y = StickNormalization(dxInput.ThumbRY);
}

// ===============================
// キー入力判定
// ===============================
bool InputManager::GetKey(int key_code) const
{
    return CheckKeyCodeRange(key_code) && now_key[key_code] != 0;
}

bool InputManager::GetKeyDown(int key_code) const
{
    return CheckKeyCodeRange(key_code) && now_key[key_code] && !old_key[key_code];
}

bool InputManager::GetKeyUp(int key_code) const
{
    return CheckKeyCodeRange(key_code) && !now_key[key_code] && old_key[key_code];
}

// ===============================
// ボタン入力判定
// ===============================
bool InputManager::GetButton(int button) const
{
    // 押している間
    return CheckButtonRange(button) && now_button[button];
}

bool InputManager::GetButtonDown(int button) const
{
    // 押した瞬間
    return CheckButtonRange(button) && now_button[button] && !old_button[button];
}

bool InputManager::GetButtonUp(int button) const
{
    // 離した瞬間
    return CheckButtonRange(button) && !now_button[button] && old_button[button];
}

// ===============================
// トリガー取得
// ===============================
float InputManager::GetLeftTrigger() const
{
    return trigger[0];
}

float InputManager::GetRightTrigger() const
{
    return trigger[1];
}

// ===============================
// スティック取得
// ===============================
Vector2D InputManager::GetLeftStick() const
{
    return stick[0];
}

Vector2D InputManager::GetRightStick() const
{
    return stick[1];
}

// ===============================
// 正規化処理
// ===============================
float InputManager::TriggerNormalization(unsigned char value)
{
    return static_cast<float>(value) / static_cast<float>(UCHAR_MAX);
}

float InputManager::StickNormalization(short value)
{
    if (value >= 0)
        return static_cast<float>(value) / static_cast<float>(SHRT_MAX);

    return -static_cast<float>(value) / static_cast<float>(SHRT_MIN);
}

// ===============================
// 範囲チェック
// ===============================
bool InputManager::CheckKeyCodeRange(int key_code) const
{
    return (key_code >= 0) && (key_code < D_KEYCODE_MAX);
}

bool InputManager::CheckButtonRange(int button) const
{
    return (button >= 0) && (button < D_BUTTON_MAX);
}