#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"

class Ranger :public Monster {
public:
	CREATE_FUNC(Ranger);
	virtual bool init();

public:
	
	
private:
	int monsterID = 1;//仅作为标识
	int _HP;
	int _Speed;
};