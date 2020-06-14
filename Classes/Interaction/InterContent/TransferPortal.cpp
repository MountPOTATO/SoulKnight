#include "TransferPortal.h"
#include "HelloWorldScene.h"

//Layer* TransferPortal::layer = Layer::create();
//
Scene* TransferPortal::createScene()
{
	auto scene = Scene::create();

	auto layer = TransferPortal::create();

    scene->addChild(layer);
	return scene;
}

bool TransferPortal::init()             //对传送门动态效果的初始化
{
	auto transPor = Sprite::create("transferPortal1.png");
	Size sizeV = Director::getInstance()->getVisibleSize();
	transPor->setPosition(Vec2(sizeV.width / 2, sizeV.height/2));
	this->addChild(transPor);

	Size sizeC = transPor->getContentSize();
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame* > vTrans;
	for (int i = 1; i <= 3; i++)
	{
		char str[20] = { 0 };
		sprintf(str, "transferPortal%d.png", i);
		std::string strs = str;
		frame = SpriteFrame::create(strs, Rect(0, 0, sizeC.width,sizeC.height));
		vTrans.pushBack(frame);
	}

	log("si there any");

	Animation* rotate = Animation::createWithSpriteFrames(vTrans, 0.16f);
	Animate* action = Animate::create(rotate);
	transPor->runAction(RepeatForever::create(action));
	return true;
}

bool TransferPortal::isToPushScene()
{
	//保持传送门对主角的碰撞检测，sprite的碰撞检测，场景的切换
	//检测到主角的碰撞并且按下按钮 则进行场景切换
	//y为攻击 u为技能 i切换武器
	//wasd上下左右
	//即检测y键是否被按下
	//Director::getInstance()->pushScene(创建场景并切换)
	return true;
}


bool TransferPortal::isColliedWithCharacter()
{
	//进行碰撞检测；
	//调用isToPushScene()函数;
	return true;
}