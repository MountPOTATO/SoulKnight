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
	float getAtkSpeed();//获取攻击间隔
	int getAtk();//获取攻击力
	void setHP(int hp);
	void setSpeed(int speed);
	void setAtkSpeed(float atkSpeed);
	void setAtk(int atk);
	virtual int attack() = 0;
	float lastAAttackTime;
private:
	int m_HP;
	int m_Speed;
	float m_AtkSpeed;//两次攻击间隔
	int m_Atk;//攻击力
};