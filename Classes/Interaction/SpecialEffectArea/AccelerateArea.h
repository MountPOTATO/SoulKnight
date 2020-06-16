#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Character;
class HelloWorld;

class AccelerateArea:public Node
{
	CC_SYNTHESIZE(bool, isCollied, IsCollied);
	CC_SYNTHESIZE(Character*, theHero, TheHero);
public:
	static AccelerateArea* create(Point position, Character* hero, HelloWorld* scene);
	virtual bool init(Point position, Character* hero, HelloWorld* scene);

	bool isColliedJudge() { return isCollied == true; }
	void accelerateHeroSpeed(HelloWorld* scene);
	void resetHeroSpeed(HelloWorld* scene);
	void updateAccelerateArea();

	void vanishIt();
};