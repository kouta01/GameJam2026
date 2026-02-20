#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

TitleScene::TitleScene() : title_image(NULL), menu_image(NULL),
titlebgm(NULL), decisionbgm(NULL),menu_cursor(0), choice_flag(0), selectbgm(NULL)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	//画像読み込み

	title_image = LoadGraph("Resource/Image/Title.png");
	
	//menu_image = LoadGraph("");
	//cursor_image=LoadGraph("");

	//BGM.SEの読み込み
	selectbgm = LoadSoundMem("Resource/Sounds/maou_se_system27.mp3");
	//titlebgm = LoadSoundMem("");

	//エラーチェック
	if (title_image == -1)
	{
		throw("Resource/ImageTitle.pngがありません。\n");
	}
	if (selectbgm == -1)
	{
		throw("Resource/Sounds/maou_se_system27.mp3がありません\n");
	}
}

eSceneType TitleScene::Update()
{
	//BGMの再生


	//ボタン決定->Aボタン場合
	if (InputManager::GetInstance()->GetButtonDown(PAD_A))
	{
		/*choice_flag = 0;*/

		//SEがながれてないとき再生
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}

		return eSceneType::E_MAIN;
	}

	//ボタン決定→Bボタン場合
	if (InputManager::GetInstance()->GetButtonDown(PAD_B))
	{
		/*choice_flag = 1;*/

		//SEが流れていないとき再生
		if (CheckSoundMem(selectbgm) != TRUE)
		{
			PlaySoundMem(selectbgm, DX_PLAYTYPE_BACK, TRUE);
		}

		return eSceneType::E_HELP;
	}

	//ボタン決定→startボタン場合
	if (InputManager::GetInstance()->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::E_END;
		/*choice_flag = 2;*/
	}

	//決定した画面に遷移する
	//switch (choice_flag)
	//{
	//	case 0:
	//		return eSceneType::E_MAIN;
	//	case 1:
	//		return eSceneType::E_HELP;
	//	default:
	//		return eSceneType::E_END;
	//}
	//現在のシーンを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw()const
{
	//タイトル画像の描画
	DrawGraph(0, 0, title_image, TRUE);

	//メニュー画像の描画
	DrawGraph(120, 200, menu_image, TRUE);

	//操作ログ
	SetFontSize(30);
	DrawString(120, 400, "Aボタンでゲーム開始、\nBボタンでヘルプ画面、\nStartボタンで",0x000000);
	//素材ログ
	SetFontSize(20);
	//DrawString()

	//タイトルネーム
	SetFontSize(100);
	DrawString(150, 20, "Quiz", 0x000000);
}

//終了時処理
void TitleScene::Finalize() 
{
	//読み込んだ画像の削除
	DeleteGraph(title_image);
	DeleteGraph(menu_image);
	DeleteGraph(titlebgm);
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}