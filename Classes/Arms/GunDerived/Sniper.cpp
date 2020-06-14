#include "Arms/GunDerived/Sniper.h"


Sniper* Sniper::create(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {


	Sniper* hecateII = new Sniper;
	if (hecateII && hecateII->
		init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {


		hecateII->autorelease();
		return hecateII;
	}
	CC_SAFE_DELETE(hecateII);
	return NULL;
}

bool Sniper::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spHecate = Sprite::create(weaponImageName1);
	Sprite* spHecateReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spHecate->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spHecate->setVisible(false);
		spHecateReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spHecateReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spHecate, 0, TAG_WEAPON1);
	this->addChild(spHecateReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\SniperBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();
	_bulletPerTime = basicInfo.at("BulletPerTime").asInt();

	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\SniperAttack.plist");
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
	_bulletImageName = "BulletImage\\SniperBullet.png";

	_imageName = GUN_SNIPER;
	_typeName = GUN;

	return true;
}