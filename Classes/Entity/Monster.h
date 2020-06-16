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
	bool isCollideWithCharacter(Character* character);//����Ƿ��������ײ

	int getHP();
	int getSpeed();
	float getAtkSpeed();//��ȡ�������
	int getAtk();//��ȡ������
	void setHP(int hp);
	void setSpeed(int speed);
	void setAtkSpeed(float atkSpeed);
	void setAtk(int atk);
	virtual int attack() = 0;
	float lastAAttackTime;
private:
	int m_HP;
	int m_Speed;
	float m_AtkSpeed;//���ι������
	int m_Atk;//������
};