#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
USING_NS_CC;

class MonsterManager :public Node {
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();

	virtual void update(float delta);

	void bindCharacter(Character* character);
public:
	void createMonster(int MonsterID,Point monsterSpawnPoint);//����id��������
private:
	Character* m_Character;
	Vector<Monster*>m_MonsterArray;//��Ź����б�
};