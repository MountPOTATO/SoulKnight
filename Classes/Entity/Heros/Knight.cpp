#include "Knight.h"
#include "Const/ConstInfo.h"

bool Knight::init() {
	setHP(KNIGHT_HP);
	setMP(KNIGHT_MP);
	setSpeed(KNIGHT_SPEED);
	setArmor(KNIGHT_ARMOR);
	Sprite* sprite=Sprite::create("Characters/Knight.png");
	this->setAnchorPoint(Point(0.5f, 0.5f));
	this->bindSprite(sprite);
	return true;
}

bool Knight::UseSkill() {
	return true;
}