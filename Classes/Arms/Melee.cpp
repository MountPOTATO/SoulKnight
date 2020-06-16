#include "Arms/Melee.h"
#include "HelloWorldScene.h"
#include "Entity/Entity.h"
#include "LongRangeAttack/Bullet.h"

Melee* Melee::create
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {
	Melee* melee = new Melee;
	if (melee && melee->init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {
		melee->autorelease();
		return melee;
	}
	CC_SAFE_DELETE(melee);
	return NULL;
}


bool Melee::init
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {
	if (!Node::init()) return false;

	Sprite* spMelee = Sprite::create(weaponImageName1);
	Sprite* spMeleeReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (_heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spMelee->setPosition(Point(0,0));//TODO:�������������
		spMelee->setVisible(false);
		spMeleeReverse->setPosition(Point(0, 0));//TODO:�������������
		spMeleeReverse->setVisible(false);
		
	}
	else {
		//TODO:����������λ�õİ�
	}


	this->addChild(spMelee, 0, TAG_WEAPON1);
	this->addChild(spMeleeReverse, 1, TAG_WEAPON2);

	_isAttacking = false;
	_currentScene = currentScene;
	_isCanMove = false;
	_hasAnimation = false;
	_target = nullptr;

	//_attackRange = 600.f;//������Χ��������
	//_attackSpeed = 0.5f;//��������,

	return true;
}


bool Melee::startWeapon(bool _isStopOther) {
	Sprite* spMelee = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spMeleeReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	//TODO:��������ʱ
	spMelee->setVisible(true);
	spMeleeReverse->setVisible(false);

	_isCanceled = false;
	return true;
}

void Melee::updateTarget() {
	if (_isCanceled) return;

	Vector<Monster*>& currentEnermies = _currentScene->_currentEnemy;
	Sprite* spMelee = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spMeleeReverse = (Sprite*)getChildByTag(TAG_WEAPON2);



	//TODO:�漰�м����ϰ���ʱ������ָ�ϣ�������Ԫ�ؼ�������
	//ָ���������Ŀ��
	if (currentEnermies.empty()) {
		_target = nullptr;
		return;
	}
	for (auto i = currentEnermies.begin(); i != currentEnermies.end(); i++) {
		//TODO:��Ӫ���֣�ע�����Ϊһ�໵��Ϊһ��;������
		if (/*��Ӫ�ж�*/(*i)->getPosition().distance(getPosition()) <= _attackRange) {
			_target = (*i);
			_targetInRange.pushBack(*i);
			float d = (*i)->getPosition().distance(getPosition());
			//log("%f", d);

			for (i++; i != currentEnermies.end(); i++) {
				if((*i)->getPosition().distance(getPosition()) <= _attackRange)
					_targetInRange.pushBack(*i);
				if ((*i)->getPosition().distance(getPosition()) <= d)
					_target = (*i);
			}
		}
		break;
	}

	
}

bool Melee::attack() {
	if (!_isAttacking) return false;
	if (_isCanceled) return false;

	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastAttackTime < _attackSpeed) {  return false; }
	//�����ж�
	
	_lastAttackTime = currentTime;
	if (!_targetInRange.size()) {//����Ŀ��
		for (auto& i : _targetInRange) {
			//TODO��ִ���˺��ж��������˺�,��Ҫ����Entity������˺��Ĺ���ʵ��
			Bullet* bullet = Bullet::create("bulletImage/EmptyBullet.png", _bulletFlyingSpeed, this, NULL, true);
			bullet->setScale(1);
			_currentScene->_bullets.pushBack(bullet);
			_currentScene->addChild(bullet);
			bullet->setVisible(false);
		}
	}
	else {//������Ŀ��
		//TODO:ִ�г����ƻ��ж�����Ҫ���ڳ���Ҫ��ʵ��
	}


	runCombatAction();

	return true;
}

bool Melee::runCombatAction() {

	Sprite* spMelee = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spMeleeReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	
	_hasAnimation = true;
	
	spMelee->stopAllActions();
	spMeleeReverse->stopAllActions();

	
	
	RotateBy* rotateBy1 = RotateBy::create(_attackSpeed*0.75, 360);
	/*RotateBy * rotateBy2 = RotateBy::create(_attackSpeed / 3,  360);*/

	EaseSineIn* speedAdjust = EaseSineIn::create(rotateBy1);
	_hasAnimation = false;
	runAction(speedAdjust);
	
	

	_isAttacking = false;
	return true;
}