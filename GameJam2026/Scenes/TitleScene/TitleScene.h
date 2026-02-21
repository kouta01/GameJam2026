#pragma once

#include "../SceneBase.h"

class TitleScene : public SceneBase
{
private:
	int title_image;		//背景画像
	int menu_image;				//メニュー画像
	int cursor_image;			//カーソル画像
	int choice_flag;			//メニュー番号
	int menu_cursor;			//メニューカーソル番号

	int titlebgm;              //タイトル画面のBGM
	int selectbgm;             //カーソル移動のSE
	int decisionbgm;           //決定時のSE

	//int nextScene;      // 次に行くシーン
	//int changeTimer;    // 遷移待ちタイマー

public:
	TitleScene();
	virtual ~TitleScene();

virtual void Initialize()override;		//初期化処理
virtual eSceneType Update() override;	//更新処理
virtual void Draw() const override;		//描画処理
virtual void Finalize() override;		//終了時処理

virtual eSceneType GetNowScene() const override;		//現在のシーン状態
};
