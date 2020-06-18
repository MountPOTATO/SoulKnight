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
#include <cstdlib>
#include "Const/ConstInfo.h"
#include "Scene/StartScene.h"
#include "Scene/LoseScene.h"
#include "Scene/WinScene.h"

USING_NS_CC;



Scene* HelloWorld::createScene(int order, HeroInfo heroinfo)
{
	HelloWorld* helloWorld = new(std::nothrow)HelloWorld;
	if (helloWorld && helloWorld->init(order, heroinfo)) {
		helloWorld->autorelease();
		return helloWorld;
	}
	CC_SAFE_DELETE(helloWorld);


}

Scene* HelloWorld::createScene() {
	auto helloWorld = HelloWorld::create();
	return helloWorld;
}


float MyGetRad(Point point1, Point point2);



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Scene::init())
	{
		return false;
	}

	_mapOrder = 0;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	std::string levelOrder = StringUtils::format("%d", _mapOrder);
	_map = TMXTiledMap::create("Maps/HelloWorldMap0.tmx");
	this->addChild(_map);
	//初始化英雄
	_hero = addCharacter(_map, 1);
	auto initWeapon = OldPistol::create
	("WeaponImage\\GunImage\\OldPistol.png", "WeaponImage\\GunImage\\OldPistolReverse.png", this, sideHero, true);
	this->addChild(initWeapon);
	initWeapon->startWeapon(true);
	initWeapon->setTiledMap(_map);
	initWeapon->setOwner(_hero);
	_currentUsedWeapon = initWeapon;
	_weapon1 = _currentUsedWeapon;
	_weapon2 = nullptr;




	initHRocker();

	safeHouseInit();


	//测试掉落物直接减起,后期加入Vector
	/*_direct = DirectPickThing::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 250), _hero, 20.f, 3, 3, 5, this);
	this->addChild(_direct);*/

	//加载ui
	//this->loadUI
	//("Resources\\DemoHead_UI\\DemoHead_UI.ExportJson");

	this->scheduleUpdate();
	return true;
}



bool HelloWorld::init(int order, HeroInfo heroInfo) {
	if (!Scene::init())	return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_mapOrder = order;
	std::string levelOrder = StringUtils::format("%d", order);
	_map = TMXTiledMap::create(StringUtils::format("Maps/HelloWorldMap%s.tmx", levelOrder));
	this->addChild(_map);

	_hero = addCharacter(_map, 1);

	if (heroInfo.wp1 || heroInfo.wp2) {
		_hero->setHP(heroInfo.hp);
		_hero->setMP(heroInfo.mp);
		_hero->setArmor(heroInfo.armor);

		resetWeapon(heroInfo);


	}
	else {
		auto initWeapon = OldPistol::create
		("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
		this->addChild(initWeapon);
		initWeapon->startWeapon(true);
		initWeapon->setTiledMap(_map);
		initWeapon->setOwner(_hero);
		_currentUsedWeapon = initWeapon;
		_weapon1 = _currentUsedWeapon;
		_weapon2 = nullptr;
	}

	auto monster = Ranger::create();
	monster->setPosition(Vec2(_hero->getPositionX(), _hero->getPositionY() - 290));
	this->addChild(monster);
	_currentEnemy.pushBack(monster);

	initHRocker();


	auto treasureBox = TreasureBox::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 180), _hero, this, _rocker);
	this->addChild(treasureBox);
	_treasureBoxVec.pushBack(treasureBox);


	_portal = TransferPortal::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() + 180), _hero, this, _rocker);
	this->addChild(_portal);

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

void HelloWorld::menuReGenerateCallBack(Ref* pSender) {

	HeroInfo heroinfo = { _hero->getHP(),_hero->getMP(),_hero->getArmor(),_weapon1,_weapon2,_currentUsedWeapon };

	auto nextScene = HelloWorld::createScene(0, heroinfo);

	Director::getInstance()->pushScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;

}

void HelloWorld::menuLoseCallBack(Ref* pSender) {
	auto nextScene = LoseScene::createScene();

	Director::getInstance()->pushScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;
}

void HelloWorld::menuWinCallBack(Ref* pSender) {
	auto nextScene = WinScene::createScene();

	Director::getInstance()->pushScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;
}

bool HelloWorld::safeHouseInit() {
	//在安全房的init
	auto treasureBox = TreasureBox::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 180), _hero, this, _rocker);
	this->addChild(treasureBox);
	_treasureBoxVec.pushBack(treasureBox);


	//accelerateDemo
	auto accelerateArea1 = AccelerateArea::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() - 300), _hero, this);
	this->addChild(accelerateArea1);
	_accelerateAreaVec.pushBack(accelerateArea1);

	auto accelerateArea2 = AccelerateArea::create
	(Vec2(_hero->getPositionX() + 300, _hero->getPositionY() - 300), _hero, this);
	this->addChild(accelerateArea2);
	_accelerateAreaVec.pushBack(accelerateArea2);

	_portal = TransferPortal::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() + 180), _hero, this, _rocker);
	this->addChild(_portal);

	auto monster = Ranger::create();
	monster->setPosition(Vec2(_hero->getPositionX(), _hero->getPositionY() - 290));
	this->addChild(monster);
	_currentEnemy.pushBack(monster);

	return true;
}



void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	this->addChild(_rocker);
	_rocker->startRocker(true);

}


void HelloWorld::checkPortalState() {
	if (!_portal) return;
	_portal->updatePortalState();
	if (_portal->objectIsPressed() && _portal->isUnUsed()) {

		_portal->initProtalState();
		_portal->setPortalAsUsed();
		this->clear();
		this->menuReGenerateCallBack(this);

	}
}



void HelloWorld::clear() {
	_bullets.clear();
	_currentEnemy.clear();
	_enemyBullet.clear();
	_pickableWeaponVec.clear();
	_pickableBottleVec.clear();
	_treasureBoxVec.clear();
	_energyVec.clear();
	_coinVec.clear();
	_accelerateAreaVec.clear();
}


void HelloWorld::update(float delta) {

	checkPortalState();

	_rocker->updatePosition(Vec2(_hero->getPositionX() - 550, _hero->getPositionY() - 350));




	for (auto j : _currentEnemy) {
		if (_hero->getBoundingBox().intersectsRect(j->getBoundingBox()))
			_hero->hit(1, j->getPosition());
	}


	for (auto& j : _currentEnemy) {
		auto currentTime = GetCurrentTime() / 1000.f;

		if (currentTime - _firetime < SWITCH_TIMESPACE) break;
		_firetime = currentTime;
		Bullet* bullet = Bullet::create("BulletImage\\SMGBullet.png", 400, j, MyGetRad(j->getPosition(), _hero->getPosition()));
		if (bullet) {
			bullet->setScale(1.8);
			bullet->setTiledMap(this->_map);
			this->addChild(bullet);
			_enemyBullet.pushBack(bullet);
		}
	}


	//更新掉落物
	//_direct->updatePickThingSprite();



	updateTreasureBoxVec();
	updatePickBottleVec();
	updateWeaponHolding();
	updatePickWeaponAndWeapon();
	updateAccelerateArea();



	_currentUsedWeapon->updateTarget();
	_currentUsedWeapon->updateImageRotation(_rocker);
	_currentUsedWeapon->updateCurrentLocation();
	_currentUsedWeapon->attack();//攻击，发射子弹

	updateBullet();//更新飞行物

}

void HelloWorld::updateBullet() {
	//对我方子弹进行遍历
	for (auto i = _bullets.begin(); i != _bullets.end(); ) {
		bool temp = true;
		(*i)->setVisible(true);
		(*i)->calPosition();//更新位置信息
		if ((*i)->isPosBlocked((*i)->getPosition())) {//被障碍物格挡，消除
			(*i)->stopBullet();
			i = _bullets.erase(i);
			temp = false;
		}
		else for (auto& enmy : _currentEnemy) {//打中怪物 扣血消除
			if (enmy->getBoundingBox().intersectsRect((*i)->getBoundingBox())) {
				enmy->setHP(enmy->getHP() - (*i)->getBulletAttack());
				//飘字

				auto flowword = FlowWord::create();
				this->addChild(flowword);
				const char* damage = StringUtils::format("%d", -(*i)->getBulletAttack()).data();
				flowword->showWord(damage, Vec2(enmy->getPositionX(), enmy->getPositionY() + 10));

				(*i)->stopBullet();
				i = _bullets.erase(i);
				temp = false;
			}
		}
		if (temp) i++;
	}
	//对敌方子弹遍历
	for (auto k = _enemyBullet.begin(); k != _enemyBullet.end(); ) {
		bool temp = true;
		(*k)->setVisible(true);
		(*k)->calPosition();//位置信息更新
		if ((*k)->isPosBlocked((*k)->getPosition())) {//被障碍物格挡，消除
			(*k)->stopBullet();
			k = _enemyBullet.erase(k);
			temp = false;
		}
		//打中主角 击退 消除
		else if (_hero->getBoundingBox().intersectsRect((*k)->getBoundingBox())) {
			if (!_hero->isInvincible) {
				_hero->hit((*k)->getBulletAttack(), (*k)->getPosition());

				auto flowword = FlowWord::create();
				this->addChild(flowword);
				const char* damage = StringUtils::format("%d", -(*k)->getBulletAttack()).data();
				flowword->showWord(damage, Vec2(_hero->getPositionX(), _hero->getPositionY() + 10));
				
				(*k)->stopBullet();
				k = _enemyBullet.erase(k);
				temp = false;
			}
		}
		if (temp) k++;
	}
}


void HelloWorld::updateWeaponHolding() {
	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastSwitchTime < SWITCH_TIMESPACE) { return; }

	if (_rocker->isPressSwitch()) {
		if (_currentUsedWeapon == _weapon1 && _weapon2) {
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
			if ((_currentUsedWeapon == _weapon1 && _weapon2 != nullptr) ||
				(_currentUsedWeapon == _weapon2 && _weapon1 != nullptr)) {
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
	this->addChild(m_controller, 0, CONTROLLER_TAG);

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
	else if (name == MELEE_WAND) {
		auto wand = Wand::create
		("MeleeImage\\Wand.png", "MeleeImage\\Wand.png", this, sideHero, true);
		this->addChild(wand);

		wand->startWeapon(true);
		wand->setPosition(hero->getPosition());
		wand->setTiledMap(_map);
		wand->setOwner(_hero);


		tempWeapon = wand;
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

	auto name = weapon->getImageName();
	auto typeName = weapon->getTypeName();

	auto pickWeapon = PickWeapon::create
	(Vec2(hero->getPositionX() + 50, hero->getPositionY()), hero, this, typeName, name, _rocker);

	this->addChild(pickWeapon);
	pickWeapon->initPickWeaponState();
	_pickableWeaponVec.pushBack(pickWeapon);


}

void HelloWorld::updateTreasureBoxVec() {


	//更新场景中可捡起物体
	for (auto i = _treasureBoxVec.begin(); i != _treasureBoxVec.end();) {

		(*i)->updateTreasureBoxState();

		if ((*i)->isUnUsed() && (*i)->objectIsPressed()) {
			(*i)->generateRandomObject();

		}
		i++;
	}
}


void HelloWorld::updateAccelerateArea()
{
	if (_accelerateAreaVec.size() == 0) return;
	bool doHasCollied = 0;
	clock_t initTime = startTime;
	endTime = clock();
	for (auto i = _accelerateAreaVec.begin(); i != _accelerateAreaVec.end(); i++)
	{
		(*i)->setPositionZ(_hero->getPositionZ() - 18);
		(*i)->updateAccelerateArea();

		if ((*i)->isColliedJudge())
		{
			startTime = clock();
			(*i)->accelerateHeroSpeed(this);
			(*i)->setIsCollied(false);
			doHasCollied = true;
		}
	}
	double finalTime = (double)(endTime - initTime) / CLOCKS_PER_SEC;
	if (finalTime >= ACCELERATE_TIME && (!doHasCollied))
	{
		(*(_accelerateAreaVec.begin()))->resetHeroSpeed(this);
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


float MyGetRad(Point point1, Point point2) {
	//获得两点x,y距离
	float xd = point2.x - point1.x;
	float yd = point1.y - point2.y;
	//斜边长度计算
	float hypo = sqrt(pow(xd, 2) + pow(yd, 2));
	//获得余弦值
	float cos = xd / hypo;
	//获得rad
	float rad = acos(cos);
	//取反ss
	if (yd > 0) {
		rad = -rad;
	}
	return rad;
}


void HelloWorld::resetWeapon(HeroInfo heroInfo) {

	if (heroInfo.wp1) {
		if (heroInfo.wp1->getTypeName() == GUN && heroInfo.wp1->getImageName() == GUN_OLDPISTOL)
			_weapon1 = OldPistol::create("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
		if (heroInfo.wp1->getTypeName() == GUN && heroInfo.wp1->getImageName() == GUN_SHOTGUN)
			_weapon1 = Shotgun::create("GunImage\\Shotgun.png", "GunImage\\ShotgunReverse.png", this, sideHero, true);
		if (heroInfo.wp1->getTypeName() == GUN && heroInfo.wp1->getImageName() == GUN_SMG)
			_weapon1 = SMG::create("GunImage\\SMG.png", "GunImage\\SMGReverse.png", this, sideHero, true);
		if (heroInfo.wp1->getTypeName() == GUN && heroInfo.wp1->getImageName() == GUN_SNIPER)
			_weapon1 = Sniper::create("GunImage\\Sniper.png", "GunImage\\SniperReverse.png", this, sideHero, true);
		if (heroInfo.wp1->getTypeName() == MELEE && heroInfo.wp1->getImageName() == MELEE_FISH)
			_weapon1 = Fish::create("MeleeImage\\Fish.png", "MeleeImage\\FishReverse.png", this, sideHero, true);
		if (heroInfo.wp1->getTypeName() == MELEE && heroInfo.wp1->getImageName() == MELEE_WAND)
			_weapon1 = Wand::create("MeleeImage\\Wand.png", "MeleeImage\\Wand.png", this, sideHero, true);

		this->addChild(_weapon1);
		_weapon1->setTiledMap(_map);
		_weapon1->setOwner(_hero);
	}
	else _weapon1 = nullptr;
	if (heroInfo.wp2) {
		if (heroInfo.wp2->getTypeName() == GUN && heroInfo.wp2->getImageName() == GUN_OLDPISTOL)
			_weapon2 = OldPistol::create("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
		if (heroInfo.wp2->getTypeName() == GUN && heroInfo.wp2->getImageName() == GUN_SHOTGUN)
			_weapon2 = Shotgun::create("GunImage\\Shotgun.png", "GunImage\\ShotgunReverse.png", this, sideHero, true);
		if (heroInfo.wp2->getTypeName() == GUN && heroInfo.wp2->getImageName() == GUN_SMG)
			_weapon2 = SMG::create("GunImage\\SMG.png", "GunImage\\SMGReverse.png", this, sideHero, true);
		if (heroInfo.wp2->getTypeName() == GUN && heroInfo.wp2->getImageName() == GUN_SNIPER)
			_weapon2 = Sniper::create("GunImage\\Sniper.png", "GunImage\\SniperReverse.png", this, sideHero, true);
		if (heroInfo.wp2->getTypeName() == MELEE && heroInfo.wp2->getImageName() == MELEE_FISH)
			_weapon2 = Fish::create("MeleeImage\\Fish.png", "MeleeImage\\FishReverse.png", this, sideHero, true);
		if (heroInfo.wp2->getTypeName() == MELEE && heroInfo.wp2->getImageName() == MELEE_WAND)
			_weapon2 = Wand::create("MeleeImage\\Wand.png", "MeleeImage\\Wand.png", this, sideHero, true);

		this->addChild(_weapon2);
		_weapon2->setTiledMap(_map);
		_weapon2->setOwner(_hero);
	}
	else _weapon2 = nullptr;

	if (heroInfo.curwp == heroInfo.wp1) this->_currentUsedWeapon = this->_weapon1;
	else if (heroInfo.curwp == heroInfo.wp2) this->_currentUsedWeapon = this->_weapon2;
	_currentUsedWeapon->startWeapon(true);

}

