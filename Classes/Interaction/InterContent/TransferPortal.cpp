#include "Interaction/InterContent/TransferPortal.h"
#include "HelloWorldScene.h"


TransferPortal* TransferPortal::create
(Point position, Character* hero, HelloWorld* scene, HRocker* rocker) {
	TransferPortal* portal = new(std::nothrow)TransferPortal;
	if (portal && portal->init(position, hero, scene, rocker)) {
		portal->autorelease();
		return portal;
	}
	CC_SAFE_DELETE(portal);
	return NULL;
}

bool TransferPortal::init(Point position, Character* hero, HelloWorld* scene, HRocker* rocker)
{
	setPosition(position);
	auto transPor = Sprite::create("transferPortal1.png");
	Size sizeV = Director::getInstance()->getVisibleSize();
	transPor->setPosition(0,0);
	transPor->setVisible(true);
	this->addChild(transPor);
	

	_hero = hero;
	_pickThingScene = scene;
	_rocker = rocker;
	initProtalState();
	_isUsed = false;
	/*transPor->setPositionZ(_hero->getPositionZ() - 100);*/

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

void TransferPortal::updatePortalState() {
	if (!isUnUsed()) return;
	if (!_isNearHero) {
		if (this->getBoundingBox().intersectsRect(_hero->getBoundingBox())
			&& _rocker->getRockerPressButton() != ERockerButtonPress::buttonAttack) {
			_isNearHero = true;
			//飘字特效加入，进入飘字状态

		}
		return;
	}
	else {
		if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isPressed = true;
			//添加武器,创建武器,抛除武器

			//停止飘字

		}
		return;
	}
}
