#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Entity/Character.h"
USING_NS_CC;

class HelloWorld;

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

	void setTiledMap(TMXTiledMap* map);

	virtual void attack(HelloWorld* scene);
	Point tileCoordForPosition(Point pos);
	bool isActivated;//怪物是否处于活动状态
	float lastAAttackTime;
	TMXTiledMap* m_map;
	TMXLayer* meta;
	void bindCharacter(Character* character);
	HelloWorld* currentScene;

	Character* m_character;

	int getMonsterID()const { return m_monsterID; }
	bool getIsUsed()const { return m_isUsed; }


private:
	int m_HP;
	int m_Speed;
	float m_AtkSpeed;//两次攻击间隔
	int m_Atk;//攻击力


	
	float _lastAttackTime;
	float _attackTimeSpace = 2.0f;

protected:
	int m_monsterID;
	int m_isUsed = false;
};