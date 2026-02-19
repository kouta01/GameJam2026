#include "DxLib.h"
//#include "Scenes/TitleScene/TitleScene.h"
#include "Scenes/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_
	LPSTR lpCmdine, _In_ int nShowCmd)
{
	try
	{
		// シーンマネージャー機能の生成
		SceneManager manager;

		// シーンマネージャー機能の初期化処理
		manager.Initialize();

		// シーンマネージャー機能の更新処理
		manager.Update();

		// シーンマネージャー機能の終了時処理
		manager.Finalize();
	}
	catch (const char* err_log)
	{
		// エラー発生内容の出力
		OutputDebugString(err_log);
	
		// エラー終了を通知
		return -1;
	}

// 正常終了を通知
return 0;
}