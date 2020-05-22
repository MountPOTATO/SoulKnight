#ifndef __WEAPONBUFF_H__
#define __WEAPONBUFF_H__


#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

//buff效果的体现
enum EWeaponBuffEffect {
	//几个设想的基础buff状态,可在此添加

	WbuffLimitBreak, //大招（不确定，只是针对单纯武器基础性能改变的大招，对特殊功能如召唤等大招不确定）
	WbuffStrengthen,  //武器加强buff
	WbuffClean		//默认状态

};

class WeaponBuff :public Sprite {
public:
	CC_SYNTHESIZE(EWeaponBuffEffect, m_weaponBuffEffect, WeaponBuffEffect);//buff种类

	//基础属性

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
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//开始时间
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//持续时间
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//结束时间





	//TODO:若增加BUFF属性，此处列表要添加
	//按所想的分类大致分好行
	virtual bool init(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed,float attackRange,float hardStrikeRate,
		int energyCost,float precision,
		float lastTime
	);

	//TODO:若增加BUFF属性，此处列表要修改
	virtual bool init(ValueVector& data);

	//TODO:若增加BUFF属性，此处列表要修改
	static WeaponBuff* create(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
		int energyCost, float precision,
		float lastTime
	);

};




#endif


