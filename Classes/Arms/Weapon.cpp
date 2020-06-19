#include "Weapon.h"
#include "LongRangeAttack/Bullet.h"
#include "Entity/Character.h"
#include "Entity/Monster.h"
#include "HelloWorldScene.h"

Weapon* Weapon::create
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned)
{
	Weapon* weaponSprite = new Weapon;
	if (weaponSprite && weaponSprite->init(weaponImageName1, weaponImageName2,
		currentScene, side, heroOwned)) {
		weaponSprite->autorelease();
		return weaponSprite;
	}
	CC_SAFE_DELETE(weaponSprite);
	return NULL;
}

bool Weapon::init
(const char* weaponImageName1, const char* weaponImageName2,
	HelloWorld* currentScene, ESide side, bool heroOwned)
{

	if (!Node::init()) return false;

	//创建武器图标，设置在屏幕中间，设为可见
	//TODO:对怪物的坐标绑定，需要怪物类的实现
	Sprite* spWeapon = Sprite::create(weaponImageName1);
	Sprite* spWeaponReverse = Sprite::create(weaponImageName2);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_side = side;
	_heroOwned = heroOwned;
	_target = nullptr;


	if (heroOwned) {

		spWeapon->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:仅仅是主角情况
		spWeapon->setVisible(false);

		spWeaponReverse->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));//TODO:仅仅是主角情况
		spWeaponReverse->setVisible(false);
	}
	else {
		//TODO:怪物与武器位置的绑定
	}

	_isAttacking = false;
	_currentScene = currentScene;
	_isCanMove = false;
	_hasAnimation = false;

	this->addChild(spWeapon, 0, TAG_WEAPON1);
	this->addChild(spWeaponReverse, 1, TAG_WEAPON2);


	return true;
}

//
////图像调整
//bool Weapon::resetWeapon(HelloWorld* newScene) {
//	if (!newScene) return false;
//	_currentScene = newScene;
//	_isCanMove = false;
//	_hasAnimation = false;
//	_isAttacking = false;
//	_target = nullptr;
//
//	_isCanceled = false;
//
//	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
//	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	spWeapon->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
//	spWeapon->setVisible(false);
//
//	spWeaponReverse->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
//	spWeaponReverse->setVisible(false);
//
//	return true;
//}
//
//bool Weapon::resetImageBeforeSwitchScene() {
//	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
//	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
//	spWeapon->stopAllActions();
//	spWeaponReverse->stopAllActions();
//	spWeapon->setRotation(0);
//	spWeaponReverse->setRotation(0);
//	spWeaponReverse->setVisible(false);
//	spWeapon->setVisible(true);
//	return true;
//}

void Weapon::startWeapon(bool _isStopOther) {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	spWeapon->setVisible(true);
	spWeaponReverse->setVisible(false);

	_isCanceled = false;

}

void Weapon::stopWeapon(bool _isStopOther) {
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);

	spWeapon->setVisible(false);
	spWeaponReverse->setVisible(false);

	_isCanceled = true;

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

void Weapon::updateTarget() {
	return;
}



float Weapon::getRad(Point point1, Point point2)const {
	//获得两点x,y距离
	float xd = point2.x - point1.x;
	float yd = point1.y - point2.y;
	//斜边长度计算
	float hypo = sqrt(pow(xd, 2) + pow(yd, 2));
	//获得余弦值
	float cos = xd / hypo;
	//获得rad
	float rad = acos(cos);
	//取反ss
	if (yd > 0) {
		rad = -rad;
	}
	return rad;
}


//武器坐标更新相关
//设置武器坐标
void Weapon::setWeaponTagPosition(int x, int y) {
	setPosition(x, y);
	setViewPointByWeapon();
}
//以武器为中心设置视角
void Weapon::setViewPointByWeapon() {
	if (!this->getVisiblePicture()) return;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* parent = (Layer*)getParent();

	Point weaponPos = this->getPosition();//当前武器坐标
	Point centrePos = Point(visibleSize.width / 2, visibleSize.height / 2);//视图中心坐标
	Point viewPos = centrePos - weaponPos;//视点
	parent->setPosition(viewPos);
}



void Weapon::updateImageRotation(HRocker* rocker) {

	if (_isCanceled) return;
	//武器精灵获取
	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	spWeapon->stopAllActions();
	spWeaponReverse->stopAllActions();
	//修改可移动状态
	_isCanMove = true;


	if (_target != nullptr) {//有目标且没有动画时，自动转到角度
		_targetMathRad = getRad(this->getPosition(), _target->getPosition());
		_mathAngle = _targetMathRad * 180.f / PI;
		if (_targetMathRad >= -PI && _targetMathRad <= -PI / 2) {
			showWeaponPicture(2);
			getVisiblePicture()->setRotation(540.f - _mathAngle);
		}
		else if (_targetMathRad > -PI / 2 && _targetMathRad <= 0) {
			showWeaponPicture(1);
			getVisiblePicture()->setRotation(360.f - _mathAngle);
		}
		else if (_targetMathRad > 0 && _targetMathRad <= PI / 2) {
			showWeaponPicture(1);
			getVisiblePicture()->setRotation(360.f - _mathAngle);
		}
		else if (_targetMathRad > PI / 2 && _targetMathRad <= PI) {
			showWeaponPicture(2);
			getVisiblePicture()->setRotation(180.f - _mathAngle);
		}
		else if (_targetMathRad > PI && _targetMathRad <= 3 * PI / 2) {
			showWeaponPicture(2);
			getVisiblePicture()->setRotation(540.f - _mathAngle);
		}
		else if (_targetMathRad > 3 * PI / 2 && _targetMathRad <= 2 * PI) {
			showWeaponPicture(1);
			getVisiblePicture()->setRotation(360.f - _mathAngle);
		}
		spWeapon->stopAllActions();
		spWeaponReverse->stopAllActions();
		_isAttacking = false;

		if (rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isCanMove = false;
			_isAttacking = true;
			return;
		}

		_target = nullptr;
		return;
	}
	else {

		if (rocker->getRockerDirection() == ERocker8Direction::rockerStop
			&& rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isCanMove = false;
			_isAttacking = true;
			_hasAnimation = true;
			return;
		}


		switch (rocker->getRockerDirection()) {
		case(ERocker8Direction::rockerRight): {
			showWeaponPicture(1);
			/*RotateTo* rotateTo = RotateTo::create(0, 0);
			spWeapon->runAction(rotateTo);*/
			spWeapon -> setRotation(0);
	
			break;
		}
		case(ERocker8Direction::rockerUpRight): {
			showWeaponPicture(1);
			/*RotateTo* rotateTo = RotateTo::create(0, 315);
			spWeapon->runAction(rotateTo);*/
			spWeapon->setRotation(315);
			break;
		}
		case(ERocker8Direction::rockerUp): {
			if (getVisiblePictureSide() == "left") {

				/*RotateTo* rotateTo = RotateTo::create(0, 90);
				spWeaponReverse->runAction(rotateTo);*/
				showWeaponPicture(2);
				spWeaponReverse->setRotation(90);
				/*log(" left Angle: %f", spWeaponReverse->getRotation());*/
			}
			else if (getVisiblePictureSide() == "right") {

				/*RotateTo* rotateTo = RotateTo::create(0, 270);
				spWeapon->runAction(rotateTo);*/
				showWeaponPicture(1);
				spWeapon->setRotation(270);
				/*log(" right Angle: %f", spWeapon->getRotation());*/
			}
			break;
		}
		case(ERocker8Direction::rockerUpLeft): {
			/*showWeaponPicture(2);
			RotateTo* rotateTo = RotateTo::create(0, 45);
			spWeaponReverse->runAction(rotateTo);*/
			showWeaponPicture(2);
			spWeaponReverse->setRotation(45);
			/*log(" left Angle: %f", spWeaponReverse->getRotation());*/
			break;
		}
		case(ERocker8Direction::rockerLeft): {
			/*showWeaponPicture(2);
			RotateTo* rotateTo = RotateTo::create(0, 0);
			spWeaponReverse->runAction(rotateTo);*/
			showWeaponPicture(2);
			spWeaponReverse->setRotation(0);
			/*log(" left Angle: %f", spWeaponReverse->getRotation());*/
			break;
		}
		case(ERocker8Direction::rockerDownLeft): {
			/*showWeaponPicture(2);
			RotateTo* rotateTo = RotateTo::create(0, 315);
			spWeaponReverse->runAction(rotateTo);*/
			showWeaponPicture(2);
			spWeaponReverse->setRotation(315);
			/*log(" left Angle: %f", spWeaponReverse->getRotation());*/
			break;
		}
		case(ERocker8Direction::rockerDown): {
			if (getVisiblePictureSide() == "left") {
				showWeaponPicture(2);
				spWeaponReverse->setRotation(270);
				/*RotateTo* rotateTo = RotateTo::create(0, 270);
				spWeaponReverse->runAction(rotateTo);*/
				/*log(" left Angle: %f", spWeaponReverse->getRotation());*/
			}
			else if (getVisiblePictureSide() == "right") {
				showWeaponPicture(1);
				spWeapon->setRotation(90);
				/*RotateTo* rotateTo = RotateTo::create(0, 90);
				spWeapon->runAction(rotateTo);*/
				/*log(" right Angle: %f", spWeapon->getRotation());*/
			}
			break;
		}
		case(ERocker8Direction::rockerDownRight): {
			/*showWeaponPicture(1);
			RotateTo* rotateTo = RotateTo::create(0, 45);
			spWeapon->runAction(rotateTo);*/
			showWeaponPicture(1);
			spWeapon->setRotation(45);
			/*log(" right Angle: %f", spWeapon->getRotation());*/
			break;
		}
		default:break;
		};

	}

	if (rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {

		_isCanMove = false;
		_isAttacking = true;
		_hasAnimation = true;

		return;
	}
}

bool Weapon::attack() {
	return false;
}




void Weapon::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}

Point Weapon::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();
	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;
	return Point(x, y);
}

void Weapon::updateCurrentLocation() {

	if (!_owner) return;
	setPosition(Point(_owner->getPositionX(), _owner->getPositionY() - 7));
	Point weaponXYPos = this->getPosition();


	auto pos = tileCoordForPosition(weaponXYPos);
	auto mapSize = m_map->getMapSize();
	this->setPositionZ(pos.y - mapSize.height);


	Sprite* spWeapon = (Sprite*)getChildByTag(TAG_WEAPON1);
	Sprite* spWeaponReverse = (Sprite*)getChildByTag(TAG_WEAPON2);
	spWeapon->setPosition(Point(0, 0));
	spWeaponReverse->setPosition(Point(0, 0));


}
