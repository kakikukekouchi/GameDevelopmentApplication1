#pragma once
#include"../Objects/Enemy/Enemy.h"
#include"../Objects/Player/Player.h"
class GameMainScene
{
private:

	Player* player;			//ƒvƒŒƒCƒ„[
	Enemy** enemy;			//“G

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() ;
	virtual void Draw() const ;
	virtual void Finalize();



private:
	//“–‚½‚è”»’è
	bool IsHitCheck(Player* p, Enemy* e);
};

