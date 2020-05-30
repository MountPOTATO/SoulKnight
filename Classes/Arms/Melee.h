#ifndef __MELEE_H__
#define __MELEE_H__

#include "Arms/Weapon.h"

#define RIGHT true
#define LEFT false


class Melee :public Weapon {
public:

	//���ͼ��һ������WeaponImage1��WeaponImage2��ͬ���Ը������������������ҷ���ͼƬ��ͬ
	static Melee* create
	(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);


	virtual void updateTarget()override;

	virtual bool attack();

	virtual bool runCombatAction();

	virtual bool startWeapon(bool _isStopOther);


private:
	Vector<Entity*> _targetInRange;
	
	//CC_SYNTHESIZE(float,_validAngle, ValidAngle);
	//CC_SYNTHESIZE(float, _validAngleRad, ValidAngleRad);


};


#endif