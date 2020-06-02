#include "Bullet.h"
#include "math.h"
#include <ctime>
#include "Arms/Weapon.h"
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

bool Bullet::init
(const char* bulletImageName,  float flyingSpeed, Weapon* shooter,  WeaponBuff* buff, bool hasDef) {
	if (!Sprite::init()) return false;
	if (!shooter) return false;

	setTexture(bulletImageName);
	setPosition(shooter->getPosition());

	setVisible(true);

	_attack = shooter->getWeaponAttack();
	_flyingSpeed = shooter->getWeaponBulletFlyingSpeed();
	_shooter = shooter;
	/*_target = target;*/
	_buff = buff;
	_hasDeflection = hasDef;
	
	//�Ƕȳ�ʼ����;
	auto shooterAngle = _shooter->getVisiblePicture()->getRotation();
	float bulletRotateAngle;
	log("%f", shooterAngle);
	if (_shooter->getVisiblePictureSide() == "left") {
		if (shooterAngle >= -90 && shooterAngle <= 0) {
			_initAngle = (180.f - shooterAngle);
			bulletRotateAngle = 360.f - _initAngle;
		}
		else if (shooterAngle >= 0.f && shooterAngle <= 90.f) {
			_initAngle = 180.f - shooterAngle;//���ڳ������ʱ������ͼƬ�������ң���
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
	//ת�ɻ�����
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
		
		//TODO��֡��ȷ����ͬ�����⣬����ֻ�л�е����
	setPosition(getPosition() + 
		Vec2(cos(_initAngle) * _flyingSpeed / 60, sin(_initAngle) * _flyingSpeed / 60));
	
	//}
	//TODO:target��Ϊ��ʱ,��Ҫʵ�����ʵ��,��׼ʵ�����Ľ��

}

void Bullet::calDistance() {
	//TODO:�����ӵ����룿
	/*if (!_target) {*/
		//TODO:��ҪEntity�Ļ�ȡλ�ú�������Ҫ�Ⱥ������
	/*}*/
}