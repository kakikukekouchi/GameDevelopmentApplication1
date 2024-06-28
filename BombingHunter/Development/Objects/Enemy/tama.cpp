#include "tama.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"../../Utility/Vector2D.h"

//コンストラクタ
tama::tama() : animation()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation_count = 0;
	image = NULL;
}

//デストラクタ
tama::~tama()
{

}

//初期化処理
void tama::Initialize()
{

	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/EnemyBullet/1.png");
	animation[1] = LoadGraph("Resource/Images//EnemyBullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images//EnemyBullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images//EnemyBullet/eff3.png");



	//エラーチェック
	if (animation[0] == -1)
	{
		throw("	とりパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 1.5;

	direction += Vector2D(0.0f, 1.5f);

	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		radian = 2.0;
		direction += Vector2D(-1.5f, 1.0f);
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		radian = 1.0;
		direction += Vector2D(1.5f, 1.0f);
	}


}

//更新処理
void tama::Update()
{
	Movement();

	AnimeControl();

}
//描画処理
void tama::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.67, radian, animation[0], TRUE);


}

//終了時処理
void tama::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);

}
//当たり判定通知処理
void tama::OnHitCollision(GameObject* hit_Object)
{
	//当たった時の処理
	direction = 0;
}
//移動処理
void tama::Movement()
{
	location += direction;
}
//アニメーション制御
void tama::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 10)
	{
		//カウントのリセット
		animation_count = 0;

		if (location.y >= 60.0f)
		{
			//画像の切り替え
			if (image == animation[0])
			{
				image = animation[1];
			}
			else if (image == animation[1])
			{
				image = animation[2];
			}
			else if (image == animation[2])
			{
				image = animation[3];
			}
		}
	}
}