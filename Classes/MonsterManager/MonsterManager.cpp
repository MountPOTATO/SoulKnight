#include "MonsterManager/MonsterManager.h"
#include "Const/ConstInfo.h"
#include "Entity/Enemy/Ranger.h"
#include "Entity/Enemy/Charger.h"
#include "Entity/Enemy/Tower.h"
#include "Entity/Enemy/Mummy.h"
#include "HelloWorldScene.h"
#include <stdlib.h>
#include "Interaction/DirectPickThing.h"

bool MonsterManager::init() {
	
	this->scheduleUpdate();

	this->createMonster(1, Point(100, 600));//һ�������õĹ���
	
	return true;
}

MonsterManager* MonsterManager::create(Point pos, HelloWorld* scene, Character* character) {
	MonsterManager* ms = new(std::nothrow)MonsterManager;
	if (ms && ms->initWithData(pos, scene, character)) {
		ms->autorelease(); return ms; 
	}
	CC_SAFE_DELETE(ms);
	return nullptr;

}

bool MonsterManager::initWithData(Point pos, HelloWorld* scene, Character* character) {
	this->setPosition(pos);
	currentScene = scene;
	bindCharacter(character);
	setTiledMap(currentScene->_map);
	return true;
}

void MonsterManager::update(float delta) {
	//��������
	if (this->getPosition().distance(m_Character->getPosition()) <=350.0f && m_isUsed == false) {
		srand((unsigned)time(NULL));
		int monsterNum = rand() % 5 + 4;
		spawnLotsOfMonsters(this->getPosition(), 350.f, monsterNum);
		m_isUsed = true;
	}
	//����ײ��
	for (auto monster : currentScene->_currentEnemy) {
		
		if (monster->isCollideWithCharacter(m_Character)) {
			m_Character->hit(HIT_WHEN_COLLIDE_WITH_ENEMY, monster->getPosition());

		}
	}
	//��������
	for (auto i = currentScene->_currentEnemy.begin(); i != currentScene->_currentEnemy.end();) {
		if ((*i)->getHP() <= 0) {
			(*i)->getSprite()->setVisible(false);

			

			i = currentScene->_currentEnemy.erase(i);

			

		}
		else i++;
	}
}

void MonsterManager::bindCharacter(Character* character) {
	m_Character = character;
}

void MonsterManager::createMonster(int MonsterID, Point monsterSpawnPoint) {
	Monster* monster = Monster::create();
	switch (MonsterID)
	{
	case 1: {
		monster = Ranger::create();

		break;
	}
	case 2:
		monster = Tower::create();
		break;
	case 3:
		monster = Charger::create();
		break;
	case 4:
		monster = Mummy::create();
		break;

	default:
		break;
	}
	monster->bindCharacter(m_Character);
	monster->setVisible(true);
	monster->currentScene = this->currentScene;
	currentScene->_currentEnemy.pushBack(monster);
	currentScene->addChild(monster);


	monster->setTiledMap(currentScene->_map);
	monster->setPosition(monsterSpawnPoint);
	/*m_MonsterArray.pushBack(monster);*/

}

void MonsterManager::spawnLotsOfMonsters(Point spawnPoint, float rad, int spawnNum) {
	int i = 0;
	while (i<spawnNum){
		auto randomPoint = spawnPoint + Point(
			(CCRANDOM_0_1() - CCRANDOM_0_1()) * CCRANDOM_0_1() * rad,
			(CCRANDOM_0_1() - CCRANDOM_0_1()) * CCRANDOM_0_1() * rad);	//�������һ����
		auto x = randomPoint.x;
		auto y = randomPoint.y;
		if (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))) { continue; }
		if (isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))) { continue; }
		if (isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))) { continue; }
		if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) { continue; }//���������Ƿ��ڵ�
		
		createMonster((int)(4 * CCRANDOM_0_1() + 1), randomPoint);
		i++;//�ɹ�������
	}
}
bool MonsterManager::isPosBlocked(Point dstPos) {

	//��ȱ*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));

	int tiledGid = meta->getTileGIDAt(tiledPos);//��ȡ������ӵ�Ψһ��ʶ



	//�ж���������Ƿ����
	if (tiledGid != 0) {

		auto propMap = m_map->getPropertiesForGID(tiledGid).asValueMap();


		if (propMap.find("Collidable") != propMap.end()) {
			//��ȡ���ӵ�Collidable����
			Value prop = propMap.at("Collidable");
			if (prop.asString().compare("true") == 0) {
				//���������������Ϊtrue��������Ҽ����ƶ�
				return true;
			}
		}

	}
	return false;//��֮������false
}
void MonsterManager::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}
Point MonsterManager::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;


	return Point(x, y);
}