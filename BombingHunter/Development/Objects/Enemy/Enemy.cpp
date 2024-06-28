#include "Enemy.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓Ǎ���
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("	�Ƃ�p�C���b�g�̉摜������܂���\n");
	}



	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	box_size = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	// �����i�s�����̔F��
		direction = Vector2D(1.0f, -0.5f);
}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimeControl();
}
//�`�揈��
void Enemy::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, filp_flag);
	//�i�s�����ɂ���āA���]��Ԃ����肷��

	//�摜���]�t���O
	int flip_flag = FALSE;

	if (direction.x < 1.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}
	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + ( box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_Object)
{
	
	//�����������̏���
	direction = 0.0f;
}

//�ړ�����
void Enemy::Movement()
{
	////��ʒ[�ɓ��B������A�i�s�����𔽓]����
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
	//	direction.x *= -1.0f;
	//}
	//�E�ֈړ���������
	location.x += 0.5f;
	//�E�ǂ��獶��
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}
	////�M���Ɍ������āA�ʒu����ύX����
	//location += direction;

	//�ړ��̑���
	Vector2D velocity = 0.0f;

	velocity. x = 1.0f;

	

	//���݂̈ʒu���W�ɑ��������Z����
 location += velocity;
}

//�A�j���[�V��������
void Enemy::AnimeControl()
{
	//�t���[���J�E���g�����Z����z
	animation_count++;

	//3�O�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
