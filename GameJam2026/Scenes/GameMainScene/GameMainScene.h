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
	int score = 0;                   //スコア
	int timer = 60 * 60;             //タイマー(1分)           
	int AnswerImage;                 //正解画像
	int IncorrectImage;              //不正解画像
	int gameBGM;                     //BGM
	int seCorrect;                   //正解SE
	int seIncorrect;                 //不正解SE
	int seNextQuestion;              //次の問題が出るときのSE
	bool showResult = false;         //結果表示中か?
	int resultTimer;                 //結果表示の時間
	int resultImageToShow;           //今表示する結果画像(正解か不正解)
	static float finalScore;		 //リザルト用スコア
	static int finalRemainingSeconds;//リザルト用タイマー
	static float highScore;			 //タイトル用スコア
	static bool isNewRecord;		 //ニューレコード用スコア
	std::vector<int> questionImages; //問題画像
	std::vector<int> questImages;    //問題文画像
	std::vector<int> choiceAImages;  //選択肢画像(A)
	std::vector<int> choiceBImages;  //選択肢画像(B)
	std::vector<int> correctAnswers; //正解(0=A, 1=B)
	
private:
	//選択肢Aの表示位置
	const int choiceAX = 395;
	const int choiceAY = 582;

	//選択肢Bの表示位置
	const int choiceBX = 875;
	const int choiceBY = 583;

	//結果画像の表示位置
	int resultX = 0;
	int resultY = 0;

public:
	GameMainScene();
	virtual ~GameMainScene();

private:
	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

public:
	
	
	static float GetFinalScore();		//最終スコア格納
	static int GetFinalRemainingSeconds();//最終時間格納
	static float GetHighScore();		//歴代スコア格納
	static bool IsNewRecord();			//ニューレコード格納
	int GetCorrectCount() const { return correctCount; }
	int GetScore() const { return score; }
	virtual eSceneType GetNowScene() const override
	{
		return eSceneType::E_MAIN;
	}
};