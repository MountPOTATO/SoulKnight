#include "Arms/MeleeDerived/Fish.h"

Fish* Fish::create(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {


	Fish* fish = new Fish;
	if (fish && fish->
		init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {


		fish->autorelease();
		return fish;
	}
	CC_SAFE_DELETE(fish);
	return NULL;
}

bool Fish::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spFish = Sprite::create(weaponImageName1);
	Sprite* spFishReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (_heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spFish->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spFish->setScale(2);
		spFish->setVisible(false);
		
		spFishReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spFishReverse->setVisible(false);
		spFishReverse->setScale(2);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spFish, 0, TAG_WEAPON1);
	this->addChild(spFishReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\FishBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();
	

	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\FishAttack.plist");
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

	_imageName = MELEE_FISH;
	_typeName = MELEE;

	return true;
}