#include "Arms/GunDerived/SMG.h"


SMG* SMG::create(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {


	SMG* smg = new SMG;
	if (smg && smg->
		init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {


		smg->autorelease();
		return smg;
	}
	CC_SAFE_DELETE(smg);
	return NULL;
}

bool SMG::init(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {

	Sprite* spSMG = Sprite::create(weaponImageName1);
	Sprite* spSMGReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spSMG->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spSMG->setVisible(false);
		spSMGReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spSMGReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spSMG, 0, TAG_WEAPON1);
	this->addChild(spSMGReverse, 1, TAG_WEAPON2);

	ValueVector vecBasic = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\SMGBasic.plist");
	ValueMap basicInfo = vecBasic.at(0).asValueMap();
	_attack = basicInfo.at("Attack").asInt();
	_precision = basicInfo.at("Precision").asInt();
	_energyCost = basicInfo.at("EnergyCost").asInt();
	_weaponPrice = basicInfo.at("WeaponPrice").asInt();
	_bulletPerTime = basicInfo.at("BulletPerTime").asInt();

	ValueVector vecAttack = FileUtils::getInstance()->getValueVectorFromFile("WeaponInfo\\SMGAttack.plist");
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
	_bulletImageName = "BulletImage\\SMGBullet.png";

	_imageName = GUN_SMG;
	_typeName = GUN;


	this->setLastAttackTime(GetCurrentTime() / 1000.0f);
	return true;
}
