#include "GameMainScene.h"
#include "../../Utility/InputManager.h"
#include<DxLib.h>

GameMainScene::GameMainScene()
	:GameMainBack(0)
{

}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	GameMainBack = LoadGraph("Resource/Image/InGame.png");
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	DrawGraph(0, 0, GameMainBack, TRUE);
}

void GameMainScene::Finalize()
{

}