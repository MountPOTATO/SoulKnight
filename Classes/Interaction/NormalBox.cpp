#include"NormalBox.h"

cocos2d::Scene* NormalBox::createScene()
{
	auto scene = Scene::create();

	auto layer = NormalBox::create();

	scene->addChild(layer);
	return scene;
}

bool NormalBox::init()
{
	auto sprite = Sprite::create("NormalBox.png");
	sprite->setPosition(300, 300);
	this->addChild(sprite);
	return true;
}

NormalBox::NormalBox()
{
	isVisible = true;
}

NormalBox::~NormalBox()
{
}

bool NormalBox::isColliedWithBullet() //��ս������Զ��������Ҫ�ֱ��ж�
{
	return true;
}

bool NormalBox::setVisible()
{
	isVisible = false;
	return true;
}