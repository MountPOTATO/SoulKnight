
#ifndef __TRANSFERPORTAL_H__
#define __TRANSFERPORTAL_H__
#include "cocos2d.h"


#include "Interaction/InterContent/ManualPickObject.h"

USING_NS_CC;

class TransferPortal :public ManualPickObject {
	CC_SYNTHESIZE(bool, _isUsed, IsUsed);
public:

	static TransferPortal* create
	(Point position, Character* hero, HelloWorld* scene, HRocker* rocker);

	virtual bool init
	(Point position, Character* hero, HelloWorld* scene, HRocker* rocker);

	void updatePortalState();

	void stopPortal(bool _isStopOther);

	void initProtalState() { _isNearHero = false; _isPressed = false; }

	void setPortalAsUsed() { _isUsed = true; }
	bool isUnUsed()const { return _isUsed == false; }

};

#endif