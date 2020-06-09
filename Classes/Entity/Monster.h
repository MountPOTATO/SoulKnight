#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Entity/Character.h"
USING_NS_CC;

class Monster :public Entity {
public:
	CREATE_FUNC(Monster);
	
	
	virtual bool init();
	
public:
	bool isCollideWithCharacter(Character* character);//检测是否与玩家相撞

	int getHP();
	int getSpeed();
	void setHP(int hp);
	void setSpeed(int speed);

private:
	int m_HP;
	int m_Speed;
};