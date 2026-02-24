#include "GameMainScene.h"
#include "../../Objects/Player.h"
//#include "../../Objects/Quiz.h"
//#include "../../Objects/View/questView.h"
#include "../../Utility/InputManager.h"
#include<DxLib.h>
#include <tchar.h>

//最終スコア初期化処理
float GameMainScene::finalScore = 0.0f;
//最終時間初期化処理
int GameMainScene::finalRemainingSeconds = 0;
//最高スコア初期化処理
float GameMainScene::highScore = 0.0f;
//ニューレコード初期化処理
bool GameMainScene::isNewRecord = false;

GameMainScene::GameMainScene()
	:GameMainBack(0)
	,currentIndex(0)
	,selectIndex(0)
	,correctCount(0)
	,AnswerImage(0)
	,IncorrectImage(0)
	,resultTimer(0)
	, warningBGM(-1)
	, isWarningPlaying(false)
	, seFinish(-1)
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

	//BGM
	gameBGM = LoadSoundMem("Resource/Sounds/Thinkingtime.mp3");
	PlaySoundMem(gameBGM, DX_PLAYTYPE_LOOP);

	// 警告BGM
	warningBGM = LoadSoundMem("Resource/Sounds/time2.mp3");

	// 終了SE
	seFinish = LoadSoundMem("Resource/Sounds/fin.mp3");

	// 正解SE
	seCorrect = LoadSoundMem("Resource/Sounds/seikai.mp3");

	// 不正解SE
	seIncorrect = LoadSoundMem("Resource/Sounds/huseikai.mp3");

	//出題SE
	//seNextQuestion = LoadSoundMem("Resource/Sounds/出題1.mp3");

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

	timer = 45 * 60; //60秒

	timerFont = CreateFontToHandle("BIZ UDPゴシック",96,7);
}

eSceneType GameMainScene::Update()
{
	// 入力取得
	InputManager* input = InputManager::GetInstance();

	// ========================================
	// 終了演出中の処理
	// ========================================
	if (isEnding)
	{
		endingTimer++;   // 演出用タイマー加算

		// 2秒経過したらリザルトへ遷移
		if (endingTimer > 120) // 60fps想定
		{
			return eSceneType::E_RESULT;
		}

		// 演出中は他の処理をしない
		return GetNowScene();
	}

	// ========================================
	// タイマー更新
	// ========================================
	timer--;  // 1フレームごとに減少

	int seconds = timer / 60;  // 秒に変換（60fps想定）

	// ========================================
	// 残り10秒で警告BGMに切り替え
	// ========================================
	if (seconds <= 10 && seconds > 0 && !isWarningPlaying)
	{
		StopSoundMem(gameBGM);                      // 通常BGM停止
		PlaySoundMem(warningBGM, DX_PLAYTYPE_LOOP); // 警告BGMループ再生
		isWarningPlaying = true;                    // 再生フラグON
	}

	// ========================================
	// タイムアップ処理
	// ========================================
	if (timer <= 0)
	{
		timer = 0;  // マイナス防止

		// 最終スコア計算
		finalRemainingSeconds = 0;
		finalScore = correctCount;

		// ハイスコア更新判定
		if (finalScore > highScore)
		{
			highScore = finalScore;
			isNewRecord = true;
		}
		else
		{
			isNewRecord = false;
		}

		// 終了演出開始
		if (!isEnding)
		{
			StopSoundMem(warningBGM);
			StopSoundMem(gameBGM);
			PlaySoundMem(seFinish, DX_PLAYTYPE_BACK);

			isEnding = true;
			endingType = 1; // TIMEOUT
			endingTimer = 0;
		}

		return GetNowScene();
	}

	// ========================================
	// 正誤結果表示中の処理
	// ========================================
	if (showResult)
	{
		resultTimer++;  // 表示時間カウント

		// 0.3秒表示後に次の問題へ
		if (resultTimer > 18)
		{
			showResult = false;
			resultTimer = 0;

			currentIndex++;  // 次の問題へ

			// ========================================
			// 全問終了チェック
			// ========================================
			if (currentIndex >= questionImages.size())
			{
				// 最終スコア計算（残り時間ボーナス含む）
				finalRemainingSeconds = timer / 60;
				finalScore = correctCount + finalRemainingSeconds * 0.1f;

				// ハイスコア更新判定
				if (finalScore > highScore)
				{
					highScore = finalScore;
					isNewRecord = true;
				}
				else
				{
					isNewRecord = false;
				}

				// 効果音停止
				StopSoundMem(warningBGM);
				StopSoundMem(gameBGM);
				StopSoundMem(seCorrect);
				StopSoundMem(seIncorrect);

				// 終了演出開始
				if (!isEnding)
				{
					PlaySoundMem(seFinish, DX_PLAYTYPE_BACK);
					isEnding = true;
					endingType = 2; // FINISH
					endingTimer = 0;
				}
			}
		}

		return GetNowScene();
	}

	// ========================================
	// 入力処理
	// ========================================

	// ----------------------------
	// Aボタン（選択肢A）
	// ----------------------------
	if (input->GetButtonDown(PAD_A))
	{
		selectIndex = 0;  // Aを選択

		// 正解判定
		if (correctAnswers[currentIndex] == 0)
		{
			correctCount++;          // 正解数加算
			score += 2;              // スコア加算
			resultImageToShow = AnswerImage;

			StopSoundMem(seCorrect);
			PlaySoundMem(seCorrect, DX_PLAYTYPE_BACK);
		}
		else
		{
			resultImageToShow = IncorrectImage;

			StopSoundMem(seIncorrect);
			PlaySoundMem(seIncorrect, DX_PLAYTYPE_BACK);
		}

		// 結果画像表示位置（Aの位置）
		resultX = choiceAX;
		resultY = choiceAY;

		showResult = true;  // 結果表示開始
	}

	// ----------------------------
	// Bボタン（選択肢B）
	// ----------------------------
	if (input->GetButtonDown(PAD_B))
	{
		selectIndex = 1;  // Bを選択

		// 正解判定
		if (correctAnswers[currentIndex] == 1)
		{
			correctCount++;
			score += 2;
			resultImageToShow = AnswerImage;

			StopSoundMem(seCorrect);
			PlaySoundMem(seCorrect, DX_PLAYTYPE_BACK);
		}
		else
		{
			resultImageToShow = IncorrectImage;

			StopSoundMem(seIncorrect);
			PlaySoundMem(seIncorrect, DX_PLAYTYPE_BACK);
		}

		// 結果画像表示位置（Bの位置）
		resultX = choiceBX;
		resultY = choiceBY;

		showResult = true;
	}

	// シーン維持
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	// currentIndex が問題数を超えたら描画しない
	//if (currentIndex >= questionImages.size())
		//return;

	//背景画像
	DrawGraph(0, 0, GameMainBack, TRUE);

	//タイマーの表示
	int seconds = timer / 60;//残り時間
	 int yellow = GetColor(255, 215, 0);//色指定：黄色
	 int red = GetColor(255, 0, 0);		//色指定：赤
	 int black = GetColor(0, 0, 0);	//色指定：黒
	float scale = 1.0f;

	int x = 900;
	int y = 70;

	TCHAR timeText[16];
	sprintf_s(timeText, TEXT("%02d"), seconds);

	//残り10秒で演出
	if (seconds <= 10)
	{
		// 拡大縮小アニメ
		scale = 1.0f + 0.2f * sin(GetNowCount() * 0.2f);

		// 点滅（20フレーム周期）
		if ((GetNowCount() / 90) % 2 == 0)
		{
			// ===== 黒フチ（8方向） =====
			DrawFormatStringToHandle(x - 2, y, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x + 2, y, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x, y - 2, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x, y + 2, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x - 2, y - 2, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x + 2, y - 2, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x - 2, y + 2, black, timerFont, TEXT("%02d"), seconds);
			DrawFormatStringToHandle(x + 2, y + 2, black, timerFont, TEXT("%02d"), seconds);

			// ===== 本体 =====
			DrawFormatStringToHandle(x, y, red, timerFont, TEXT("%02d"), seconds);
		}
	}
	else
	{
		// ===== 黒フチ =====
		DrawFormatStringToHandle(x - 2, y, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x + 2, y, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x, y - 2, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x, y + 2, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x - 2, y - 2, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x + 2, y - 2, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x - 2, y + 2, black, timerFont, TEXT("%02d"), seconds);
		DrawFormatStringToHandle(x + 2, y + 2, black, timerFont, TEXT("%02d"), seconds);

		// ===== 本体 =====
		DrawFormatStringToHandle(x, y, yellow, timerFont, TEXT("%02d"), seconds);
	}

	if (currentIndex < questionImages.size())
	{
		//問題画像
		DrawGraph(525, 65, questionImages[currentIndex], TRUE);

		//問題文画像
		DrawGraph(190, 250, questImages[currentIndex], TRUE);

		//選択肢画像A
		DrawGraph(395, 582, choiceAImages[currentIndex], TRUE);

		//選択肢画像B
		DrawGraph(875, 583, choiceBImages[currentIndex], TRUE);
	}

		if (showResult)
		{
			DrawGraph(resultX, resultY, resultImageToShow, TRUE);
		}

		if (isEnding)//終了演出
		{
			int red = GetColor(255, 0, 0);
			int black = GetColor(0, 0, 0);

			const TCHAR* text = TEXT("");

			if (endingType == 1)
				text = TEXT("TIME OUT");
			else if (endingType == 2)
				text = TEXT("FINISH");

			// 黒フチ
			DrawString(500 - 2, 300, text, black);
			DrawString(500 + 2, 300, text, black);
			DrawString(500, 300 - 2, text, black);
			DrawString(500, 300 + 2, text, black);

			// 本体
			DrawString(500, 300, text, red);
		}
}

//最終スコア格納
float GameMainScene::GetFinalScore()
{
	return finalScore;
}

//最終時間格納
int GameMainScene::GetFinalRemainingSeconds()
{
	return finalRemainingSeconds;
}

//最高スコア格納
float GameMainScene::GetHighScore()
{
	return highScore;
}

//ニューレコードスコア格納
bool GameMainScene::IsNewRecord()
{
	return isNewRecord;
}

//終了時処理
void GameMainScene::Finalize()
{
	
	DeleteSoundMem(gameBGM);
	DeleteSoundMem(warningBGM);
	DeleteSoundMem(seFinish);
	DeleteSoundMem(seCorrect);
	DeleteSoundMem(seIncorrect);
}
