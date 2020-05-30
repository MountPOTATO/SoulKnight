#ifndef __WEAPON_H___
#define __WEAPON_H___

#include "cocos2d.h"
#include "Buff/WeaponBuff.h"
#include "Controller/HRocker.h"


#include <string>
#include <iostream>
#include <Const/ConstInfo.h>
#include "Entity/Entity.h"


using namespace cocos2d;

#define PRESS 1
#define RELEASE 2

#define TAG_WEAPON1 1
#define TAG_WEAPON2 2


class HelloWorld;


//TODO:常量移到专门的常量库里



class Weapon :public Sprite {
private:
	bool m_upState, m_downState, m_leftState, m_rightState;
	//武器属性：
	//固有的属性（可变动）
	CC_SYNTHESIZE(INT32, _attack, Attack); //攻击力
		//TODO:可能有其他攻击形式，如近战，远战，元素，魔法等，视后续开发情况添加
	
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);//攻击速度(两个攻击之间间隔时间)
	CC_SYNTHESIZE(float, _attackRange, AttackRange);//攻击范围
	CC_SYNTHESIZE(float, _hardStrikeRate, HardStrikeRate);//暴击率，视后续功能而定
	CC_SYNTHESIZE(int, _energyCost, EnergyCost);//能量消耗
	CC_SYNTHESIZE(float, _precision, Precision);//精准度

	//固有的属性（不可变动）
	CC_SYNTHESIZE(String,_weaponName, WeaponName);
	CC_SYNTHESIZE(INT32, _weaponPrice, WeaponPrice);

	//场景，持有信息
	CC_SYNTHESIZE(HelloWorld*, _currentScene, CurrentScene);	
	CC_SYNTHESIZE(ESide, _side, Side);//武器持有者
	CC_SYNTHESIZE(Entity*, _target, Target);//武器攻击者

	//时间信息
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);



	//角度信息
	CC_SYNTHESIZE(float, _mathAngle, MathAngle);
	CC_SYNTHESIZE(float, _targetMathRad, TargetMathRad);
	float getWeaponTargetMathRad()const { return _targetMathRad; }

	//武器状态
	CC_SYNTHESIZE(bool, _heroOwned, HeroOwned);//是否被英雄所持有，如果是则对应一系列键盘输入，如果否则对应射击型怪物的情况
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);//是否在攻击
	CC_SYNTHESIZE(bool, _isCanMove, IsCanMove);//是否可以动(键盘不输入时不可以动)
	CC_SYNTHESIZE(bool, _hasAnimation, HasAnimation);//是否有动画（如有，暂时禁用图片更新）

	bool hasMeleeAnimation()const { return _hasAnimation; }


public:

	Vector<WeaponBuff*> _vecWeaponBuff;


	virtual void takeBuff(WeaponBuff* weaponBuff);
	virtual void cancelBuff(WeaponBuff* weaponBuff);
	virtual void deleteTempBuff();
	virtual void clearBuff();

	virtual bool attack();//TODO:待多态形式
	INT32 getWeaponAttack()const { return _attack; }
	HelloWorld* getWeaponCurrentScene() { return this->_currentScene; }
	//void stopWeapon();TODO


	//角度信息：
	float getRad(Point point1, Point point2)const;


	static Weapon* create
	(const char* weaponImageName1, const char* weaponImageName2,
	  HelloWorld* currentScene,ESide side, bool _heroOwned);

	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2,
	  HelloWorld* currentScene, ESide side, bool heroOwned);

	void startWeapon(bool _isStopOther);

	void showWeaponPicture(int type);//1代表指向右边的图片，2代表指向左边（反向）的图片
	
	const char* getVisiblePictureSide()const;//如果右边图可视返回"right",反之"left";

	Sprite* getVisiblePicture()const;

	//get函数集合
	/*float getAttackRange()const { return this->_attackRange; }*/
	void updateImageRotation(HRocker* rocker);

	virtual void updateTarget();


protected:

	//TODO:编辑InitBasicInfo
	/*virtual void initBasicInfo(ESide side);*/

};



#endif