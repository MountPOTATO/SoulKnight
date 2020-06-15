#include "PickWeapon.h"
#include "Entity/Entity.h"
#include "Controller/HRocker.h"
#include "HelloWorldScene.h"

#define TAG_PICKWEAPON 1 

PickWeapon* PickWeapon::create
(Point position, Character* hero, HelloWorld* scene, const char* typeName, const char* imageName,HRocker* rocker) {
	PickWeapon* pickWeapon = new(std::nothrow)PickWeapon;
	if (pickWeapon && pickWeapon->init(position,hero,scene,typeName,imageName,rocker)) {
		pickWeapon->autorelease();
		return pickWeapon;
	}
	CC_SAFE_DELETE(pickWeapon);
	return NULL;
}

bool PickWeapon::init
(Point position, Character* hero, HelloWorld* scene, const char* typeName,const char*imageName,HRocker* rocker) {
	if (!Node::init()) return false;

	this->setPosition(position);

	Sprite* pickWeaponImage = Sprite::create
		(StringUtils::format("WeaponImage//%sImage//%s.png",typeName,imageName));
	pickWeaponImage->setTexture(StringUtils::format("WeaponImage//%sImage//%s.png", typeName, imageName));

	pickWeaponImage->setPosition(Vec2(0,0));
	this->addChild(pickWeaponImage, 0, TAG_PICKWEAPON);
	pickWeaponImage->setVisible(true);

	_pickThingScene = scene;

	_typeName = typeName;
	_imageName = imageName;

	_hero = hero;
	_rocker = rocker;

	_isPressed = false;
	_isNearHero =false;

	return true;

}

void PickWeapon::updatePickWeaponState() {
	if (!_isNearHero) {
		if (this->getPosition().distance(_hero->getPosition()) <= 17.0f
			&& _rocker->getRockerPressButton() != ERockerButtonPress::buttonAttack) {
			_isNearHero = true;
			//Æ®×ÖÌØÐ§¼ÓÈë£¬½øÈëÆ®×Ö×´Ì¬

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

void PickWeapon::stopPickWeapon(bool _isStopOther) {
	Sprite* spPickWeapon = (Sprite*)getChildByTag(TAG_PICKWEAPON);

	spPickWeapon->setVisible(false);

	_isPressed = false;
	_isNearHero = false;
}