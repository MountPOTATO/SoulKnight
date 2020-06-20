#include "Knight.h"
#include "Const/ConstInfo.h"

bool Knight::init() {
	setMaxHP(KNIGHT_HP);
	setMaxMP(KNIGHT_MP);
	setMaxArmor(KNIGHT_ARMOR);
	setHP(max_HP);
	setMP(max_MP);
	setArmor(max_Armor);
	setSpeed(KNIGHT_SPEED);
	isTakingDamage = false;
	isInvincible = false;
	isAlive = true;
	
	Sprite* sprite=Sprite::create("Characters/Knight.png");
	this->setAnchorPoint(Point(0.5f, 0.5f));
	this->bindSprite(sprite);
	return true;
}

bool Knight::UseSkill() {
	return true;
}

