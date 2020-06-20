#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
#include "Const/ConstInfo.h"
class HelloWorld;


class Tower :public Monster {
public:
	CREATE_FUNC(Tower);
	virtual bool init();
	void update(float delta);
public:


	void calDistance();//怪物移动
	bool isAiMoving;//是否正在自行移动
	bool isPosBlocked(Point dstPos);


public:

	MovingDir nextMovingDir;//储存当前移动方向
	int nextMovingDistance;//预计的最大移动距离
	int remainMovingDistance;//剩余移动步数

private:
	int monsterID = 1;//仅作为标识
	int _HP;
	int _Speed;

};