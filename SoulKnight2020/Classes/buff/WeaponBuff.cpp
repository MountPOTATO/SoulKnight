#include "WeaponBuff.h"

bool WeaponBuff::init(EWeaponBuffEffect weaponBuffEffect,
	INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
	int energyCost, float precision,
	float lastTime
) {
	if (!Sprite::init()) return false;

	m_weaponBuffEffect = weaponBuffEffect;

	m_attack = attack;	
	m_attackSpeed = attackSpeed;
	m_attackRange = attackRange;
	m_hardStrikeRate = hardStrikeRate;

	m_energyCost = energyCost;
	m_precision = precision;

	m_beginTime = GetCurrentTime() / 1000.f;
	m_lastTime = lastTime;
	m_endTime = m_beginTime + m_lastTime;

	return true;
}

WeaponBuff* WeaponBuff::create(EWeaponBuffEffect weaponBuffEffect,
	INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
	int energyCost, float precision,
	float lastTime
) {
	WeaponBuff* buff = new WeaponBuff;
	if (buff) {
		if (buff->init(weaponBuffEffect,
			attack,attackSpeed,attackRange,hardStrikeRate,
			energyCost,precision,
			lastTime)) {

			buff->autorelease();
			return buff;
		}
	}
	CC_SAFE_DELETE(buff);
	return NULL;
}		

//TODO:init的第二种形式编辑