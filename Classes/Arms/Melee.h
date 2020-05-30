#ifndef __MELEE_H__
#define __MELEE_H__

#include "Arms/Weapon.h"

#define RIGHT true
#define LEFT false


class Melee :public Weapon {
public:

	//如果图标一样，则WeaponImage1和WeaponImage2相同，对斧子这类武器可能左右方向图片不同
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