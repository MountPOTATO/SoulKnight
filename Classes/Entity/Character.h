#pragma once
#include "Entity.h"
#include "cocos2d.h"

class Character :public Entity {
public:
	CREATE_FUNC(Character);
	Character();
	~Character();
	virtual bool init();

public:
	void setHP(int hp);
	void setMP(int mp);
	void setArmor(int armor);
	void setSpeed(int speed);

private:
	int m_HP;
	int m_MP;
	int m_Armor;
	int m_Speed;

};