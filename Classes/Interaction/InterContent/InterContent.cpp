#include "InterContent.h"

cocos2d::Scene* InterContent::createScene()
{
	auto scene = Scene::create();

	auto layer = InterContent::create();
	scene->addChild(layer);
	return scene;
}

bool InterContent::init()
{
	auto sprite = Sprite::create("transferPortal.png");
	sprite->setPosition(100, 100);
	this->addChild(sprite);
	return true;
}

//键盘监听事件，主角是否对交互物产生反应

//动态效果，传送门和宝箱在交互后会产生动作