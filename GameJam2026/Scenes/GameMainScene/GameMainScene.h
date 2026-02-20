#pragma once

#include "../SceneBase.h"
#include <vector>

class GameMainScene : public SceneBase
{
private:
	int GameMainBack;                //背景画像
	int currentIndex;                //現在の問題番号
	int selectIndex;                 //プレイヤーが選んだ選択肢(0=A, 1=B)
	int correctCount;                //正解数
	std::vector<int> questionImages; //問題画像
	std::vector<int> questImages;    //問題文画像
	std::vector<int> choiceAImages;  //選択肢画像(A)
	std::vector<int> choiceBImages;  //選択肢画像(B)
	std::vector<int> correctAnswers; //正解(0=A, 1=B)
	int GetCorrectCount() const { return correctCount; }	//リザルト画面に渡す

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