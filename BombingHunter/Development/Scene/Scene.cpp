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
#include"DxLib.h"


//コンストラクタ
Scene::Scene() : objects()
{

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
	//背景
	CreateObject<BackGround>(Vector2D(320.0f, 240.0f));
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(60.0f, 60.0f));
	//エネミィーを生成する
	CreateObject<Enemy>(Vector2D(350.0f, 350.0f));
	//エネミィー2を生成する
	CreateObject<Enemy2>(Vector2D(300.0f, 300.0f));
	//エネミィー３を生成する
	CreateObject<Enemy3>(Vector2D(250.0f, 250.0f));
	//エネミィー４を生成する
	CreateObject<Enemy4>(Vector2D(200.0f, 200.0f));
	
}
//更新処理
void Scene::Update()
{
	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
	//Zキーを押したら敵を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Bomb>(objects[1]->GetLocation());

	}
}

//描画処理
void Scene::Draw()const
{
	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
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


