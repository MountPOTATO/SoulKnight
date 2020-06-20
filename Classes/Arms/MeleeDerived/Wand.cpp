#include "Arms/MeleeDerived/Wand.h"


Wand* Wand::create(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {


	Wand* wand = new Wand;
	if (wand && wand->
		init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {


		wand->autorelease();
		return wand;
	}
	CC_SAFE_DELETE(wand);
	return NULL;
}

bool Wand::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spWand = Sprite::create(weaponImageName1);
	Sprite* spWandReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	setScale(2.3);
	if (_heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));

		spWand->setPosition(Point(0, 0));//TODO:仅仅是主角情况

		spWand->setVisible(false);


		spWandReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spWandReverse->setVisible(false);

	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spWand, 0, TAG_WEAPON1);
	this->addChild(spWandReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\WandBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();


	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\WandAttack.plist");
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

	_imageName = MELEE_WAND;
	_typeName = MELEE;


	this->setLastAttackTime(GetCurrentTime() / 1000.0f);

	return true;
}
