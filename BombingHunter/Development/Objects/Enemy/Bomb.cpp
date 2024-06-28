#include"Bomb.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"../../Utility/Vector2D.h"

//�R���X�g���N�^
Bomb::Bomb() : animation()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
	animation_count = 0;
	image = NULL;
	
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	
	//�摜�̓Ǎ���
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");
	animation[4] = NULL;

	

	//�G���[�`�F�b�N
	if (animation[0] == -1)
	{
		throw("	�Ƃ�p�C���b�g�̉摜������܂���\n");
	}
	image = animation[0];
	
	//�����̐ݒ�
	radian = 1.5;

	direction += Vector2D(0.0f, 1.0f);

	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		radian = DX_PI_F / 4 * 3;
		direction += Vector2D(-2.0f, 1.0f);
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		radian = DX_PI_F / 4;
		direction += Vector2D(1.5f, 1.0f);
	}
	else
	{
		radian = DX_PI_F / 2;
		direction += Vector2D(0.0f, 1.0f);

	}

	box_size = 40.0f;
}

//�X�V����
void Bomb::Update()
{
	Movement();

	AnimeControl();

	
}
//�`�揈��
void Bomb::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.67, radian, image, TRUE);
	DrawFormatString(10, 26, GetColor(0, 0, 0), "%f", this->location.y);

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif
	

}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	
}
//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_Object)
{
	//�����������̏���
	direction = 0;
}
//�ړ�����
void Bomb::Movement()
{
	
	if (location.y <= 400.0f)
	{
		location += direction;
	}
	
}
//�A�j���[�V��������
void Bomb::AnimeControl()
{	 
	//�t���[���J�E���g�����Z����
	animation_count++;

	//�U�O�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;
		

		
			if (location.y >= 400.0f)
			{
				radian = 0;
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
				else if (image == animation[3])
				{
					image = animation[4];
				}
			
			
			
		}
	}
}





