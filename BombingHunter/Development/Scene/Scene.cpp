#include "Scene.h"
#include"../Utility/InputControl.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Enemy/Enemy2.h"
#include"../Objects/Enemy/Enemy3.h"
#include"../Objects/Enemy/Enemy4.h"
#include"../Objects/Enemy/BackGround.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Bomb.h"
#include"../Objects/Enemy/tama.h"
#include"../Objects/GameObject.h"
#include"DxLib.h"


Bomb* b = nullptr;

//�R���X�g���N�^
Scene::Scene() : objects(),back_image(NULL),tim_image(),tim(),sc(),hi(),oto(NULL),enemy_count(),count()
{
	animation_count = 0;
	enemy_count = NULL;
	count = NULL;
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(300.0f, 60.0f));
	//�G�l�~�B�[�𐶐�����
	CreateObject<Enemy>(Vector2D(350.0f, 350.0f));
	//�G�l�~�B�[�𐶐�����
	CreateObject<Enemy>(Vector2D(240.0f, 350.0f));
	//�G�l�~�B�[�𐶐�����
	CreateObject<Enemy>(Vector2D(150.0f, 350.0f));
	//�G�l�~�B�[2�𐶐�����
	CreateObject<Enemy2>(Vector2D(200.0f, 100.0f));
	//�G�l�~�B�[2�𐶐�����
	CreateObject<Enemy2>(Vector2D(100.0f, 120.0f));
	//�G�l�~�B�[2�𐶐�����
	CreateObject<Enemy2>(Vector2D(300.0f, 120.0f));
	//�G�l�~�B�[�R�𐶐�����
	CreateObject<Enemy3>(Vector2D(100.0f, 350.0f));
	//�G�l�~�B�[�S�𐶐�����
	CreateObject<Enemy4>(Vector2D(200.0f, 200.0f));
	//�G�l�~�B�[�S�𐶐�����
	CreateObject<Enemy4>(Vector2D(100.0f, 200.0f));
	//�G�l�~�B�[�S�𐶐�����
	CreateObject<Enemy4>(Vector2D(50.0f, 200.0f));

	oto=LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	//�w�i
	back_image = LoadGraph("Resource/Images/BackGround.png");

	tim_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
}
	
//�X�V����
void Scene::Update()
{
	//��
	PlaySoundMem(oto, DX_PLAYTYPE_LOOP,FALSE);
	animation_count++;
	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//Z�L�[����������G�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		if (b == nullptr)
		{
			b = CreateObject<Bomb>(objects[0]->GetLocation());
		}

	}
	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 1; i < objects.size(); i++)
	{

		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N
			HitCheckObject(objects[i], objects[j]);
		}
	}

	
	if (InputControl::GetKeyDown(KEY_INPUT_Y))
	{
		CreateObject<tama>(objects[2]->GetLocation());
	}

	//�c���Ă铖���蔻�������
	if (b != nullptr)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i] == b)
			{
				if (objects[i]->GetLocation().y > 400.0f && animation_count >= 180)
				{
					b->Finalize();
					delete b;
					objects.erase(objects.begin() + i);
					b = nullptr;
				}
			}
		}
	}	

}

//�`�揈��
void Scene::Draw()const
{
	DrawRotaGraph(320.0f, 230.0f, 0.7, 0, back_image, TRUE, 0);
	DrawRotaGraph(30.0f, 460.0, 0.6, 0, tim_image, TRUE, 0);
	DrawRotaGraph(300.0f, 460.0, 1, 0, hi, TRUE, 0);
	DrawRotaGraph(320.0f, 460.0, 1, 0, sc, TRUE, 0);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();

	}

	DrawFormatString(10, 10, GetColor(0, 0, 0), "%d", this->animation_count);
	

}

//�I��������
void Scene::Finalize()
{

	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}
	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	//���I�z��̊J��
	objects.clear();
}
#ifdef D_PIVOT_CENTER
//�����蔻��`�F�b�N�����i��`�̒��S�œ����蔻����Ƃ�j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�Q�I�u�W�F�N�g�̋���������
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫��������
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
//�����蔻��`�F�b�N����(���㒸��̍��W���瓖���蔻��v�Z���s���j
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W����������
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER


