

/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "Controller/HRocker.h"
#include "Arms/GunDerived/OldPistol.h"
#include "Arms/Gun.h"
#include "Arms/MeleeDerived/Fish.h"
#include "Arms/Melee.h"
#include "Arms/GunDerived/SMG.h"
#include "Arms/GunDerived/Shotgun.h"
#include "Arms/GunDerived/Sniper.h"
#include "LongRangeAttack/Bullet.h"
#include "ControllerByKeyBoard/ControllerOfEightDir.h"
#include "Entity/Character.h"
#include "Entity/Heros/Knight.h"
#include "Entity/Enemy/Ranger.h"
#include "Interaction/DirectPickThing.h"
#include "Interaction/InterContent/PickWeapon.h"
#include "Interaction/InterContent/TreasureBox.h"
#include "Interaction/PickBottle.h"
<<<<<<< HEAD
=======



>>>>>>> fd2e215e90434deea13e29cc08059450435790b7
class Weapon;

class HelloWorld : public cocos2d::Scene
{
	//5.18加入CCSYNTHESIZE 控制器类
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);

	CC_SYNTHESIZE(Character*, _hero, Hero);

	CC_SYNTHESIZE(Ranger*, _testMonster, TestMonster);

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	virtual void update(float delta);//更新状态
	void updateBullet();
	void updateDirectPickThingSprite();
	void updatePickWeaponAndWeapon();

	//容器集
	Vector<Bullet*> _bullets;

	Vector<Entity*> _currentUnit;

	Vector<Monster*> _currentEnemy;
	Vector<Bullet*> _enemyBullet;
	float _firetime;

	//test
	Vector<Character*>_test;

	cocos2d::Vector<Sprite*> _energyVec;//能量掉落物Vector
	cocos2d::Vector<Sprite*> _coinVec;//金币掉落物Vector

	Vector<TreasureBox*> _treasureBoxVec;
	void updateTreasureBoxVec();

	

	//初始化摇杆
	void initHRocker();

	//测试组件:

	Weapon* _weapon1;
	Weapon* _weapon2;
	Weapon* _emptyHandWeapon;
	void updateWeaponHolding();//更新持有的武器（切换武器）

	Vector<Weapon*> _weaponVec;//武器Vector(定)
	Weapon* _currentUsedWeapon;//当下武器
	Vector<PickWeapon*> _pickableWeaponVec;
	Vector<PickBottle*> _pickableBottleVec;
	void updatePickBottleVec();


	CC_SYNTHESIZE(TMXTiledMap*, _map, Map);
	CC_SYNTHESIZE(float, _lastPickTime, LastPicTime);
	CC_SYNTHESIZE(float, _lastSwitchTime, LastPickTime);



	
	void transferPickWeaponToWeapon(PickWeapon*,Character*);
	void transferWeaponToPickWeapon(Weapon*, Character*);



	//TODO:加入Vector
	CC_SYNTHESIZE(DirectPickThing*, _direct, Direct);//单个DirectPickThing类，后期应加入Vector



public:
	Character* addCharacter(TMXTiledMap* map,int HeroID);
	
	//加载ui
	//bool loadUI(const char* file);

private:
	
	

	//监听装置
	EventListenerTouchOneByOne* listenerTouch;
	EventListenerKeyboard* listenerKeyBoard;
	//键盘输入
	
};

#endif // __HELLOWORLD_SCENE_H__
