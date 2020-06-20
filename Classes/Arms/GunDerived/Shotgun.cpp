#include "Arms/GunDerived/Shotgun.h"

Shotgun* Shotgun::create(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {


	Shotgun* shotgun = new Shotgun;
	if (shotgun && shotgun->
		init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {


		shotgun->autorelease();
		return shotgun;
	}
	CC_SAFE_DELETE(shotgun);
	return NULL;
}

bool Shotgun::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spShotgun = Sprite::create(weaponImageName1);
	Sprite* spShotgunReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spShotgun->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spShotgun->setVisible(false);
		spShotgunReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spShotgunReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spShotgun, 0, TAG_WEAPON1);
	this->addChild(spShotgunReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\ShotgunBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();
	_bulletPerTime = basicInfo.at("BulletPerTime").asInt();

	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\ShotgunAttack.plist");
	ValueMap attackInfo = vecAttack.at(0).asValueMap();
	_attackSpeed = attackInfo.at("AttackSpeed").asFloat();
	_attackRange = attackInfo.at("AttackRange").asFloat();
	_hardStrikeRate = attackInfo.at("HardStrikeRate").asFloat();
	_bulletFlyingSpeed = attackInfo.at("BulletFlyingSpeed").asFloat();


	_side = side;
	_heroOwned = heroOwned;
	_target = nullptr;
	_isAttacking = false;
	_currentScene = currentScene;
	_isCanMove = false;
	_hasAnimation = false;
	_bulletImageName = "BulletImage\\ShotgunBullet.png";

	_imageName = GUN_SHOTGUN;
	_typeName = GUN;


	return true;
}

bool Shotgun::runShootingAction() {

	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON1);
	_hasAnimation = true;
	if (getVisiblePictureSide() == "right") {
		RotateBy* rotateby1 = RotateBy::create(0.03f, -30);
		ActionInterval* action = Sequence::create(rotateby1, rotateby1->reverse(), NULL);

		runAction(action);

	}
	else if (getVisiblePictureSide() == "left") {
		RotateBy* rotateby1 = RotateBy::create(0.03f, 30);
		ActionInterval* action = Sequence::create(rotateby1, rotateby1->reverse(), NULL);

		runAction(action);

	}
	_hasAnimation = false;
	_isAttacking = false;
	return true;

}