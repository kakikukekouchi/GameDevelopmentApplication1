
#pragma once
#include"../GameObject.h"
class Bomb :public GameObject
{
private:
	Vector2D  direction;
	int animation[4];   //アニメーション画像
	int image;
	int animation_count; //アニメーション時間
public:
	Bomb();
	~Bomb();

	void Initialize();  //初期化処理
	void Update();      //更新処理
	void Draw() const;  //描画処理
	void Finalize();    //終了時処理

private:
	//移動処理
	void Movement();
	//アニメーション制御
	void AnimeControl();
	
};



