#pragma once
#include"../GameObject.h"
class BackGround :public GameObject
{
private:
	int animation;   //�A�j���[�V�����摜

public:
	BackGround();
	~BackGround();

	void Initialize() ;  //����������
	void Update() ;      //�X�V����
	void Draw() const ;  //�`�揈��
	void Finalize();    //�I��������

};


