#include "Enemy.h"
#include"../../Utility/InputControl.h"
#include"DxLib.h"

//コンストラクタ
Enemy::Enemy() :animation_count(0), filp_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("	とりパイロットの画像がありません\n");
	}



	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];

	// 初期進行方向の認定
		direction = Vector2D(1.0f, -0.5f);
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}
//描画処理
void Enemy::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, filp_flag);
	//進行方向によって、反転状態を決定する

	//画像反転フラグ
	int flip_flag = FALSE;

	if (direction.x < 1.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}
	//情報を基にハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 0.5, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + ( box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_Object)
{
	
	//当たった時の処理
	direction = 0.0f;
}

//移動処理
void Enemy::Movement()
{
	////画面端に到達したら、進行方向を反転する
	//if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	//{
	//	direction.x *= -1.0f;
	//}
	//右へ移動し続ける
	location.x += 0.5f;
	//右壁から左壁
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}
	////信仰情報に向かって、位置情報を変更する
	//location += direction;

	//移動の速さ
	Vector2D velocity = 0.0f;

	velocity. x = 1.0f;

	

	//現在の位置座標に速さを加算する
 location += velocity;
}

//アニメーション制御
void Enemy::AnimeControl()
{
	//フレームカウントを加算するz
	animation_count++;

	//3０フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
