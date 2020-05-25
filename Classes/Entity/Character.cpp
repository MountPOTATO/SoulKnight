#include "Character.h"

Character::Character() {}
Character::~Character() {}



bool Character::init() {
	m_HP = 1;
	m_MP = 1;
	m_Armor = 1;
	m_Speed = 1;
	setAnchorPoint(Point(0.5f, 0.5f));
	return true;
}





//设置四维
void Character::setHP(int hp) {
	m_HP = hp;
}
void Character::setMP(int mp) {
	m_MP = mp;
}
void Character::setArmor(int armor) {
	m_Armor = armor;
}
void Character::setSpeed(int speed) {//设置角色速度
	m_Speed = speed;
	 
}
//
int Character::getHP() { return m_HP; }
int Character::getMP() { return m_MP; }
int Character::getArmor() { return m_Armor; }
int Character::getSpeed() { return m_Speed; }

//以玩家为中心设置视角
void Character::setViewPointByCharacter() {
	if (getSprite() == NULL) { return; }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* parent = (Layer*)getParent();//
	Point characterPos = getPosition();//获取主角坐标
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPos = centerPos - characterPos;
	parent->setPosition(viewPos);

}

void Character::setTagPosition(int x, int y) {
	Entity::setTagPosition(x, y);
	setViewPointByCharacter();
}