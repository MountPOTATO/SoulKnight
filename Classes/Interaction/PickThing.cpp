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

//���̼����¼���ʹʰȡ������ʧ

//����ʰȡ���ߺ�״̬�ĸı䣬��Ҫcharater��Ĺ���