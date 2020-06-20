#include "Interaction/PickBottle.h"
#include "HelloWorldScene.h"
#include "Entity/Entity.h"
#include "Controller/HRocker.h"
#include "Entity/Character.h"
#include "FlowWord/FlowWord.h"

#define TAG_PICKBOTTLE 2

PickBottle * PickBottle::create
(Point position, Character * hero, HelloWorld * scene, const char* imageName, HRocker * rocker) {
	PickBottle* pickbottle = new(std::nothrow)PickBottle;
	if (pickbottle && pickbottle->init(position, hero, scene, imageName, rocker)) {
		pickbottle->autorelease();
		return pickbottle;
	}
	CC_SAFE_DELETE(pickbottle);
	return NULL;
}

bool PickBottle::init(Point position, Character* hero, HelloWorld* scene, const char* imageName, HRocker* rocker) {
	if (!Node::init()) return false;

	this->setPosition(position);

	Sprite* pickBottleImage = Sprite::create
	(StringUtils::format("BottleImage//%sBottle.png", imageName));
	pickBottleImage->setTexture(StringUtils::format("BottleImage//%sBottle.png", imageName));

	pickBottleImage->setPosition(Vec2(0, 0));
	this->addChild(pickBottleImage, 0, TAG_PICKBOTTLE);
	pickBottleImage->setVisible(true);

	_pickThingScene = scene;


	_imageName = imageName;

	_hero = hero;
	_rocker = rocker;

	_isPressed = false;
	_isNearHero = false;

	return true;
}



void PickBottle::updatePickBottleState() {
	if (!_isNearHero) {
		if (this->getPosition().distance(_hero->getPosition()) <= 17.0f
			&& _rocker->getRockerPressButton() != ERockerButtonPress::buttonAttack) {
			_isNearHero = true;
			//Æ®×ÖÌØÐ§¼ÓÈë£¬½øÈëÆ®×Ö×´Ì¬

			auto flowWord = FlowWord::create();
			this->_pickThingScene->addChild(flowWord);
			flowWord->showWord(_imageName, Vec2(getPositionX(), getPositionY() + 10));

		}
		return;
	}
	else {
		if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isPressed = true;
			//Ìí¼ÓÎäÆ÷,´´½¨ÎäÆ÷,Å×³ýÎäÆ÷

			//Í£Ö¹Æ®×Ö

		}
		return;
	}
}


void PickBottle::stopPickBottle() {
	Sprite* spPickBottle = (Sprite*)getChildByTag(TAG_PICKBOTTLE);

	spPickBottle->setVisible(false);

	_isPressed = false;
	_isNearHero = false;
}

void PickBottle::addPoint() {
	if (_imageName == RED) {
		_hero->setHP((_hero->getHP() + 2>=10)?10:_hero->getHP()+2);
		auto flowword = FlowWord::create();
		_pickThingScene->addChild(flowword);

		flowword->showWord("+2", Vec2(getPositionX(),getPositionY() + 10));
	}
	if (_imageName == BLUE) {
		_hero->setArmor((_hero->getArmor() + 2 >= 5) ? 5 : _hero->getHP() + 2);

		auto flowword = FlowWord::create();
		_pickThingScene->addChild(flowword);

		flowword->showWord("+2", Vec2(getPositionX(), getPositionY() + 10));
	}
}