#ifndef __GUN_H__
#define __GUN_H__

#include "Arms/Weapon.h"

class Gun :public Weapon {
public:
	
	//��������
	CC_SYNTHESIZE(int, _bulletPerTime, BulletPerTime);//һ�ι�������ӵ���
	

	virtual bool init();
};

#endif