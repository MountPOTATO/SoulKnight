

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
#include "Arms/MeleeDerived/Wand.h"
#include "Arms/Melee.h"
#include "Arms/GunDerived/SMG.h"
#include "Arms/GunDerived/Shotgun.h"
#include "Arms/GunDerived/Sniper.h"
#include "LongRangeAttack/Bullet.h"
#include "ControllerByKeyBoard/ControllerOfEightDir.h"
//#include "Entity/Character.h"
#include "Entity/Heros/Knight.h"
#include "Entity/Enemy/Ranger.h"
#include "Interaction/DirectPickThing.h"
#include "Interaction/InterContent/PickWeapon.h"
#include "Interaction/InterContent/TreasureBox.h"
#include "Interaction/PickBottle.h"
#include "Interaction/SpecialEffectArea/AccelerateArea.h"
#include "Interaction/InterContent/TransferPortal.h"
#include "FlowWord/FlowWord.h"
#include "Map/Space.h"
#include "MonsterManager/MonsterManager.h"
#include "Pause/PauseLayer.h"

class Weapon;
class Character;


class HelloWorld : public cocos2d::Scene
{

	CC_SYNTHESIZE(bool, _hasDerivedInfo, HasDerivedInfo);

public:
	
	static cocos2d::Scene* createScene(int order, HeroInfo heroinfo);
	static cocos2d::Scene* createScene();

	CC_SYNTHESIZE(INT32,_mapOrder, MapOrder);

	CC_SYNTHESIZE(Character*, _hero, Hero);

	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);

	CC_SYNTHESIZE(Sprite*, pauseBtn, PauseBtn);


	virtual bool init();

	bool init(int order,HeroInfo heroinfo);

	bool safeHouseInit();

	bool BattleHouseInit();

	void resetWeapon(HeroInfo heroinfo);


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuReGenerateCallBack(cocos2d::Ref* pSender);
	void menuLoseCallBack(cocos2d::Ref* pSender);
	void menuWinCallBack(cocos2d::Ref* pSender);

	void clear();
	

////////////////////////////////////////////////////////////////////////////////////////////////////////
	//srq测试随机地图
	//std::vector<Space*>appliedSpace;
	//int roomCount;
	//std::vector<int> typeNum;
	//bool roomNotFull(int type);
	//std::vector<std::vector<int>> placement;
	//cocos2d::CCTMXTiledMap* curMap;
	//Character* _knight;
	////virtual bool initMaps();
	////virtual void updateMap();
	////virtual void findCurMap(Character*);
	/////*cocos2d::EventListenerKeyboard* listenerKeyBoard;*/
	////virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);//测试地图用
	//////修改添加
	//void addCharacter(Character* hero, TMXTiledMap* map);//改写自原初始函数
	//Node* _parent;//尝试保存player->getParent(),暂时不知道有没有作用
	
////////////////////////////////////////////////////////////////////////////////////////////////////////

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	virtual void update(float delta);//更新状态


	TransferPortal* _portal;
	void checkPortalState();

	//容器集
	Vector<Bullet*> _bullets;
	Vector<Monster*> _currentEnemy;
	Vector<Bullet*> _enemyBullet;
	float _firetime;
	Vector<PickWeapon*> _pickableWeaponVec;
	Vector<PickBottle*> _pickableBottleVec;
	Vector<TreasureBox*> _treasureBoxVec;
	cocos2d::Vector<Sprite*> _energyVec;//能量掉落物Vector
	cocos2d::Vector<Sprite*> _coinVec;//金币掉落物Vector
	//加速区域以及时间元素
	Vector<AccelerateArea*> _accelerateAreaVec;
	Vector<MonsterManager*>_monsterManageerVec;
	


	//容器维护更新
	void updateTreasureBoxVec();
	void updateAccelerateArea();
	void updatePickBottleVec();
	void updateBullet();
	void updateDirectPickThingSprite();
	void updatePickWeaponAndWeapon();

	/*void updateBuffSkills();*/


	//初始化摇杆
	void initHRocker();

	
	//人物武器
	Weapon* _weapon1;
	Weapon* _weapon2;
	Weapon* _emptyHandWeapon;
	void updateWeaponHolding();//更新持有的武器（切换武器）
	Weapon* _currentUsedWeapon;//当下武器

	
	//地图
	TMXTiledMap* _map;


	//冷却时间记录
	CC_SYNTHESIZE(float, _lastPickTime, LastPicTime);
	CC_SYNTHESIZE(float, _lastSwitchTime, LastPickTime);
	CC_SYNTHESIZE(float, _lastSkillTime, LastSkillTime);
	clock_t startTime = 0;//加速带时间元素
	clock_t endTime = 0;


	//捡拾武器所需
	void transferPickWeaponToWeapon(PickWeapon*,Character*);
	void transferWeaponToPickWeapon(Weapon*, Character*);



	//TODO:加入Vector
	CC_SYNTHESIZE(DirectPickThing*, _direct, Direct);//单个DirectPickThing类，后期应加入Vector



public:
	/*Character* addCharacter(TMXTiledMap* map,int HeroID);*/

	Character* addCharacter(TMXTiledMap* map, int HeroID);
	
	//加载ui
	//bool loadUI(const char* file);
private:
	
	

	//监听装置
	EventListenerTouchOneByOne* listenerTouch;
	EventListenerKeyboard* listenerKeyBoard;
	//键盘输入
	
};




#endif // __HELLOWORLD_SCENE_H__
