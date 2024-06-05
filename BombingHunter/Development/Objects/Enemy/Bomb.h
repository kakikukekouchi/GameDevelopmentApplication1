
#pragma once
#include"../GameObject.h"
class Bomb :public GameObject
{
private:
	Vector2D  direction;
	int animation[4];   //�A�j���[�V�����摜
	int image;
	int animation_count; //�A�j���[�V��������
public:
	Bomb();
	~Bomb();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I��������

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();
	
};



