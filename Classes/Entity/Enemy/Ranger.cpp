#include "Entity/Enemy/Ranger.h"

bool Ranger::init() {
	Sprite* sprite = Sprite::create("Enemy\\Ranger.png");
	this->bindSprite(sprite);
	setAnchorPoint(Point(0.5f, 0.5f));
	setSpeed(RANGER_SPEED);
	setHP(RANGER_HP);




	return true;
}

 int Ranger::attack() {
	 //ÄÚÈÝ´ý¶¨
	 return 0;
}