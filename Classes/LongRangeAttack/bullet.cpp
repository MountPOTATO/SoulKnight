#include "Bullet.h"
#include "math.h"
#include "Arms/Weapon.h"



bool Bullet::init
	(const char* bulletImageName, float attack, float flyingSpeed, Weapon* shooter, Entity* target, WeaponBuff* buff) {
	if (!Sprite::init()) return false;

	setTexture(bulletImageName);
	setPosition(shooter->getPosition());
	

	_attack = attack;
	_flyingSpeed = flyingSpeed;
	_shooter = shooter;
	_target = target;
	_buff = buff;
}

void Bullet::calPosition() {
	
	if (!_target) {
		float angle;
		if (_shooter->getVisiblePictureSide() == "left") {
			angle = _shooter->getVisiblePicture()->getRotation();
			setRotation(angle-180.f);
		}
		else if (_shooter->getVisiblePictureSide() == "right") {
			angle = _shooter->getVisiblePicture()->getRotation();
			setRotation(angle);
		}
		//TODO：帧率确认与同步问题，现在只有机械设置
		setPosition(getPosition() + Vec2(cos(angle) * _flyingSpeed / 60, sin(angle) * _flyingSpeed / 60));
	}
	//TODO:target不为空时,需要实体类的实现,瞄准实体类后的结果

}

void Bullet::calDistance() {
	if (!_target) {
		//TODO:需要Entity的获取位置函数，需要等后续完成
	}
}