#pragma once
#include"../GameObject.h"
class BackGround :public GameObject
{
private:
	int animation;   //アニメーション画像

public:
	BackGround();
	~BackGround();

	void Initialize() ;  //初期化処理
	void Update() ;      //更新処理
	void Draw() const ;  //描画処理
	void Finalize();    //終了時処理

};


