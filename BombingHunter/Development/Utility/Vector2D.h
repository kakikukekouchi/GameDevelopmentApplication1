#pragma once
class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D();				//Vector2D�̃R���X�g���N�^
	Vector2D(float scalar);//Vector2D�̃R���X�g���N�^
	Vector2D(float mx, float my);//Vector2D�̃R���X�g���N�^

	~Vector2D();			//Vector2D�̃f�X�g���N�^

public:

	//���Z�q�I�[�o�[���[�h��������
	Vector2D& operator=(const Vector2D& location);

	const Vector2D operator+(const Vector2D& location)const;
	Vector2D& operator +=(const Vector2D& location);

	const Vector2D operator-(const Vector2D& location)const;
	Vector2D& operator -=(const Vector2D& location);

	const Vector2D operator*(const float& scalar)const;
	const Vector2D operator*(const Vector2D& location)const;
	Vector2D& operator*=(const float& scalar);
	Vector2D& operator*=(const Vector2D& location);

	const Vector2D operator/(const float& scalar)const;
	const Vector2D operator/(const Vector2D& location)const;
	Vector2D& operator/=(const float& scalar);
	Vector2D& operator/=(const Vector2D& location);
	//���Z�q�I�[�o�[���[�h�����܂�

	//�����^�f�[�^�ɕϊ�
	void ToInt(int* x, int* y)const;
};

