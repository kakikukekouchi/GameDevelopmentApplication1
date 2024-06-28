#include "Scene.h"
#include"../Utility/InputControl.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Enemy/Enemy2.h"
#include"../Objects/Enemy/Enemy3.h"
#include"../Objects/Enemy/Enemy4.h"
#include"../Objects/Enemy/BackGround.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Bomb.h"
#include"../Objects/Enemy/tama.h"
#include"../Objects/GameObject.h"
#include"DxLib.h"


Bomb* b = nullptr;

//コンストラクタ
Scene::Scene() : objects(),back_image(NULL),tim_image(),tim(),sc(),hi(),oto(NULL),enemy_count(),count()
{
	animation_count = 0;
	enemy_count = NULL;
	count = NULL;
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(300.0f, 60.0f));
	//エネミィーを生成する
	CreateObject<Enemy>(Vector2D(350.0f, 350.0f));
	//エネミィーを生成する
	CreateObject<Enemy>(Vector2D(240.0f, 350.0f));
	//エネミィーを生成する
	CreateObject<Enemy>(Vector2D(150.0f, 350.0f));
	//エネミィー2を生成する
	CreateObject<Enemy2>(Vector2D(200.0f, 100.0f));
	//エネミィー2を生成する
	CreateObject<Enemy2>(Vector2D(100.0f, 120.0f));
	//エネミィー2を生成する
	CreateObject<Enemy2>(Vector2D(300.0f, 120.0f));
	//エネミィー３を生成する
	CreateObject<Enemy3>(Vector2D(100.0f, 350.0f));
	//エネミィー４を生成する
	CreateObject<Enemy4>(Vector2D(200.0f, 200.0f));
	//エネミィー４を生成する
	CreateObject<Enemy4>(Vector2D(100.0f, 200.0f));
	//エネミィー４を生成する
	CreateObject<Enemy4>(Vector2D(50.0f, 200.0f));

	oto=LoadSoundMem("Resource/Sounds/Evaluation/BGM_arrows.wav");
	//背景
	back_image = LoadGraph("Resource/Images/BackGround.png");

	tim_image = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
}
	
//更新処理
void Scene::Update()
{
	//音
	PlaySoundMem(oto, DX_PLAYTYPE_LOOP,FALSE);
	animation_count++;
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//Zキーを押したら敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		if (b == nullptr)
		{
			b = CreateObject<Bomb>(objects[0]->GetLocation());
		}

	}
	//オブジェクト同士の当たり判定チェック
	for (int i = 1; i < objects.size(); i++)
	{

		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック
			HitCheckObject(objects[i], objects[j]);
		}
	}

	
	if (InputControl::GetKeyDown(KEY_INPUT_Y))
	{
		CreateObject<tama>(objects[2]->GetLocation());
	}

	//残ってる当たり判定を消す
	if (b != nullptr)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i] == b)
			{
				if (objects[i]->GetLocation().y > 400.0f && animation_count >= 180)
				{
					b->Finalize();
					delete b;
					objects.erase(objects.begin() + i);
					b = nullptr;
				}
			}
		}
	}	

}

//描画処理
void Scene::Draw()const
{
	DrawRotaGraph(320.0f, 230.0f, 0.7, 0, back_image, TRUE, 0);
	DrawRotaGraph(30.0f, 460.0, 0.6, 0, tim_image, TRUE, 0);
	DrawRotaGraph(300.0f, 460.0, 1, 0, hi, TRUE, 0);
	DrawRotaGraph(320.0f, 460.0, 1, 0, sc, TRUE, 0);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();

	}

	DrawFormatString(10, 10, GetColor(0, 0, 0), "%d", this->animation_count);
	

}

//終了時処理
void Scene::Finalize()
{

	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}
	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	//動的配列の開放
	objects.clear();
}
#ifdef D_PIVOT_CENTER
//当たり判定チェック処理（矩形の中心で当たり判定をとる）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//２つオブジェクトの距離を所得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを所得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else
//当たり判定チェック処理(左上頂上の座標から当たり判定計算を行う）
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を所得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER


