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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "Const/ConstInfo.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//test Entity can delete


	//此处修改,初始化一样武器实例,以SMG冲锋枪为例
	/*test_InitFish();*/
	/*test_InitPistol();*/

	//test_InitShotgun();

	//测试自动瞄准时加上，不需要测试时去掉,同时在update函数中添加相应的模块
	


	//测试地图和角色
	//先放人物再放武器
	_map = TMXTiledMap::create("Maps/test.tmx");
	this->addChild(_map);
	//初始化英雄
	_hero = addCharacter(_map, 1);

	

	initHRocker();

	//初始武器
	auto initWeapon = OldPistol::create
	("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
	this->addChild(initWeapon);
	initWeapon->startWeapon(true);
	initWeapon->setTiledMap(_map);
	initWeapon->setOwner(_hero);
	_currentUsedWeapon = initWeapon;



	_weapon1 = _currentUsedWeapon;
	_weapon2 = nullptr;


	


	//测试掉落物直接减起,后期加入Vector
	_direct = DirectPickThing::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 250), _hero, 20.f, 3, 3, 5, this);
	this->addChild(_direct);

	auto treasureBox=TreasureBox::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 100), _hero, this, _rocker);
	this->addChild(treasureBox);
	_treasureBoxVec.pushBack(treasureBox);
	






	this->scheduleUpdate();
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}


void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	this->addChild(_rocker);
	_rocker->startRocker(true);

}




//测试函数：初始化武器实例（破旧的手枪，鱼（尚方宝剑），冲锋枪，霰弹枪）






void HelloWorld::update(float delta) {


	

	//更新掉落物
	_direct->updatePickThingSprite();


	updateTreasureBoxVec();
	updatePickBottleVec();
	updateWeaponHolding();
	updatePickWeaponAndWeapon();

	//武器

	auto i = _currentUnit.begin();
	
	
	_currentUsedWeapon->updateTarget();
	_currentUsedWeapon->updateImageRotation(_rocker);
	_currentUsedWeapon->updateCurrentLocation();
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键

	_currentUsedWeapon->attack();//攻击，发射子弹

	/*}*/
	updateBullet();//更新飞行物




}

void HelloWorld::updateBullet() {
	//TODO:只添加了射击现象
	for (auto i = _bullets.begin(); i != _bullets.end(); i++) {
		(*i)->setVisible(true);
		(*i)->calPosition();
	}
}

void HelloWorld::updateWeaponHolding() {
	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastSwitchTime < SWITCH_TIMESPACE) { return; }

	if (_rocker->isPressSwitch()) {
		if (_currentUsedWeapon == _weapon1&&_weapon2) {
			_lastSwitchTime = currentTime;
			_weapon1->stopWeapon(true);
			_currentUsedWeapon = _weapon2;
			_currentUsedWeapon->startWeapon(true);
		}
		else if (_currentUsedWeapon == _weapon2 && _weapon1) {
			_lastSwitchTime = currentTime;
			_weapon2->stopWeapon(true);
			_currentUsedWeapon = _weapon1;
			_currentUsedWeapon->startWeapon(true);
		}
	}
}

void HelloWorld::updatePickWeaponAndWeapon() {
	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastPickTime < PICK_TIMESPACE) { return; }

	//更新场景中可捡起物体
	for (auto i = _pickableWeaponVec.begin(); i != _pickableWeaponVec.end();) {
		
		(*i)->updatePickWeaponState();
		
		if ((*i)->objectIsPressed()) {//其中一个PickWeapon类的状态是“按下捡拾键”			

			_lastPickTime = currentTime;
			auto temp = *i;
			if ((_currentUsedWeapon == _weapon1 && _weapon2!=nullptr)||
				(_currentUsedWeapon == _weapon2 && _weapon1!=nullptr)) {
				transferWeaponToPickWeapon(_currentUsedWeapon, _hero);//根据持有武器添加PickWeapon，添加入PickWeapon库
			}
			transferPickWeaponToWeapon(temp, _hero);//根据i的种类添加武器,并添加入武器库
			
			temp->initPickWeaponState();

			auto oldpick = _pickableWeaponVec.find(temp);
			(*oldpick)->stopPickWeapon(true);
			oldpick = _pickableWeaponVec.erase(oldpick);

			break;
		}
		i++;
	}
}



Character* HelloWorld::addCharacter(TMXTiledMap* map, int HeroID) {
	Character* m_Character = Character::create();
	switch (HeroID)
	{
	case 1:
		m_Character = Knight::create();
		break;
	default:

		break;
	}


	this->addChild(m_Character);
	ControllerOfEightDir* m_controller = ControllerOfEightDir::create();
	m_Character->setController(m_controller);
	m_controller->setiSpeed(m_Character->getSpeed());
	this->addChild(m_controller);




	m_Character->setTiledMap(map);

	TMXObjectGroup* objGroup = map->getObjectGroup("Object");

	ValueMap characterPointMap = objGroup->getObject("CharacterPoint");
	float characterPointX = characterPointMap.at("x").asFloat();
	float characterPointY = characterPointMap.at("y").asFloat();

	m_Character->setPosition(Point(characterPointX, characterPointY));//根据tmx对象确定出生点
	m_Character->setViewPointByCharacter();

	return m_Character;
}





void HelloWorld::transferPickWeaponToWeapon(PickWeapon* pickWeapon, Character* hero) {

	auto name = pickWeapon->getImageName();


	_currentUsedWeapon->stopWeapon(true);
	
	int currentWeaponID = (_currentUsedWeapon == _weapon1) ? 1 : 2;

	Weapon* tempWeapon;

	if (name == GUN_OLDPISTOL) {
		auto oldPistol = OldPistol::create
		("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
		this->addChild(oldPistol);
		oldPistol->startWeapon(true);
		oldPistol->setPosition(hero->getPosition());
		oldPistol->setTiledMap(_map);
		oldPistol->setOwner(_hero);
		
		tempWeapon = oldPistol;
	}
	else if (name == GUN_SMG) {
		auto smg = SMG::create
		("GunImage\\SMG.png", "GunImage\\SMGReverse.png", this, sideHero, true);
		this->addChild(smg);
		smg->startWeapon(true);
		smg->setPosition(hero->getPosition());
		smg->setTiledMap(_map);
		smg->setOwner(_hero);
		

		tempWeapon = smg;
		
	}
	else if (name == GUN_SHOTGUN) {
		auto stgun = Shotgun::create
		("GunImage\\Shotgun.png", "GunImage\\ShotgunReverse.png", this, sideHero, true);
		this->addChild(stgun);
		stgun->startWeapon(true);
		stgun->setPosition(hero->getPosition());
		stgun->setTiledMap(_map);
		stgun->setOwner(_hero);
		
		tempWeapon = stgun;
	}
	else if (name == GUN_SNIPER) {
		auto hecateII = Sniper::create
		("GunImage\\Sniper.png", "GunImage\\SniperReverse.png", this, sideHero, true);
		this->addChild(hecateII);
		hecateII->startWeapon(true);
		hecateII->setPosition(hero->getPosition());
		hecateII->setTiledMap(_map);
		hecateII->setOwner(_hero);

		tempWeapon = hecateII;
		
	}
	else if (name == MELEE_FISH) {
		auto fish = Fish::create
		("MeleeImage\\Fish.png", "MeleeImage\\FishReverse.png", this, sideHero, true);
		this->addChild(fish);
		fish->startWeapon(true);
		fish->setPosition(hero->getPosition());
		fish->setTiledMap(_map);
		fish->setOwner(_hero);
		
		
		tempWeapon = fish;
	}

	else {
		
		return;
	}

	if (currentWeaponID == 1) {
		if (!_weapon2) {
			_weapon2 = tempWeapon;
			_currentUsedWeapon = tempWeapon;
		}
		else {
			_weapon1 = tempWeapon;
			_currentUsedWeapon = tempWeapon;
		}
	}
	//TODO:内存池优化
	if (currentWeaponID == 2) {
		if (!_weapon1) {
			_weapon1 = tempWeapon;
			_currentUsedWeapon = tempWeapon;
		}
		else {
			_weapon2 = tempWeapon;
			_currentUsedWeapon = tempWeapon;
		}
	}

}





void HelloWorld::transferWeaponToPickWeapon(Weapon* weapon, Character* hero) {

	auto name =weapon->getImageName();
	auto typeName = weapon->getTypeName();
	
	auto pickWeapon = PickWeapon::create
		(Vec2(hero->getPositionX() + 50, hero->getPositionY()), hero, this, typeName,name, _rocker);

	this->addChild(pickWeapon);
	pickWeapon->initPickWeaponState();
	_pickableWeaponVec.pushBack(pickWeapon);


}

void HelloWorld::updateTreasureBoxVec() {
	

	//更新场景中可捡起物体
	for (auto i = _treasureBoxVec.begin(); i != _treasureBoxVec.end();) {

		(*i)->updateTreasureBoxState();

		if ((*i)->isUnUsed()&&(*i)->objectIsPressed()) {		
			(*i)->generateRandomObject();
			
		}
		i++;
	}
}

void HelloWorld::updatePickBottleVec() {
	for (auto i = _pickableBottleVec.begin(); i != _pickableBottleVec.end();) {

		(*i)->updatePickBottleState();

		if ((*i)->objectIsPressed()) {
			(*i)->addPoint();
			(*i)->stopPickBottle();
			i = _pickableBottleVec.erase(i);
		}
		else
			i++;
	}
}