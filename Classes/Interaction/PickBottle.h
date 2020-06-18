#ifndef __PICKBOTTLE_H__
#define __PICKBOTTLE_H__

#include "Interaction/InterContent/ManualPickObject.h"

class Character;
class FlowWorld;

class PickBottle :public ManualPickObject {



public:

	static PickBottle* create
	(Point position,Character* hero, HelloWorld* scene, const char* imageName, HRocker* rocker);

	virtual bool init
	(Point position,Character* hero, HelloWorld* scene, const char* imageName, HRocker* rocker);


	void updatePickBottleState();

	void stopPickBottle();

	void addPoint();
};


#endif