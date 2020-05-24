#ifndef __ENTITYBUFF_H__
#define __ENTITYBUFF_H__



#include "cocos2d.h"

USING_NS_CC;

//buff效果的体现
enum EEntityBuffEffect {
	//几个设想的基础buff状态,可在此添加
	EbuffFrozen,	//冻结	
	EbuffPoisoned,	//中毒
	EbuffBurning,	//火烧（爆炸？）
	EbuffSpeedUp,	//加速
	EbuffSlowDown,	//减速


	EbuffLimitBreak, //大招（不确定，只是针对单纯基础性能改变的大招，对特殊功能如召唤等大招不确定）
	EbuffInvincible,//无敌(可能有护盾状态?)

	EbuffClean			//默认状态

};

class EntityBuff :public cocos2d::Sprite {
public:
	CC_SYNTHESIZE(EEntityBuffEffect, m_entityBuffEffect, EntityBuffEffect);//buff种类

	//基础属性
	CC_SYNTHESIZE(INT32, m_defence, Defence); //防御
	//TODO:可能有后续防御模式，如近战伤害防御，远程攻击防御，防护盾BUFF等，视后续开发情况添加


	CC_SYNTHESIZE(INT32, m_HP, HP)//血量
	CC_SYNTHESIZE(INT32, m_armor, Armor)//护甲
	CC_SYNTHESIZE(INT32, m_MP, MP)//魔力
	CC_SYNTHESIZE(float, m_moveSpeed, MoveSpeed);//移动速度


	CC_SYNTHESIZE(float, m_limitBreakRecoverSpeed, LimitBreakRecoverSpeed);//技能冷却速度

	//不那么基础的属性

	CC_SYNTHESIZE(INT32, m_HPRecoverSpeed, HPRecoverSpeed)//血量自动回复速度，视后续功能而定(！可能会减）
	CC_SYNTHESIZE(INT32, m_armorRecoverSpeed, ArmorRecoverSpeed)//护甲自动回复速度，视后续功能而定
	CC_SYNTHESIZE(INT32, m_MPRecoverSpeed, MPRecoverSpeed)//血量自动回复速度，视后续功能而定

	//概率事件
	CC_SYNTHESIZE(float, m_hardStrikeRate, HardStrikeRate);//暴击率，视后续功能而定


	//时间间隔
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//开始时间
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//持续时间
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//结束时间

	//TODO:若增加BUFF属性，此处列表要添加
	//按所想的分类大致分好行
	virtual bool init(EEntityBuffEffect entityBuffEffect,
		INT32 defence,
		INT32 HP, INT32 armor, INT32 MP,float moveSpeed, 
		float limitBreakRecoverSpeed,
		INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
		float hardStrikeRate,
		float lastTime
	);

	//TODO:若增加BUFF属性，此处列表要修改

	//TODO:添加vector型init方式
	/*virtual bool init(ValueVector& data);*/

	//TODO:若增加BUFF属性，此处列表要修改
	static EntityBuff* create(EEntityBuffEffect entityBuffEffect,
		INT32 defence,
		INT32 HP, INT32 armor, INT32 MP, float moveSpeed,
		float limitBreakRecoverSpeed,
		INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
		float hardStrikeRate,
		float lastTime
	);

};




#endif


