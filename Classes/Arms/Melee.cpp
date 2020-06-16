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
		spMelee->setPosition(Point(0,0));//TODO:仅仅是主角情况
		spMelee->setVisible(false);
		spMeleeReverse->setPosition(Point(0, 0));//TODO:仅仅是主角情况
		spMeleeReverse->setVisible(false);
		
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spMelee, 0, TAG_WEAPON1);
	this->addChild(spMeleeReverse, 1, TAG_WEAPON2);

	_isAttacking = false;
	_currentScene = currentScene;
	_isCanMove = false;
	_hasAnimation = false;
	_target = nullptr;

	//_attackRange = 600.f;//攻击范围测试数据
	//_attackSpeed = 0.5f;//测试数据,

	return true;
}


bool Melee::startWeapon(bool _isStopOther) {
	Sprite* spMelee = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spMeleeReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	//TODO:捡起武器时
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



	//TODO:涉及中间有障碍物时的重新指认，待场景元素加入后决定
	//指认最近距离目标
	if (currentEnermies.empty()) {
		_target = nullptr;
		return;
	}
	for (auto i = currentEnermies.begin(); i != currentEnermies.end(); i++) {
		//TODO:阵营划分，注意好人为一类坏人为一类;或不引入
		if (/*阵营判断*/(*i)->getPosition().distance(getPosition()) <= _attackRange) {
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
	//攻击判定
	
	_lastAttackTime = currentTime;
	if (!_targetInRange.size()) {//存在目标
		for (auto& i : _targetInRange) {
			//TODO：执行伤害判定，给出伤害,需要后期Entity类承受伤害的功能实现
			Bullet* bullet = Bullet::create("bulletImage/EmptyBullet.png", _bulletFlyingSpeed, this, NULL, true);
			bullet->setScale(1);
			_currentScene->_bullets.pushBack(bullet);
			_currentScene->addChild(bullet);
			bullet->setVisible(false);
		}
	}
	else {//不存在目标
		//TODO:执行场景破坏判定，需要后期场景要素实现
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