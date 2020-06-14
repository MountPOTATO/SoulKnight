#ifndef __PICKWEAPON_H__
#define __PICKWEAPON_H__


#include "Interaction/InterContent/ManualPickObject.h"



class PickWeapon :public ManualPickObject {

	CC_SYNTHESIZE(const char*, _typeName, TypeName);

public:

	static PickWeapon* create
		(Point position, Entity* hero, HelloWorld* scene,const char* typeName, const char* imageName, HRocker* rocker);

	virtual bool init
		(Point position, Entity* hero, HelloWorld* scene,const char* typeName, const char* imageName, HRocker* rocker);

	void updatePickWeaponState();


	const char* getPickWeaponImageName() { return _imageName; }
	const char* getPickWeaponTypeName() { return _typeName; }

	void stopPickWeapon(bool _isStopOther);

	void initPickWepaonState() { _isNearHero = false; _isPressed = false; }
};


#endif