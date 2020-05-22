#include "EntityBuff.h"

bool EntityBuff::init(EEntityBuffEffect entityBuffEffect,
	INT32 defence,
	INT32 HP, INT32 armor, INT32 MP, float moveSpeed,
	float limitBreakRecoverSpeed,
	INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
	float hardStrikeRate,
	float lastTime
) {
	if (!Sprite::init()) return false;
	
		m_entityBuffEffect = entityBuffEffect;
	
		m_defence = defence;
	
		m_HP = HP;
		m_armor = armor;
		m_MP = MP;	
		m_moveSpeed = moveSpeed;
		m_limitBreakRecoverSpeed = limitBreakRecoverSpeed;
	

		m_HPRecoverSpeed = HPRecoverSpeed;
		m_armorRecoverSpeed = armorRecoverSpeed;
		m_MPRecoverSpeed = MPRecoverSpeed;
	
		m_hardStrikeRate = hardStrikeRate;
	
		m_beginTime = GetCurrentTime() / 1000.f;
		m_lastTime = lastTime;
		m_endTime = m_beginTime + m_lastTime;
	
		return true;
}

EntityBuff* EntityBuff::create(EEntityBuffEffect entityBuffEffect,
	INT32 defence,
	INT32 HP, INT32 armor, INT32 MP, float moveSpeed,
	float limitBreakRecoverSpeed,
	INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
	float hardStrikeRate,
	float lastTime
) {
	EntityBuff* buff = new EntityBuff;
	if (buff) {
		if (buff->init(entityBuffEffect,
			defence,
			HP, armor,MP,moveSpeed,
			limitBreakRecoverSpeed,
			HPRecoverSpeed,armorRecoverSpeed,MPRecoverSpeed,
			hardStrikeRate,
			lastTime
			)) {

			buff->autorelease();
			return buff;
		}
	}

	CC_SAFE_DELETE(buff);
	return NULL;
}


//TODO:init的第二种形式编辑