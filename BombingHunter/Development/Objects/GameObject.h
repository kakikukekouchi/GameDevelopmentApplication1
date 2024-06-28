#pragma once
#define D_PIVOT_CENTER
#include"../Utility/Vector2D.h"

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D box_size;    //��`�̑傫��
	Vector2D location;    //�ʒu���
	double radian;        //����
	int image;            //�`�悷��摜
	int sound;            //�Đ����鉹��
	int type;			  //�I�u�W�F�N�g�̃^�C�v
public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();  //����������
	virtual void Update();      //�X�V����
	virtual void Draw()const;   //�`�揈��
	virtual void Finalize();    //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu��񏊓�����
	Vector2D GetLocation()const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);
	//�^�C�v���ύX����
	void Settyp(int Objecttype);
	//�^�C�v��񏊓�����
	int  Gettyp();

	//�����蔻��̑傫������������
	Vector2D GetBoxSize() const;
};

