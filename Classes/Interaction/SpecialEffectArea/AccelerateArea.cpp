#include "AccelerateArea.h"
#include "HelloWorldScene.h"



AccelerateArea* AccelerateArea::create(Point position, Character* hero, HelloWorld* scene)
{
	AccelerateArea* accelerate = new(std::nothrow)AccelerateArea;
	if (accelerate && accelerate->init(position, hero, scene))
	{
		accelerate->autorelease();
		return accelerate;
	}
	else
	{
		CC_SAFE_DELETE(accelerate);
		return NULL;
	}
}

bool AccelerateArea::init(Point position, Character* hero, HelloWorld* scene)
{
	this->setPosition(position);
	auto acceArea = Sprite::create("SpecialEffectArea/accelerateArea.png");
	acceArea->setTag(1);
	acceArea->setPosition(0,0);
	acceArea->setVisible(true);

	this->addChild(acceArea);
	log("%d", isCollied);
	isCollied = false;
	log("is init");
	log("%d", isCollied);
	theHero = hero;

	return true;
}

void AccelerateArea::updateAccelerateArea()    //更新是否和主角产生碰撞，即是否到达交互距离
{
	auto area = (Sprite*)this->getChildByTag(1);
	/*log("is update");*/
	/*log("%d", isCollied);*/
	if (this->getPosition().distance(theHero->getPosition()) <=ACCELERATE_TOUCHRANGE)
	{
		isCollied = true;
		/*log("is collied");*/
	}
	else isCollied = false;
}

void AccelerateArea::accelerateHeroSpeed(HelloWorld* scene) 
{                                       
	/*log("is speed");*/
	if (isCollied)
	{
		theHero->setSpeed(ACCELERATE_KNIGHT_SPEED);
		auto controller = (ControllerOfEightDir*)scene->getChildByTag(CONTROLLER_TAG);
		controller->setiSpeed(theHero->getSpeed());
		log("has speedup");
	}
}

void AccelerateArea::resetHeroSpeed(HelloWorld* scene)
{
	theHero->setSpeed(KNIGHT_SPEED);
	auto controller = (ControllerOfEightDir*)scene->getChildByTag(CONTROLLER_TAG);
	controller->setiSpeed(theHero->getSpeed());

}

void AccelerateArea::vanishIt()
{
	auto spArea = (Sprite*)this->getChildByTag(1);
	spArea->setVisible(false);

}