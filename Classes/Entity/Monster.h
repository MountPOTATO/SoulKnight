#pragma once
#include "Entity.h"
#include "cocos2d.h"
USING_NS_CC;

class Monster :public Entity {
public:
	CREATE_FUNC(Monster);
	Monster();
	~Monster();
	virtual bool init();
	int monsterType;//��������
public:

private:
	int m_HP;
	int m_Speed;
};