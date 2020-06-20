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
	bool isCollideWithCharacter(Character* character);//����Ƿ��������ײ
	int getHP();
	int getSpeed();
	float getAtkSpeed();//��ȡ�������
	int getAtk();//��ȡ������
	void setHP(int hp);
	void setSpeed(int speed);
	void setAtkSpeed(float atkSpeed);
	void setAtk(int atk);

	void setTiledMap(TMXTiledMap* map);

	virtual void attack(HelloWorld* scene);
	Point tileCoordForPosition(Point pos);
	bool isActivated;//�����Ƿ��ڻ״̬
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
	float m_AtkSpeed;//���ι������
	int m_Atk;//������


	
	float _lastAttackTime;
	float _attackTimeSpace = 2.0f;

protected:
	int m_monsterID;
	int m_isUsed = false;
};