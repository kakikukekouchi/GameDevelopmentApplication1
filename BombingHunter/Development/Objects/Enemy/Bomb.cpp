#include"Bomb.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"
#include"../../Utility/Vector2D.h"

//コンストラクタ
Bomb::Bomb() : animation()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
	animation_count = 0;
	image = NULL;
	
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	
	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/Bomb/Bomb.png");
	animation[1] = LoadGraph("Resource/Images/Blast/1.png");
	animation[2] = LoadGraph("Resource/Images/Blast/2.png");
	animation[3] = LoadGraph("Resource/Images/Blast/3.png");
	animation[4] = NULL;

	

	//エラーチェック
	if (animation[0] == -1)
	{
		throw("	とりパイロットの画像がありません\n");
	}
	image = animation[0];
	
	//向きの設定
	radian = 1.5;

	direction += Vector2D(0.0f, 1.0f);

	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		radian = DX_PI_F / 4 * 3;
		direction += Vector2D(-2.0f, 1.0f);
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		radian = DX_PI_F / 4;
		direction += Vector2D(1.5f, 1.0f);
	}
	else
	{
		radian = DX_PI_F / 2;
		direction += Vector2D(0.0f, 1.0f);

	}

	box_size = 40.0f;
}

//更新処理
void Bomb::Update()
{
	Movement();

	AnimeControl();

	
}
//描画処理
void Bomb::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.67, radian, image, TRUE);
	DrawFormatString(10, 26, GetColor(0, 0, 0), "%f", this->location.y);

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif
	

}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	
}
//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_Object)
{
	//当たった時の処理
	direction = 0;
}
//移動処理
void Bomb::Movement()
{
	
	if (location.y <= 400.0f)
	{
		location += direction;
	}
	
}
//アニメーション制御
void Bomb::AnimeControl()
{	 
	//フレームカウントを加算する
	animation_count++;

	//６０フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;
		

		
			if (location.y >= 400.0f)
			{
				radian = 0;
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
				else if (image == animation[3])
				{
					image = animation[4];
				}
			
			
			
		}
	}
}





