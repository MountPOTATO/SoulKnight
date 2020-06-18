#include "MonsterManager/MonsterManager.h"
#include "Const/ConstInfo.h"
#include "Entity/Enemy/Ranger.h"
bool MonsterManager::init() {
	this->scheduleUpdate();

	this->createMonster(1, Point(100, 600));//һ�������õĹ���
	






	
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

void MonsterManager::spawnLotsOfMonsters(Point spawnPoint, float rad, int spawnNum) {
	int i = 0;
	while (i<spawnNum){
		auto randomPoint = spawnPoint + Point(
			(CCRANDOM_0_1() - CCRANDOM_0_1()) * CCRANDOM_0_1() * rad,
			(CCRANDOM_0_1() - CCRANDOM_0_1()) * CCRANDOM_0_1() * rad);	//�������һ����
		auto x = randomPoint.x;
		auto y = randomPoint.y;
		if (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))) { return; }
		if (isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))) { return; }
		if (isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))) { return; }
		if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) { return; }//���������Ƿ��ڵ�
		createMonster(1, randomPoint);
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