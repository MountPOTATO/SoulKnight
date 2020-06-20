#include "Gun.h"
#include "HelloWorldScene.h"
#include "LongRangeAttack/Bullet.h"
#include "SimpleAudioEngine.h"

Gun* Gun::create
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool _heroOwned) {
	Gun* gun = new Gun;
	if (gun && gun->init(weaponImageName1, weaponImageName2, currentScene, side, _heroOwned)) {
		gun->autorelease();
		return gun;
	}
	CC_SAFE_DELETE(gun);
	return NULL;
}


bool Gun::init
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned) {
	if (!Node::init()) return false;

	Sprite* spWeapon = Sprite::create(weaponImageName1);
	Sprite* spWeaponReverse = Sprite::create(weaponImageName2);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (heroOwned) {
		setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		spWeapon->setPosition(Point(0,0));//TODO:仅仅是主角情况
		spWeapon->setVisible(false);
		spWeaponReverse->setPosition(Point(0,0));//TODO:仅仅是主角情况
		spWeaponReverse->setVisible(false);
	}
	else {
		//TODO:怪物与主角位置的绑定
	}


	this->addChild(spWeapon, 0, TAG_WEAPON1);
	this->addChild(spWeaponReverse, 1, TAG_WEAPON2);

	_side = side;
	_heroOwned = heroOwned;
	_target = nullptr;
	_isAttacking = false;
	_currentScene = currentScene;
	_isCanMove = false;
	//_attackSpeed = 0.35f;//测试数据,
	//_attackRange = 10000;//测试数据,
	return true;
}

bool Gun::startWeapon(bool _isStopOther) {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	spWeapon->setVisible(true);
	spWeaponReverse->setVisible(false);

	_isCanceled = false;
	return true;
}

void Gun::updateTarget() {

	if (_isCanceled) return;

	Vector<Monster*>& currentEnermies = _currentScene->_currentEnemy;

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
			float d = (*i)->getPosition().distance(getPosition());
			for (auto rest = i + 1; rest != currentEnermies.end(); rest++) {
				if ((*rest)->getPosition().distance(getPosition()) <= d)
					_target = (*rest);
			}
		}
		break;
	}
}

bool Gun::attack() {

	if (!_isAttacking) return false;

	if (_isCanceled) return false;

	auto currentTime = GetCurrentTime() / 1000.f;
	
	if (currentTime - _lastAttackTime < _attackSpeed) { return false; }


	_lastAttackTime = currentTime;

	//默认子弹Buff
	WeaponBuff* bulletBuff = WeaponBuff::create(WbuffCombine, 0, 0.0, 0.0, 0.0, 0, 0.0, 0.0);

	//TODO:叠加Weapon的buff容器里所有weaponBuff
	//子弹生成方式因枪支不同而异
	
	for (int i = 0; i <=this->getBulletPerTime() - 1; i++) {
		Bullet* bullet = Bullet::create(_bulletImageName, _bulletFlyingSpeed, this, bulletBuff, true);
		bullet->setScale(1.8f);
		bullet->setTiledMap(this->m_map);
		_currentScene->_bullets.pushBack(bullet);
		_currentScene->addChild(bullet);
	}
	
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/Bullet.mp3", false);
	//TODO:Scene类添加子弹容器


	runShootingAction();


	_isAttacking = false;
	_hasAnimation = false;
	return true;


}

bool Gun::runShootingAction() {
	//TODO:animation sitback
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON1);
	_hasAnimation = true;
	if (getVisiblePictureSide() == "right") {
		RotateBy* rotateby1 = RotateBy::create(0.03f, -15);
		ActionInterval* action = Sequence::create(rotateby1, rotateby1->reverse(), NULL);

		runAction(action);

	}
	else if (getVisiblePictureSide() == "left") {
		RotateBy* rotateby1 = RotateBy::create(0.03f, 15);
		ActionInterval* action = Sequence::create(rotateby1, rotateby1->reverse(), NULL);

		runAction(action);

	}
	_hasAnimation = false;
	_isAttacking = false;
	return true;
}