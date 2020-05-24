#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#define PI  3.14159
USING_NS_CC;

class Weapon;
class WeaponBuff;
class Entity;
class Buff;

class Bullet :public cocos2d::Sprite {
private:
	CC_SYNTHESIZE(float,_attack, Attack);
	CC_SYNTHESIZE(float,_flyingSpeed, FlyingSpeed);
	CC_SYNTHESIZE(Weapon*, _shooter, Shooter);
	CC_SYNTHESIZE(Entity*, _target, Target);
	CC_SYNTHESIZE(WeaponBuff*,_buff, Buff);

public:
	virtual bool init
	(const char* bulletImageName, float attack, float flyingSpeed, Weapon* shooter, Entity* target, WeaponBuff* buff);

	static Bullet* create
	(const char* bulletImageName, float attack, float flyingSpeed, Weapon* shooter, Entity* target, WeaponBuff* buff);

	void calPosition();

	void calDistance();

};




#endif