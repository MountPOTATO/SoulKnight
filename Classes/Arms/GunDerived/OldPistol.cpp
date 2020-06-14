#include "Arms/GunDerived/OldPistol.h"

OldPistol* OldPistol::create(const char* weaponImageName1, const char* weaponImageName2,
	 HelloWorld* currentScene, ESide side, bool _heroOwned) {


	OldPistol* oldPistol = new OldPistol;
	if (oldPistol && oldPistol->
		init(weaponImageName1, weaponImageName2,  currentScene, side, _heroOwned)) {


		oldPistol->autorelease();
		return oldPistol;
	}
	CC_SAFE_DELETE(oldPistol);
	return NULL;
}

bool OldPistol::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spOldPistol = Sprite::create(weaponImageName1);
	Sprite* spOldPistolReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spOldPistol->setPosition(Point(0,0));//TODO:仅仅是主角情况
		spOldPistol->setVisible(false);
		spOldPistolReverse->setPosition(Point(0,0));//TODO:仅仅是主角情况
		spOldPistolReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spOldPistol, 0, TAG_WEAPON1);
	this->addChild(spOldPistolReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\OldPistolBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();
	_bulletPerTime = basicInfo.at("BulletPerTime").asInt();

	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\OldPistolAttack.plist");
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
	_bulletImageName = "BulletImage\\OldPistolBullet.png";

	_imageName = GUN_OLDPISTOL;
	_typeName = GUN;

	return true;
}