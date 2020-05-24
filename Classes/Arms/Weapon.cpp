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

	//��������ͼ�꣬��������Ļ�м䣬��Ϊ�ɼ�
	//TODO:�Թ��������󶨣���Ҫ�������ʵ��
	Sprite* spWeapon = Sprite::create(weaponImageName1);
	Sprite* spWeaponReverse = Sprite::create(weaponImageName2);

	Size visibleSize = Director::getInstance()->getVisibleSize();


	if (heroOwned) {
		spWeapon->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:�������������
		spWeapon->setVisible(false);
		spWeaponReverse->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:�������������
		spWeaponReverse->setVisible(false);
	}
	else {
		//TODO:����������λ�õİ�
	}

	_isAttacking = false;

	//TODO:���
	/*initBasicInfo(side);*/

	this->addChild(spWeapon, 0, TAG_WEAPON1);
	this->addChild(spWeaponReverse, 1, TAG_WEAPON2);

	//�������ü��̼�����
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
	//ȥ����ʱ�Ե�����buff
	float nowTime = GetCurrentTime() / 1000.f;
	for (auto i = _vecWeaponBuff.begin(); i != _vecWeaponBuff.end();) {
		if ((*i)->isATempWeaponBuff()) {
			if ((*i)->getWeaponBuffEndTime() <= nowTime) {
				cancelBuff(*i);
				i = _vecWeaponBuff.erase(i);
			}
		}
		else {
			//TODO:�վ��������ʱȫ��ȥ��buff���߼�δ���
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
	//���������ȡ
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	spWeapon->stopAllActions();
	spWeaponReverse->stopAllActions();
	//�޸Ŀ��ƶ�״̬
	_isCanMove = true;

	if (_ewDirection == EWeaponDirection::weaponStop) {
		_isCanMove = false;
		return false;
	}
	if (_ewDirection == EWeaponDirection::weaponAttackingEnermy) {
		//TODO������,��Ҫ���ӵ����ж�����,λ��ת���Ƕ�װ��

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

	//����ָ����
	//TODO:��Ҫ�����޸ļ�λϵͳ�Ļ�ע���޸Ĵ˴�KEY_W,KEY_S,KEY_A,KEY_D
	//��Եļ�λ״̬����ͬʱ��ͬ
	//�����蹥����ΪJ
	switch (keyCode) {
	case(EventKeyboard::KeyCode::KEY_J): {
		//����J�����빥��״̬����ʱ���ÿ��Ƕ�������
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
	//TODO:��������Entity��Ĺ����߼��Ĳ���
	/*
		if(
	
	*/
}