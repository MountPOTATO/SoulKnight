#ifndef __WEAPONBUFF_H__
#define __WEAPONBUFF_H__


#include "cocos2d.h"
#include "Const/ConstInfo.h"
using namespace cocos2d;
USING_NS_CC;


class WeaponBuff :public Sprite {
public:
	CC_SYNTHESIZE(EWeaponBuffEffect, m_weaponBuffEffect, WeaponBuffEffect);//buff种类

	//基础属性
	CC_SYNTHESIZE(bool, m_isTempBuff, IsTempBuff);//是否为暂时性buff，如limitBreak等
	//攻击性能
	CC_SYNTHESIZE(INT32, m_attack, Attack); //攻击力
		//TODO:可能有其他攻击形式，如近战，远战，元素，魔法等，视后续开发情况添加
	CC_SYNTHESIZE(float, m_attackSpeed, AttackSpeed);//攻击速度(两个攻击之间间隔时间)
	CC_SYNTHESIZE(float, m_attackRange, AttackRange);//攻击范围
	CC_SYNTHESIZE(float, m_hardStrikeRate, HardStrikeRate);//暴击率，视后续功能而定

	//辅助性能
	CC_SYNTHESIZE(int, m_energyCost, EnergyCost);//能量消耗
	CC_SYNTHESIZE(float, m_precision, Precision);//精准度


	//时间间隔
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//开始时间，-1代表是永久buff，没有起始时间
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//持续时间,-1为永久
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//结束时间,-1代表是永久buff，没有结束时间

	bool isATempWeaponBuff()const { return m_isTempBuff; }
	INT32 getWeaponBuffAttack()const { return m_attack; }
	float getWeaponBuffAttackSpeed()const { return m_attackSpeed; }
	float getWeaponBuffAttackRange()const { return m_attackRange; }
	float getWeaponBuffHardStrikeRate()const { return m_hardStrikeRate; }
	int getWeaponBuffEnergyCost()const { return m_energyCost; }
	float getWeaponBuffPrecision()const { return m_precision; }
	float getWeaponBuffLastTime()const { return m_lastTime; }
	float getWeaponBuffEndTime()const { return m_endTime; }



	//TODO:若增加BUFF属性，此处列表要添加
	//按所想的分类大致分好行
	virtual bool init(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed,float attackRange,float hardStrikeRate,
		int energyCost,float precision,
		float lastTime
	);

	//TODO:若增加BUFF属性，此处列表要修改
	/*virtual bool init(ValueVector& data);*/

	//TODO:若增加BUFF属性，此处列表要修改
	static WeaponBuff* create(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
		int energyCost, float precision,
		float lastTime
	);

	//叠加态的武器buff
	
};




#endif


