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
	auto sprite = Sprite::create();//���������ͼƬ����
	sprite->setPosition(100, 150);
	this->addChild(sprite);
	return true;
}