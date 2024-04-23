#pragma once
class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D();				//Vector2Dのコンストラクタ
	Vector2D(float scalar);//Vector2Dのコンストラクタ
	Vector2D(float mx, float my);//Vector2Dのコンストラクタ

	~Vector2D();			//Vector2Dのデストラクタ

public:

	//演算子オーバーロードここから
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
	//演算子オーバーロードここまで

	//整数型データに変換
	void ToInt(int* x, int* y)const;
};

