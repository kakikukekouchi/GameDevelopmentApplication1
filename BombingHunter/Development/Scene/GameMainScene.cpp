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
//�`�揈��
void GameMainScene::Draw() const
{

}
//�I��������
void GameMainScene::Finalize()
{
	//���I�m�ۂ����I�u�W�F�N�g���폜����
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
//�����蔻�菈��(�v���C���[�ƓG)
bool GameMainScene::IsHitCheck(Player* p, Enemy* e)
{
	// �G��񂪖�����΁A�����蔻��𖳎�����
		if (e == nullptr)
		{
			return false;
		}
}

