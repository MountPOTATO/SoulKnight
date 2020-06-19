#ifndef __MANUALPICKOBJECT_H__
#define __MANUALPICKOBJECT_H__


#include "cocos2d.h"


class HelloWorld;
class Entity;

class HRocker;
class Character;

USING_NS_CC;

class ManualPickObject :public Node {
private:
	CC_SYNTHESIZE(HelloWorld*, _pickThingScene, PickThingScene);//³¡¾°

	CC_SYNTHESIZE(Character*, _hero, Hero);//Ó¢ÐÛ

	CC_SYNTHESIZE(bool,_isNearHero, IsNearHero);

	CC_SYNTHESIZE(bool, _isPressed, IsPressed);

	CC_SYNTHESIZE(const char*, _imageName, ImageName);

	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);

public:
	static ManualPickObject* create();

	virtual bool init();

	bool objectIsNearHero() { return _isNearHero; }
	bool objectIsPressed() { return _isPressed; }

};

#endif