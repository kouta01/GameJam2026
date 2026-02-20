#pragma once

#include "../SceneBase.h"

class GameMainScene : public SceneBase
{
private:
	int GameMainBack;

public:
	GameMainScene();
	virtual ~GameMainScene();

private:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	virtual eSceneType GetNowScene() const override
	{
		return eSceneType::E_MAIN;
	}
};