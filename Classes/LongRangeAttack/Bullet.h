#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "Arms/Weapon.h"
#include "Buff/WeaponBuff.h"

#define PI  3.14159
USING_NS_CC;

//
//class Entity;


class Bullet :public Sprite {
private:
	CC_SYNTHESIZE(float,_attack, Attack);
	CC_SYNTHESIZE(float,_flyingSpeed, FlyingSpeed);
	CC_SYNTHESIZE(Weapon*, _shooter, Shooter);
	/*CC_SYNTHESIZE(Entity*, _target, Target);*/
	CC_SYNTHESIZE(WeaponBuff*,_buff, Buff);

	CC_SYNTHESIZE(float, _initAngle, InitAngle);
	CC_SYNTHESIZE(bool, _hasDeflection, HasDeflection);//ÊÇ·ñÓÐÆ«½Ç

public:
	virtual bool init
	(const char* bulletImageName,  float flyingSpeed, Weapon* shooter,  WeaponBuff* buff,bool hasDef);

	static Bullet* create
	(const char* bulletImageName, float flyingSpeed, Weapon* shooter,  WeaponBuff* buff, bool hasDef);

	void calPosition();

	void calDistance();
	INT32 getBulletAttack()const { return _attack; }

};




#endif