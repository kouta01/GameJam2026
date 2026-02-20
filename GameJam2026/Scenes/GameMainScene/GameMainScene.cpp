#include "GameMainScene.h"
#include "../../Objects/Player.h"
//#include "../../Objects/Quiz.h"
//#include "../../Objects/View/questView.h"
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