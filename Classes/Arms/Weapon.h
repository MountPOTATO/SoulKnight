#ifndef __WEAPON_H___
#define __WEAPON_H___

#include "cocos2d.h"
#include "Buff/WeaponBuff.h"
#include "HelloWorldScene.h"
#include <string>
#include <iostream>
using namespace cocos2d;


//TODO:常量移到专门的常量库里
enum ESide {
	sideHero,
	sideMonster,
	sidePet,
	sideHelper
};

enum EWeaponDirection {
	weaponUp,
	weaponDown,
	weaponLeft,
	weaponRight,
	weaponUpLeft,
	weaponUpRight,
	weaponDownLeft,
	weaponDownRight,
	weaponStop,//没有键盘输入状态
	weaponAttackingEnermy//检测到敌人存在时射击状态
};

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
	/*CC_SYNTHESIZE(HelloWorld*, _currentScene, CurrentScene);*/	
	CC_SYNTHESIZE(ESide, _side, Side);//武器持有者
	//CC_SYNTHESIZE(Entity*, _target, Target);//武器攻击者

	//时间信息
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);

	//武器状态
	CC_SYNTHESIZE(bool, _heroOwned, HeroOwned);//是否被英雄所持有，如果是则对应一系列键盘输入，如果否则对应射击型怪物的情况
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(bool, _isCanMove, IsCanMove);//是否可以动(键盘不输入时不可以动)




	CC_SYNTHESIZE(EWeaponDirection, _ewDirection, EwDirection);

	EventListenerKeyboard* listenerKeyboard;//键盘监听
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, int type);
	virtual bool updateDirection();

	/*Point getAnglePosition(float r, float angle);*/

public:

	Vector<WeaponBuff*> _vecWeaponBuff;


	virtual void takeBuff(WeaponBuff* weaponBuff);
	virtual void cancelBuff(WeaponBuff* weaponBuff);
	virtual void deleteTempBuff();
	virtual void clearBuff();

	virtual bool attack();//TODO:待多态形式

	
	//void stopWeapon();TODO

	static Weapon* create
	(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool _heroOwned);
	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool _heroOwned);
	void startWeapon(bool _isStopOther);

	void showWeaponPicture(int type);//1代表指向右边的图片，2代表指向左边（反向）的图片
	
	const char* getVisiblePictureSide()const;//如果右边图可视返回"right",反之"left";

	Sprite* getVisiblePicture()const;

	//get函数集合
	float getAttackRange()const { return _attackRange; }

protected:

	//TODO:编辑InitBasicInfo
	/*virtual void initBasicInfo(ESide side);*/

};



#endif