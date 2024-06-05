#include "BackGround.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//�R���X�g���N�^
BackGround::BackGround() : animation(NULL)
{

}

//�f�X�g���N�^
BackGround::~BackGround()
{

}

//����������
void BackGround::Initialize()
{
	//�摜�̓Ǎ���
	animation = LoadGraph("Resource/Images/BackGround.png");
	
	//�G���[�`�F�b�N
	if (animation == -1)
	{
		throw("	�Ƃ�p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0;

}

//�X�V����
void BackGround::Update()
{
	
	
}
//�`�揈��
void BackGround::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.67, radian, animation, TRUE);

	
}

//�I��������
void BackGround::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation);
	
}







