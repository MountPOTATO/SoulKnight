#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"

class HelloWorld;



class Charger :public Monster {
public:
	CREATE_FUNC(Charger);
	virtual bool init();
	void update(float delta);
public:
	void chargeTowardsPos(Point dstPos);//朝某个方向快速冲锋
	void calDistance();//怪物移动
	bool isAiMoving;//是否正在自行移动
	bool isPosBlocked(Point dstPos);


public:
	MovingDir nextMovingDir;//储存当前移动方向
	int nextMovingDistance;//预计的最大移动距离
	int remainChargingDistance;
	int remainMovingDistance;


private:
	int monsterID = 1;//仅作为标识
	int _HP;
	int _Speed;
};