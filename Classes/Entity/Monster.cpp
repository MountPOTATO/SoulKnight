#include "Entity/Monster.h"

bool Monster::init() {
	return true;
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
void Monster::setHP(int hp) {
	m_HP = hp;
}
void Monster::setSpeed(int speed) {
	m_Speed = speed;
}