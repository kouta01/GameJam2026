#include "GameMainScene.h"
#include "../../Objects/Player.h"
//#include "../../Objects/Quiz.h"
//#include "../../Objects/View/questView.h"
#include "../../Utility/InputManager.h"
#include<DxLib.h>

GameMainScene::GameMainScene()
	:GameMainBack(0)
	,currentIndex(0)
	,selectIndex(0)
	,correctCount(0)
	,AnswerImage(0)
	,IncorrectImage(0)
	,resultTimer(0)
{

}

GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{
	//背景画像
	GameMainBack = LoadGraph("Resource/Image/InGame.png");

	//正解画像
	AnswerImage = LoadGraph("Resource/Image/Answer.png");

	//不正解画像
	IncorrectImage = LoadGraph("Resource/Image/Incorrect.png");

	//問題画像
	questionImages.push_back(LoadGraph("Resource/Image/Question1.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question1.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question2.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question2.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question2.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question1.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question1.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question2.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question1.png"));
	questionImages.push_back(LoadGraph("Resource/Image/Question2.png"));

	//問題文画像
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint1.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint2.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint3.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint4.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint5.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint6.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint7.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint8.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint9.png"));
	questImages.push_back(LoadGraph("Resource/Image/Hint/Hint10.png"));

	//選択肢A
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice1.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice6.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice3.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice4.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice8.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice6.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice4.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice10.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice1.png"));
	choiceAImages.push_back(LoadGraph("Resource/Image/Choice/Choice10.png"));

	//選択肢B
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice5.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice2.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice6.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice10.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice5.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice2.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice7.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice8.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice9.png"));
	choiceBImages.push_back(LoadGraph("Resource/Image/Choice/Choice5.png"));

	//正解(0=A, 1=B)
	correctAnswers.push_back(0);  //Q1の正解はA
	correctAnswers.push_back(1);  //Q2の正解はB
	correctAnswers.push_back(0);  //Q3の正解はA
	correctAnswers.push_back(0);  //Q4の正解はA
	correctAnswers.push_back(1);  //Q5の正解はB
	correctAnswers.push_back(0);  //Q6の正解はA
	correctAnswers.push_back(1);  //Q7の正解はB
	correctAnswers.push_back(1);  //Q8の正解はB
	correctAnswers.push_back(1);  //Q9の正解はB
	correctAnswers.push_back(0);  //Q10の正解はA
}

eSceneType GameMainScene::Update()
{
	InputManager* input = InputManager::GetInstance();

	//結果表示中ならタイマーだけ進める
	if (showResult)
	{
		resultTimer++;

		//30フレーム(0.5秒)表示したら次へ
		if (resultTimer > 30)
		{
			showResult = false;
			resultTimer = 0;

			currentIndex++;
			//全問終了
			if (currentIndex >= questionImages.size())
			{
				return eSceneType::E_RESULT;
			}
		}

		return GetNowScene();
	}

	//Aボタンなら選択肢Aを選ぶ
	if (input->GetButtonDown(PAD_A))
	{
		selectIndex = 0;

		//正解なら正解数をカウントする
		if (correctAnswers[currentIndex] == 0)
		{
			correctCount++;
			resultImageToShow = AnswerImage;
		}
		else
		{
			resultImageToShow = IncorrectImage;
		}

		//Aの位置に結果画像を表示
		resultX = choiceAX;
		resultY = choiceAY;

		showResult = true;
	}

	//Bボタンなら選択肢Bを選ぶ
	if (input->GetButtonDown(PAD_B))
	{
		selectIndex = 1;

		//正解かどうか判定
		if (correctAnswers[currentIndex] == 1)
		{
			correctCount++;
			resultImageToShow = AnswerImage;
		}
		else
		{
			resultImageToShow = IncorrectImage;
		}

		resultX = choiceBX;
		resultY = choiceBY;

		showResult = true;

	}

	return GetNowScene();
}

void GameMainScene::Draw() const
{
	//背景画像
	DrawGraph(0, 0, GameMainBack, TRUE);

	if (currentIndex >= questionImages.size()) return;
		//問題画像
		DrawGraph(525, 68, questionImages[currentIndex], TRUE);

		//問題文画像
		DrawGraph(190, 250, questImages[currentIndex], TRUE);

		//選択肢画像A
		DrawGraph(395, 582, choiceAImages[currentIndex], TRUE);

		//選択肢画像B
		DrawGraph(875, 583, choiceBImages[currentIndex], TRUE);

		if (showResult)
		{
			DrawGraph(resultX, resultY, resultImageToShow, TRUE);
		}
}

void GameMainScene::Finalize()
{

}