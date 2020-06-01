#ifndef __GUN_H__
#define __GUN_H__

#include "Arms/Weapon.h"

class Gun :public Weapon {

	
	//��������
	CC_SYNTHESIZE(INT32, _bulletPerTime, BulletPerTime);//����һ�ι�������ӵ���

	CC_SYNTHESIZE(float,_movingSpeedDecrease, MovingSpedDecrease);//���룬�����ӵ��������ڹ���״̬�µķ���״̬)


	CC_SYNTHESIZE(const char*, _bulletImageName, BulletImageName);//����һ�ι�������ӵ���

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