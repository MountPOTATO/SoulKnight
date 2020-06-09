#include"PickThing.h"

cocos2d::Scene* PickThing::createScene()
{
	auto scene = Scene::create();

	auto layer = PickThing::create();
	scene->addChild(layer);
	return scene;
}

bool PickThing::init()
{
	auto sprite = Sprite::create("redBottle.png");
	sprite->setPosition(200, 200);
	this->addChild(sprite);
	return true;
}

PickThing::PickThing()
{
	isVisible = true;
}

PickThing::~PickThing()
{

}

bool PickThing::setVisible()
{
	isVisible = false;
	return true;
}

//键盘监听事件，使拾取道具消失

//主角拾取道具后状态的改变，需要charater类的功能