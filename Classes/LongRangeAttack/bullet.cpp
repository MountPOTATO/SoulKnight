#include "Bullet.h"
#include "math.h"
#include <ctime>
#include "Arms/Weapon.h"
#include "Entity/Monster.h"
#include "Const/ConstInfo.h"
#define TAG_BULLET -1
Bullet* Bullet::create
(const char* bulletImageName, float flyingSpeed, Weapon* shooter,  WeaponBuff* buff,bool hasDef) {
	Bullet* bullet = new(std::nothrow)Bullet;
	if (bullet && bullet->init(bulletImageName, flyingSpeed, shooter,  buff, hasDef)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;

}

Bullet* Bullet::create
(const char* bulletImageName, float flyingSpeed, Monster* monster, float Angle) {
	Bullet* bullet = new(std::nothrow)Bullet;
	if (bullet && bullet->init(bulletImageName, flyingSpeed, monster,Angle)) {
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

bool Bullet::init
(const char* bulletImageName, float flyingSpeed, Monster* monster, float AngleRad) {
	if (!Node::init()) return false;
	Sprite* spBullet = Sprite::create(bulletImageName);
	spBullet->setTexture(bulletImageName);
	setPosition(monster->getPosition());
	spBullet->setPosition(0, 0);
	setVisible(true);
	spBullet->setVisible(true);
	this->addChild(spBullet);

	_initAngle = AngleRad;
	_attack = 3;
	_flyingSpeed = flyingSpeed;
	

	int angle = _initAngle / PI * 180;

	spBullet->setRotation(360-angle);
}

bool Bullet::init
(const char* bulletImageName,  float flyingSpeed, Weapon* shooter,  WeaponBuff* buff, bool hasDef) {
	if (!Node::init()) return false;
	if (!shooter) return false;

	Sprite* spBullet = Sprite::create(bulletImageName);
	spBullet->setTexture(bulletImageName);
	setPosition(shooter->getPosition());
	spBullet->setPosition(0, 0);

	setVisible(true);
	spBullet->setVisible(true);
	this->addChild(spBullet);

	_attack = shooter->getWeaponAttack();
	_flyingSpeed = shooter->getWeaponBulletFlyingSpeed();
	_shooter = shooter;
	/*_target = target;*/
	_buff = buff;
	_hasDeflection = hasDef;
	
	//角度初始计算;
	auto shooterAngle = _shooter->getVisiblePicture()->getRotation();
	float bulletRotateAngle;
	//log("%f", shooterAngle);
	if (_shooter->getVisiblePictureSide() == "left") {
		if (shooterAngle >= -90 && shooterAngle <= 0) {
			_initAngle = (180.f - shooterAngle);
			bulletRotateAngle = 360.f - _initAngle;
		}
		else if (shooterAngle >= 0.f && shooterAngle <= 90.f) {
			_initAngle = 180.f - shooterAngle;//对于常规的逆时针正向图片（分左右）的
			bulletRotateAngle = - _initAngle;
		}
		else if (shooterAngle >= 270.f && shooterAngle <= 360.f) {
			_initAngle = 540.f - shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;

		}
		else if (shooterAngle >= 360.f && shooterAngle <= 450.f) {
			_initAngle = 540.f - shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;
		}
		else if (shooterAngle >= 630.f && shooterAngle <= 720.f) {
			_initAngle = 540.f - shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;
		}

	}
	else if (_shooter->getVisiblePictureSide() == "right") {
		if (shooterAngle >= -90 && shooterAngle <= 0) {
			_initAngle = -shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;
		}
		else if ((shooterAngle >= 0 && shooterAngle <= 90)||(shooterAngle>=270&&shooterAngle<=360)) {
			_initAngle = 360.f - shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;
		}
		else if ((shooterAngle >= 360.f && shooterAngle <= 450.f)) {
			_initAngle = 360.f - shooterAngle;
			bulletRotateAngle = 360.f - _initAngle;
		}
		 
	}
	//转成弧度制
	if (hasDef) {
		float deflection = rand() % (shooter->getWeaponPrecision() * 2 + 1) - (shooter->getWeaponPrecision());
		setRotation(bulletRotateAngle + deflection);
		_initAngle -= deflection;
		_initAngle *= (PI / 180);
	}
	else {
		_initAngle *= (PI / 180);
		setRotation(bulletRotateAngle);
	}
	return true;
}

void Bullet::calPosition() {

	//if (!_target) {
		
		//TODO：帧率确认与同步问题，现在只有机械设置
	setPosition(getPosition() + 
		Vec2(cos(_initAngle) * _flyingSpeed / 60, sin(_initAngle) * _flyingSpeed / 60));
	
	//}
	//TODO:target不为空时,需要实体类的实现,瞄准实体类后的结果

}

void Bullet::calDistance() {
	//TODO:跟踪子弹引入？
	/*if (!_target) {*/
		//TODO:需要Entity的获取位置函数，需要等后续完成
	/*}*/
}

void Bullet::stopBullet() {
	setVisible(false);
}

Point Bullet::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;


	return Point(x, y);
}


void Bullet::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}

bool Bullet::isPosBlocked(Point dstPos) {
	/*int dir;
	Point curPos=this->getPosition();
	if ((dstPos.x - curPos.x) < 0) { dir = 1; }
	else if ((dstPos.y - curPos.y) > 0) { dir = 2; }
	else if ((dstPos.x - curPos.x) > 0) { dir = 3; }
	else if ((dstPos.y - curPos.y) < 0) { dir = 4; }
	else { dir = 0; }
	switch (dir)
	{
	case 1:
		dstPos.x -= 20;
		break;
	case 2:
		dstPos.y += 20;
		break;
	case 3:
		dstPos.x += 20;
		break;
	case 4:
		dstPos.y -= 20;
		break;
	case 0:
		break;
	default:
		break;
	}
	//暂缺*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));

	int tiledGid = meta->getTileGIDAt(tiledPos);//获取这个格子的唯一标识

	//判断这个格子是否存在
	if (tiledGid != 0) {

		auto propMap = m_map->getPropertiesForGID(tiledGid).asValueMap();

		if (propMap.find("Collidable") != propMap.end()) {
			//获取格子的Collidable属性
			Value prop = propMap.at("Collidable");
			if (prop.asString().compare("true") == 0) {
				//发现这个格子属性为true，不让玩家继续移动
				return true;
			}
		}
	}
	return false;//反之，返回false
}
