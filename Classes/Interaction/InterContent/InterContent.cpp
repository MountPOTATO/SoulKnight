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

//���̼����¼��������Ƿ�Խ����������Ӧ

//��̬Ч���������źͱ����ڽ�������������