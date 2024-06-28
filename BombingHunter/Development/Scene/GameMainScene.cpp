#include "GameMainScene.h"
#include"DxLib.h"

GameMainScene::GameMainScene()
{

}
GameMainScene::~GameMainScene()
{

}

void GameMainScene::Initialize()
{

}
//描画処理
void GameMainScene::Draw() const
{

}
//終了時処理
void GameMainScene::Finalize()
{
	//動的確保したオブジェクトを削除する
	player->Finalize();
	delete player;

	for (int i = 0; i < 10; i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;
		}
	}
}
//当たり判定処理(プレイヤーと敵)
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	// 敵情報が無ければ、当たり判定を無視する
		if (e == nullptr)
		{
			return false;
		}
}

