#include "Weapon.h"

#define PRESS 1
#define RELEASE 2

#define TAG_WEAPON1 1
#define TAG_WEAPON2 2

Weapon * Weapon::create
(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool heroOwned)
{
	Weapon* weaponSprite = new Weapon;
	if (weaponSprite && weaponSprite->init(weaponImageName1, weaponImageName2, side, heroOwned)) {
		weaponSprite->autorelease();
		return weaponSprite;
	}
	CC_SAFE_DELETE(weaponSprite);
	return NULL;
}

bool Weapon::init
(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool heroOwned)
{
	if (!Sprite::initWithFile(weaponImageName1)) return false;

	//创建武器图标，设置在屏幕中间，设为可见
	//TODO:对怪物的坐标绑定，需要怪物类的实现
	Sprite* spWeapon = Sprite::create(weaponImageName1);
	Sprite* spWeaponReverse = Sprite::create(weaponImageName2);

	Size visibleSize = Director::getInstance()->getVisibleSize();


	if (heroOwned) {
		spWeapon->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:仅仅是主角情况
		spWeapon->setVisible(false);
		spWeaponReverse->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:仅仅是主角情况
		spWeaponReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}

	_isAttacking = false;

	//TODO:添加
	/*initBasicInfo(side);*/

	this->addChild(spWeapon, 0, TAG_WEAPON1);
	this->addChild(spWeaponReverse, 1, TAG_WEAPON2);

	//创建设置键盘监听器
	listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(Weapon::onPressKey, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(Weapon::onReleaseKey, this);

	return true;
}

void Weapon::startWeapon(bool _isStopOther) {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	spWeapon->setVisible(true);
	spWeaponReverse->setVisible(false);

	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithFixedPriority(listenerKeyboard, 2);
}


void Weapon::showWeaponPicture(int type) {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	if (type == 1) {
		spWeapon->setVisible(true);
		spWeaponReverse->setVisible(false);
	}
	else if (type == 2) {
		spWeapon->setVisible(false);
		spWeaponReverse->setVisible(true);
	}
}

const char* Weapon::getVisiblePictureSide()const {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	if (spWeaponReverse->isVisible() && (!spWeapon->isVisible()))
		return "left";
	if (spWeapon->isVisible() && (!spWeaponReverse->isVisible()))
		return "right";
	else
		return "noSide";
}

Sprite* Weapon::getVisiblePicture()const {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	if (spWeaponReverse->isVisible() && (!spWeapon->isVisible()))
		return spWeaponReverse;
	if (spWeapon->isVisible() && (!spWeaponReverse->isVisible()))
		return spWeapon;
	else
		return nullptr;
}

void Weapon::takeBuff(WeaponBuff* weaponBuff) {
	_vecWeaponBuff.pushBack(weaponBuff);
	_attack += weaponBuff->getWeaponBuffAttack();
	_attackSpeed -= weaponBuff->getWeaponBuffAttackSpeed();
	_attackRange += weaponBuff->getWeaponBuffAttackRange();
	_hardStrikeRate += weaponBuff->getWeaponBuffHardStrikeRate();
	_precision += weaponBuff->getWeaponBuffPrecision();
	_energyCost -= weaponBuff->getWeaponBuffEnergyCost();
}

void Weapon::cancelBuff(WeaponBuff* weaponBuff) {
	_attack -= weaponBuff->getWeaponBuffAttack();
	_attackSpeed += weaponBuff->getWeaponBuffAttackSpeed();
	_attackRange -= weaponBuff->getWeaponBuffAttackRange();
	_hardStrikeRate -= weaponBuff->getWeaponBuffHardStrikeRate();
	_precision -= weaponBuff->getWeaponBuffPrecision();
	_energyCost += weaponBuff->getWeaponBuffEnergyCost();
}

void Weapon::deleteTempBuff() {
	//去除暂时性的武器buff
	float nowTime = GetCurrentTime() / 1000.f;
	for (auto i = _vecWeaponBuff.begin(); i != _vecWeaponBuff.end();) {
		if ((*i)->isATempWeaponBuff()) {
			if ((*i)->getWeaponBuffEndTime() <= nowTime) {
				cancelBuff(*i);
				i = _vecWeaponBuff.erase(i);
			}
		}
		else {
			//TODO:终局条件添加时全部去除buff的逻辑未添加
			++i;
		}
	}
}

void Weapon::clearBuff() {
	for (auto i = _vecWeaponBuff.begin(); i != _vecWeaponBuff.end();)
		i = _vecWeaponBuff.erase(i);
}


bool Weapon::onPressKey(EventKeyboard::KeyCode keyCode, Event* event) {
	if (!_heroOwned) return false;

	updateState(keyCode, PRESS);
	//武器精灵获取
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	spWeapon->stopAllActions();
	spWeaponReverse->stopAllActions();
	//修改可移动状态
	_isCanMove = true;

	if (_ewDirection == EWeaponDirection::weaponStop) {
		_isCanMove = false;
		return false;
	}
	if (_ewDirection == EWeaponDirection::weaponAttackingEnermy) {
		//TODO待补充,需要增加敌人判定机制,位置转换角度装置

		return true;
	}
	spWeapon->stopAllActions();
	spWeaponReverse->stopAllActions();
	switch (_ewDirection) {

	case(EWeaponDirection::weaponRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 0);
		spWeapon->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponUpRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 315);
		spWeapon->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponUp): {
		if (getVisiblePictureSide() == "left") {

			RotateTo* rotateTo = RotateTo::create(0, 90);
			spWeaponReverse->runAction(rotateTo);
		}
		else if (getVisiblePictureSide() == "right") {

			RotateTo* rotateTo = RotateTo::create(0, 270);
			spWeapon->runAction(rotateTo);
		}
		break;
	}
	case(EWeaponDirection::weaponUpLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 45);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 0);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponDownLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 315);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponDown): {
		if (getVisiblePictureSide() == "left") {
			RotateTo* rotateTo = RotateTo::create(0, 270);
			spWeaponReverse->runAction(rotateTo);
		}
		else if (getVisiblePictureSide() == "right") {
			RotateTo* rotateTo = RotateTo::create(0, 90);
			spWeapon->runAction(rotateTo);
		}
		break;
	}
	case(EWeaponDirection::weaponDownRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 45);
		spWeapon->runAction(rotateTo);
		break;
	}
	default:break;
	};

	return true;
}


bool Weapon::onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event) {
	if (!_heroOwned) return false;

	updateState(keyCode, RELEASE);//RELEASE
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	spWeapon->stopAllActions();
	spWeaponReverse->stopAllActions();

	switch (_ewDirection) {
	case(EWeaponDirection::weaponRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 0);
		spWeapon->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponUpRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 315);
		spWeapon->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponUp): {
		if (getVisiblePictureSide() == "left") {

			RotateTo* rotateTo = RotateTo::create(0, 90);
			spWeaponReverse->runAction(rotateTo);
		}
		else if (getVisiblePictureSide() == "right") {

			RotateTo* rotateTo = RotateTo::create(0, 270);
			spWeapon->runAction(rotateTo);
		}
		break;
	}
	case(EWeaponDirection::weaponUpLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 45);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 0);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponDownLeft): {
		showWeaponPicture(2);
		RotateTo* rotateTo = RotateTo::create(0, 315);
		spWeaponReverse->runAction(rotateTo);
		break;
	}
	case(EWeaponDirection::weaponDown): {
		if (getVisiblePictureSide() == "left") {
			RotateTo* rotateTo = RotateTo::create(0, 270);
			spWeaponReverse->runAction(rotateTo);
		}
		else if (getVisiblePictureSide() == "right") {
			RotateTo* rotateTo = RotateTo::create(0, 90);
			spWeapon->runAction(rotateTo);
		}
		break;
	}
	case(EWeaponDirection::weaponDownRight): {
		showWeaponPicture(1);
		RotateTo* rotateTo = RotateTo::create(0, 45);
		spWeapon->runAction(rotateTo);
		break;
	}
	default:break;
	};


	_isCanMove = false;
	return true;
}


bool Weapon::updateState(EventKeyboard::KeyCode keyCode, int type) {
	if (!_heroOwned) return false;

	//按键指定：
	//TODO:若要开发修改键位系统的话注意修改此处KEY_W,KEY_S,KEY_A,KEY_D
	//相对的键位状态不能同时相同
	//这里设攻击键为J
	switch (keyCode) {
	case(EventKeyboard::KeyCode::KEY_J): {
		//按下J，进入攻击状态，此时不用考虑动作属性
		if (type == PRESS) _ewDirection = EWeaponDirection::weaponAttackingEnermy;
		break;
	}
	case(EventKeyboard::KeyCode::KEY_W): {
		if (type == PRESS) { m_upState = true; m_downState = false; }
		else if (type == RELEASE) { m_upState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_S): {
		if (type == PRESS) { m_upState = false; m_downState = true; }
		else if (type == RELEASE) { m_downState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_A): {
		if (type == PRESS) { m_leftState = true; m_rightState = false; }
		else if (type == RELEASE) { m_leftState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_D): {
		if (type == PRESS) { m_leftState = false; m_rightState = true; }
		else if (type == RELEASE) { m_rightState = false; }
		break;
	}
	default:break;
	};

	updateDirection();



	return true;
}

bool Weapon::updateDirection() {
	if (!_heroOwned) return false;

	if (m_upState) {

		if (m_leftState) {
			_ewDirection = EWeaponDirection::weaponUpLeft;
		}
		else if (m_rightState) {
			_ewDirection = EWeaponDirection::weaponUpRight;
		}
		else {
			_ewDirection = EWeaponDirection::weaponUp;
		}
	}
	else if (m_downState) {
		if (m_leftState) {
			_ewDirection = EWeaponDirection::weaponDownLeft;
		}
		else if (m_rightState) {
			_ewDirection = EWeaponDirection::weaponDownRight;
		}
		else {
			_ewDirection = EWeaponDirection::weaponDown;
		}
	}
	else {
		if (m_leftState) {
			_ewDirection = EWeaponDirection::weaponLeft;
		}
		else if (m_rightState) {
			_ewDirection = EWeaponDirection::weaponRight;
		}
		else {
			_ewDirection = EWeaponDirection::weaponStop;
		}
	}
}


bool Weapon::attack() {
	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastAttackTime < _attackSpeed) {
		return false;
	}
	//TODO:当引入了Entity后的攻击逻辑的补充
	/*
		if(
	
	*/
}