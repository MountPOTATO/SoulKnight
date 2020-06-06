#include "MonsterManager/MonsterManager.h"
#include "Const/ConstInfo.h"
#include "Entity/Enemy/Ranger.h"
bool MonsterManager::init() {
	this->scheduleUpdate();

	this->createMonster(1, Point(100, 400));//一个测试用的怪物
	






	
	return true;
}

void MonsterManager::update(float delta) {
	for (auto monster : m_MonsterArray) {
		if (monster->isCollideWithCharacter(m_Character)) {
			m_Character->hit(HIT_WHEN_COLLIDE_WITH_ENEMY, monster->getPosition());

		}
	}
}

void MonsterManager::bindCharacter(Character* character) {
	m_Character = character;
}

void MonsterManager::createMonster(int MonsterID, Point monsterSpawnPoint) {
	Monster* monster = Monster::create();
	switch (MonsterID)
	{
	case 1:
		monster = Ranger::create();
	default:
		break;
	}
	monster->setPosition(monsterSpawnPoint);
	m_MonsterArray.pushBack(monster);
	this->addChild(monster);
}