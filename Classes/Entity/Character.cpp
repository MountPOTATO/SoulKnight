#include "Character.h"

Character::Character() {}
Character::~Character() {}



bool Character::init() {
	m_HP = 0;
	m_MP = 0;
	m_Armor = 0;
	m_Speed = 0;
	return true;
}





//…Ë÷√ÀƒŒ¨
void Character::setHP(int hp) {
	m_HP = hp;
}
void Character::setMP(int mp) {
	m_MP = mp;
}
void Character::setArmor(int armor) {
	m_Armor = armor;
}
void Character::setSpeed(int speed) {
	m_Speed = speed;
}
//