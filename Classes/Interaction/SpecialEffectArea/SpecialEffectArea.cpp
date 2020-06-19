#include "SpecialEffectArea.h"

cocos2d::Scene* SpecialEffectArea()
{
	auto scene = Scene::create();

	auto layer = SpecialEffectArea::create();
	scene->addChild(layer);
	return scene;
}

bool SpecialEffectArea::init()
{
	auto sprite = Sprite::create();//机关区域的图片暂无
	sprite->setPosition(100, 150);
	this->addChild(sprite);
	return true;
}