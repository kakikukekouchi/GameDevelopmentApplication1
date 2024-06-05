#include "BackGround.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
BackGround::BackGround() : animation(NULL)
{

}

//デストラクタ
BackGround::~BackGround()
{

}

//初期化処理
void BackGround::Initialize()
{
	//画像の読込み
	animation = LoadGraph("Resource/Images/BackGround.png");
	
	//エラーチェック
	if (animation == -1)
	{
		throw("	とりパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0;

}

//更新処理
void BackGround::Update()
{
	
	
}
//描画処理
void BackGround::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.67, radian, animation, TRUE);

	
}

//終了時処理
void BackGround::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation);
	
}







