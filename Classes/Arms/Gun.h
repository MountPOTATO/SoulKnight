#ifndef __GUN_H__
#define __GUN_H__

#include "Arms/Weapon.h"

class Gun :public Weapon {
public:
	
	//固有属性
	CC_SYNTHESIZE(int, _bulletPerTime, BulletPerTime);//一次攻击射出子弹数
	

	virtual bool init();
};

#endif