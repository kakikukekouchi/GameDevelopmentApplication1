#pragma once
#include"../GameObject.h"
class tama :public GameObject
{
private:
	Vector2D  direction;
	int animation[4];   //�A�j���[�V�����摜

	int animation_count; //�A�j���[�V��������
public:
	tama();
	~tama();

	void Initialize();  //����������
	void Update();      //�X�V����
	void Draw() const;  //�`�揈��
	void Finalize();    //�I��������
	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object)override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimeControl();

};
