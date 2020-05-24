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
		//TODO��֡��ȷ����ͬ�����⣬����ֻ�л�е����
		setPosition(getPosition() + Vec2(cos(angle) * _flyingSpeed / 60, sin(angle) * _flyingSpeed / 60));
	}
	//TODO:target��Ϊ��ʱ,��Ҫʵ�����ʵ��,��׼ʵ�����Ľ��

}

void Bullet::calDistance() {
	if (!_target) {
		//TODO:��ҪEntity�Ļ�ȡλ�ú�������Ҫ�Ⱥ������
	}
}