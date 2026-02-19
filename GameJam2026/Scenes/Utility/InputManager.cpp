#include "InputManager.h"
#include "DxLib.h"

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
	}
	return instance;
}

void InputManager::DeleteInstance()
{
	delete instance;
	instance = nullptr;
}

void InputManager::Update()
{
	memcpy(old_key, now_key, sizeof(now_key));
	GetHitKeyStateAll(now_key);

	memcpy(old_button, now_button, sizeof(now_button));

	XINPUT_STATE dxInput = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &dxInput);

	// 十字キー入力（ビットフラグで取得）
	unsigned int state = GetJoypadInputState(DX_INPUT_PAD1);

	now_button[D_PAD_UP] = (state & PAD_INPUT_UP) != 0;
	now_button[D_PAD_DOWN] = (state & PAD_INPUT_DOWN) != 0;
	now_button[D_PAD_LEFT] = (state & PAD_INPUT_LEFT) != 0;
	now_button[D_PAD_RIGHT] = (state & PAD_INPUT_RIGHT) != 0;

	now_button[PAD_A] = (state & PAD_INPUT_1) != 0;
	now_button[PAD_B] = (state & PAD_INPUT_2) != 0;


	// トリガー/スティック
	trigger[0] = TriggerNormalization(dxInput.LeftTrigger);
	trigger[1] = TriggerNormalization(dxInput.RightTrigger);
	stick[0].x = StickNormalization(dxInput.ThumbLX);
	stick[0].y = StickNormalization(dxInput.ThumbLY);
	stick[1].x = StickNormalization(dxInput.ThumbRX);
	stick[1].y = StickNormalization(dxInput.ThumbRY);
}

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

bool InputManager::GetButton(int button) const
{
	return CheckButtonRange(button) && now_button[button] && old_button[button];
}

bool InputManager::GetButtonDown(int button) const
{
	return CheckButtonRange(button) && now_button[button] && !old_button[button];
}

bool InputManager::GetButtonUp(int button) const
{
	return CheckButtonRange(button) && !now_button[button] && old_button[button];
}

float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

Vector2D InputManager::GetLeftStick() const
{
	return stick[0];
}

Vector2D InputManager::GetRightStick() const
{
	return stick[1];
}

float InputManager::TriggerNormalization(unsigned char value)
{
	return static_cast<float>(value) / static_cast<float>(UCHAR_MAX);
}

float InputManager::StickNormalization(short value)
{
	if (value >= 0)
	{
		return static_cast<float>(value) / static_cast<float>(SHRT_MAX);
	}
	return -static_cast<float>(value) / static_cast<float>(SHRT_MIN);
}

bool InputManager::CheckKeyCodeRange(int key_code) const
{
	return (key_code >= 0) && (key_code < D_KEYCODE_MAX);
}

bool InputManager::CheckButtonRange(int button) const
{
	return (button >= 0) && (button < D_BUTTON_MAX);
}
