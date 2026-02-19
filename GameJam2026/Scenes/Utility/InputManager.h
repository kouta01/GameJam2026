#pragma once
#pragma once

#include "Vector2D.h"
#define PAD_A       (0)   // Aボタン
#define PAD_B		(1) // Bボタン
#define D_PAD_UP    (12)
#define D_PAD_DOWN  (13)
#define D_PAD_LEFT  (14)
#define D_PAD_RIGHT (15)
#define D_KEYCODE_MAX (256)
#define D_BUTTON_MAX (16)

class InputManager
{
private:
	static InputManager* instance;

	char now_key[D_KEYCODE_MAX] = {};
	char old_key[D_KEYCODE_MAX] = {};

	bool now_button[D_BUTTON_MAX] = {};
	bool old_button[D_BUTTON_MAX] = {};
	float trigger[2] = {};
	Vector2D stick[2] = {};

	InputManager() = default;
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

public:
	~InputManager() = default;

	static InputManager* GetInstance();
	static void DeleteInstance();

	void Update();

	bool GetKey(int key_code) const;
	bool GetKeyDown(int key_code) const;
	bool GetKeyUp(int key_code) const;

	bool GetButton(int button) const;
	bool GetButtonDown(int button) const;
	bool GetButtonUp(int button) const;

	float GetLeftTrigger() const;
	float GetRightTrigger() const;

	Vector2D GetLeftStick() const;
	Vector2D GetRightStick() const;

private:
	float TriggerNormalization(unsigned char value);
	float StickNormalization(short value);

	bool CheckKeyCodeRange(int key_code) const;
	bool CheckButtonRange(int button) const;
};
