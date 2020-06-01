#ifndef __GUN_H__
#define __GUN_H__

#include "Arms/Weapon.h"

class Gun :public Weapon {

	
	//固有属性
	CC_SYNTHESIZE(INT32, _bulletPerTime, BulletPerTime);//设想一次攻击射出子弹数

	CC_SYNTHESIZE(float,_movingSpeedDecrease, MovingSpedDecrease);//设想，发射子弹（即处于攻击状态下的发射状态)


	CC_SYNTHESIZE(const char*, _bulletImageName, BulletImageName);//设想一次攻击射出子弹数

public:
	
	static Gun* create
	(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual void updateTarget();

	virtual bool attack();

	virtual bool runShootingAction();

	virtual bool startWeapon(bool _isStopOther);
	
	
};

#endif