#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"

class Ranger :public Monster {
public:
	CREATE_FUNC(Ranger);
	bool init();

public:
	//��ȡ����
	int getHP();
	void setHP(int hp);

private:
	int _HP;
	int _Speed;
};