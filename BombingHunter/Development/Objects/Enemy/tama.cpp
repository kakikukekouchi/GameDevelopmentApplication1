#include "tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"../../Utility/Vector2D.h"

//�R���X�g���N�^
tama::tama() : animation()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation_count = 0;
	image = NULL;
}

//�f�X�g���N�^
tama::~tama()
{

}

//����������
void tama::Initialize()
{

	//�摜�̓Ǎ���
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images//EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images//EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images//EnemyBullet/eff3.png");



	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("	�Ƃ�p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 1.5;

	direction += Vector2D(0.0f, 1.5f);

	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		radian = 2.0;
		direction += Vector2D(-1.5f, 1.0f);
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		radian = 1.0;
		direction += Vector2D(1.5f, 1.0f);
	}


}

//�X�V����
void tama::Update()
{
	Movement();

	AnimeControl();

}
//�`�揈��
void tama::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.67, radian, animation[0], TRUE);


}

//�I��������
void tama::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);

}
//�����蔻��ʒm����
void tama::OnHitCollision(GameObject* hit_Object)
{
	//�����������̏���
	direction = 0;
}
//�ړ�����
void tama::Movement()
{
	location += direction;
}
//�A�j���[�V��������
void tama::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 10)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		if (location.y >= 60.0f)
		{
			//�摜�̐؂�ւ�
			if (image == animation[0])
			{
				image = animation[1];
			}
			else if (image == animation[1])
			{
				image = animation[2];
			}
			else if (image == animation[2])
			{
				image = animation[3];
			}
		}
	}
}