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
	int attack();
	void setTiledMap(TMXTiledMap* map);
	void bindCharacter(Character* character);
	Point tileCoordForPosition(Point pos);
	bool isActivated;//怪物是否处于活动状态
	float lastAAttackTime;
	TMXTiledMap* m_map;
	TMXLayer* meta;

	Character* m_character;

private:
	int m_HP;
	int m_Speed;
	float m_AtkSpeed;//两次攻击间隔
	int m_Atk;//攻击力
};