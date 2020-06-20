#include "Entity/Monster.h"


bool Monster::init() {

	return true;
}
void Monster::bindCharacter(Character* character) {
	m_character = character;
}
void Monster::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}

bool Monster::isCollideWithCharacter(Character* character) {
	Rect entityRect = character->getBoundingBox();
	Rect monsterRect = this->getBoundingBox();
	Point monsterPos = getPosition();
	return entityRect.intersectsRect(monsterRect);
}

int Monster::getHP() {
	return m_HP;
}

int Monster::getSpeed() {
	return m_Speed;
}
float Monster::getAtkSpeed() {
	return m_AtkSpeed;
}
int Monster::getAtk() {
	return m_Atk;
}
void Monster::setHP(int hp) {
	m_HP = hp;
}
void Monster::setSpeed(int speed) {
	m_Speed = speed;
}
void Monster::setAtkSpeed(float atkSpeed) {
	m_AtkSpeed = atkSpeed;
}
void Monster::setAtk(int atk){
	m_Atk = atk;
}
int Monster::attack() {
	return 0;

}

Point Monster::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;


	return Point(x, y);
}