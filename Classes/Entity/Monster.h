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
	
public:

private:
	int m_HP;
	int m_Speed;
};