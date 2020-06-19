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

//std::vector<std::string> exitRightMaps;
//std::vector<std::string> exitLeftMaps;
//std::vector<std::string> exitUpMaps;
//std::vector<std::string> exitDownMaps;
//std::vector<std::string>  corridors;


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
	
	_map = TMXTiledMap::create(StringUtils::format("Maps/HelloWorldMap%s.tmx", levelOrder));
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

	Vector<AccelerateArea*> _accelerateAreaVec;



	initHRocker();

	safeHouseInit();

	pauseBtn = Sprite::create("Pause/pauseButton.png");
	pauseBtn->setPosition(_hero->getPositionX() + 380, _hero->getPositionY() + 220);
	pauseBtn->setAnchorPoint(Vec2(0, 0));
	pauseBtn->setTag(50);
	pauseBtn->setScale(0.2);
	this->addChild(pauseBtn, 10);

	Point positionSp = pauseBtn->getPosition();
	/*log("%f,%f", positionSp.x, positionSp.y);*/
	Size sizeC = pauseBtn->getContentSize();
	log("%f,%f", sizeC.width, sizeC.height);

	/*auto rc = Rect(positionSp.x, positionSp.y, sizeC.width, sizeC.height);*/

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = ([&, sizeC](Touch* t, Event* e) {
		/*log("began");*/
		auto node = (Sprite*)this->getChildByTag(50);
		auto pauseB = HelloWorld::getPauseBtn();
		/*log("%f %f", node->getPositionX(), node->getPositionY());
		log("%f %f", pauseB->getPositionX(), node->getPositionY());*/


		auto touchLocation = t->getLocation();
		auto rc = Rect(node->getPositionX(), node->getPositionY(), sizeC.width, sizeC.height);
		Point localPos = convertToNodeSpace(touchLocation);
		bool isTouched = rc.containsPoint(localPos);
		if (isTouched)
		{
			auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
			audio->playEffect("Audio/button.mp3", false);
			node->setScale(0.16);
		}
		return true; });
	listener->onTouchEnded = ([&, sizeC](Touch* t, Event* e) {
		/*log("end");*/
		auto node = (Sprite*)this->getChildByTag(50);
		auto touchLocation = t->getLocation();
		auto rc = Rect(node->getPositionX(), node->getPositionY(), sizeC.width, sizeC.height);
		Point localPos = convertToNodeSpace(touchLocation);
		bool isTouched = rc.containsPoint(localPos);
		if (isTouched)
		{
			node->setScale(0.2);
			Director::getInstance()->pause();

			CCRenderTexture* renderTexture = CCRenderTexture::create(960, 640);

			renderTexture->begin();
			node->getParent()->visit();
			renderTexture->end();

			Director::getInstance()->pushScene(PauseLayer::createScene(renderTexture));
		}
		});
	listener->onTouchMoved = ([&](Touch* t, Event* e) {/*log("move");*/ });

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pauseBtn);

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

//////////////////////////////////////////////////////////////////////////////////////////////////

//bool HelloWorld::init()
//{
//	if (!Scene::init())
//	{
//		return false;
//	}
//
//	_mapOrder = 0;
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//	appliedSpace = *(new std::vector<Space*>);
//	placement = *(new std::vector<std::vector<int>>(5, std::vector<int>(5, EMPTY)));
//	roomCount = 0;
//	typeNum = *(new std::vector<int>(5));
//	
//
//	initMaps();
//	_knight = addCharacter(appliedSpace[0]->getMap(), 1);
//	this->addChild(_knight, 1);
//	_knight->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
//
//	_parent = _knight->getParent();
//
//	this->scheduleUpdate();
//	//listenerTouch = EventListenerTouchOneByOne::create();
//	//listenerTouch->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//	listenerKeyBoard = EventListenerKeyboard::create();
//	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
//	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
//
//	return true;
//}
//
//void HelloWorld::addCharacter(Character* hero, TMXTiledMap* map) {
//	
//	hero->setTiledMap(map);
//
//	hero->setViewPointByCharacter();
//
//	
//}
//
//void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
//
//{
//	//判断 keyCode 枚举来区分所按下的按键
//	switch (keyCode) {
//	case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW):
//	{
//		//for (int j = 0; j < appliedSpace.size(); j++)
//		{
//			auto map = appliedSpace[0]->getMap();
//			map->setPosition(map->getPosition() + Vec2(-200, 0));
//		}
//		break;
//	}
//	case (EventKeyboard::KeyCode::KEY_UP_ARROW):
//	{
//		//for (int j = 0; j < appliedSpace.size(); j++)
//		{
//			auto map = appliedSpace[0]->getMap();
//			map->setPosition(map->getPosition() + Vec2(0, -200));
//		}
//		break;
//	}
//	case (EventKeyboard::KeyCode::KEY_LEFT_ARROW):
//	{
//		//for (int j = 0; j < appliedSpace.size(); j++)
//		{
//			auto map = appliedSpace[0]->getMap();
//			map->setPosition(map->getPosition() + Vec2(200, 0));
//		}
//		break;
//	}
//	case (EventKeyboard::KeyCode::KEY_DOWN_ARROW):
//	{
//		//for (int j = 0; j < appliedSpace.size(); j++)
//		{
//			auto map = appliedSpace[0]->getMap();
//			map->setPosition(map->getPosition() + Vec2(0, 200));
//		}
//		break;
//	}
//	}
//
//}
//
//
//
//void HelloWorld::update(float delta) {
//
//	updateMap();//更新地图
//
//}
//
//
//void HelloWorld::findCurMap(Character* player)//找到主角当前地图
//{
//	CCTMXTiledMap* map = curMap;
//	auto playerWorldPos = (player->getParent())->convertToWorldSpace(player->getPosition());	
//	for (int i = 0; i < appliedSpace.size(); i++)
//	{
//		if (appliedSpace[i]->isInBound(playerWorldPos))
//		{
//			map = appliedSpace[i]->getMap();
//						
//		}
//		
//	}
//	
//	if (map == curMap) {
//		return;
//	}
//	else if (map != nullptr)
//	{
//		curMap = map;
//		auto playerLocalPos = map->convertToNodeSpace(playerWorldPos);
//		player->setPosition(playerLocalPos);
//		player->setParent(NULL);
//		map->addChild(player);
//
//		addCharacter(player, map);
//		log("Map changes!");
//		
//	}
//
//}
//
//void HelloWorld::updateMap()
//{
//	findCurMap(_knight);
//}
//
//bool HelloWorld::initMaps()
//{
//	//std::string startRoom = "StartRoom.tmx";
//	std::string verticalCorridor = "VerticalCorridor.tmx";
//	std::string horizontalCorridor = "HorizontalCorridor.tmx";
//	//std::string monsterRoom4Exits = "MonsterRoom4Exits.tmx";
//	exitDownMaps = { "D1.tmx","D1.tmx","D1.tmx","DR.tmx","UD.tmx","DL.tmx","UDL.tmx","DLR.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
//	exitRightMaps = { "R1.tmx","R1.tmx","R1.tmx","DR.tmx","UR.tmx","LR.tmx","ULR.tmx","DLR.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
//	exitUpMaps = { "U1.tmx","U1.tmx","U1.tmx","UD.tmx","UR.tmx","UL.tmx","ULR.tmx","UDL.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
//	exitLeftMaps = { "L1.tmx","L1.tmx","L1.tmx","DL.tmx","LR.tmx","UL.tmx","ULR.tmx","UDL.tmx","DLR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
//	corridors = { verticalCorridor,horizontalCorridor };
//	auto firstRoom = Space::create(this);
//	if (firstRoom != nullptr)
//	{
//		auto firstMap = firstRoom->getMap();
//		//auto firstMap = CCTMXTiledMap::create(squareRoom);
//		if (firstMap != nullptr)
//		{
//			this->addChild(firstMap, 0);
//			placement[0][2] = FULL;
//			auto visibleSize = Director::getInstance()->getVisibleSize();
//			Vec2 origin = Director::getInstance()->getVisibleOrigin();
//			firstMap->setAnchorPoint(Vec2(0.57142, 0.57142));//0.5 0.5
//			firstMap->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y));
//			auto mapSize = firstMap->getMapSize();
//			auto tileSize = firstMap->getTileSize();
//			//firstMap->setPosition(Vec2(origin.x+20, visibleSize.height/2+ origin.y));
//			auto curAnc = firstMap->getAnchorPoint();
//			auto curPos = firstMap->getPosition();
//			firstRoom->resetAnchor(Vec2(0.57142, 0.57142));//0.5 0.5
//			firstRoom->setCover(Rect(firstMap->getPosition(), Size(mapSize.width * tileSize.width/* / 2.0915*/, mapSize.height * tileSize.height/* / 2.0915*/)));
//			this->curMap = firstMap;
//			this->appliedSpace.push_back(firstRoom);
//			typeNum[1]++;
//			roomCount++;
//		}
//		else
//		{
//			log("Map access failed!");
//			return false;
//		}
//	}
//	else
//	{
//		log("Room building failed!");
//		return false;
//	}
//	while (roomCount < 9)
//	{
//		for (int j = 0; j < appliedSpace.size(); j++)
//		{
//			appliedSpace[j]->getCover();
//			for (int i = 1; i <= 4; i++)
//			{
//				if (i > 4)
//				{
//					log("exitInfo out of range.");
//				}
//				else
//				{
//					if (appliedSpace[j] != nullptr && appliedSpace[j]->exitInfo[i] == E_UNAPPENDED)//存在出口未延伸
//					{
//						Space* temp = appliedSpace[j]->append(this, i);
//						if (temp != nullptr)
//						{
//							temp->count = appliedSpace.size();
//							this->appliedSpace.push_back(temp);
//							appliedSpace[j]->exitInfo[i] = E_APPENDED;
//							int otherExit = i > 2 ? i - 2 : i + 2;
//							appliedSpace[appliedSpace.size() - 1]->exitInfo[otherExit] = E_APPENDED;
//						}
//					}
//				}
//			}
//		}
//	}
//
//}
//
//bool HelloWorld::roomNotFull(int type)
//{
//	switch (type)
//	{
//	case(1):
//		return true;
//		//return typeNum[type] < 5 ? true : false;
//	case(2):
//		return typeNum[type] < 4 ? true : false;
//	case(3):
//		return typeNum[type] < 2 ? true : false;
//	case(4):
//		return typeNum[type] < 2 ? true : false;
//	default:
//		return false;
//	}
//}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool HelloWorld::init(int order, HeroInfo heroInfo) {
	if (!Scene::init())	return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();


	_mapOrder = order;
	std::string levelOrder = StringUtils::format("%d", order);
	_map = TMXTiledMap::create(StringUtils::format("Maps/HelloWorldMap%s.tmx", levelOrder));

	if(_mapOrder==1)
	_map->setPosition(_map->getPositionX() , _map->getPositionY() + 40);
	if (_mapOrder == 2)
		_map->setPosition(_map->getPositionX(), _map->getPositionY()+80);

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
		("WeaponImage\\GunImage\\OldPistol.png", "WeaponImage\\GunImage\\OldPistolReverse.png", this, sideHero, true);
		this->addChild(initWeapon);
		initWeapon->startWeapon(true);
		initWeapon->setTiledMap(_map);
		initWeapon->setOwner(_hero);
		_currentUsedWeapon = initWeapon;
		_weapon1 = _currentUsedWeapon;
		_weapon2 = nullptr;
	}

	initHRocker();

	BattleHouseInit();


	//auto monster = Ranger::create();
	//monster->setPosition(Vec2(_hero->getPositionX(), _hero->getPositionY() - 290));
	//this->addChild(monster);
	//_currentEnemy.pushBack(monster);
	//auto treasureBox = TreasureBox::create
	//(Vec2(_hero->getPositionX(), _hero->getPositionY() - 180), _hero, this, _rocker);
	//this->addChild(treasureBox);
	//_treasureBoxVec.pushBack(treasureBox);
	//_portal = TransferPortal::create
	//(Vec2(_hero->getPositionX(), _hero->getPositionY() + 180), _hero, this, _rocker);
	//this->addChild(_portal);

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

	if (_mapOrder == 2) this->menuWinCallBack(this);
	else {
		clear();
		auto nextScene = HelloWorld::createScene(_mapOrder + 1, heroinfo);

		Director::getInstance()->pushScene(
			TransitionSlideInT::create(1.0f / 60, nextScene));
		MenuItem* item = (MenuItem*)pSender;
	}

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




	_portal = TransferPortal::create
	(Vec2(_hero->getPositionX(), _hero->getPositionY() + 180), _hero, this, _rocker);
	this->addChild(_portal);

	auto manager = MonsterManager::create(Vec2(_hero->getPositionX(), _hero->getPositionY() - 200),this,_hero);
	manager->setTiledMap(_map);
	this->addChild(manager);
	_monsterManageerVec.pushBack(manager);



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
		_currentUsedWeapon->clearBuff();
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

	auto node = (Sprite*)this->getChildByTag(50);
	node->setPosition(_hero->getPositionX() + 380, _hero->getPositionY() + 220);

	for (auto& j : _monsterManageerVec) j->update(1);


	for (auto& j : _currentEnemy) {
		j->update(1);
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
	/*updateBuffSkills();*/


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

bool HelloWorld::BattleHouseInit() {
	if (!_map) { log("ERROR:Map Missing"); return false; }
	TMXObjectGroup* objGroup = _map->getObjectGroup("Object");

	//宝箱位置
	ValueMap TreasureBoxPointMap = objGroup->getObject("Treasure");
	float trePointX = TreasureBoxPointMap.at("x").asFloat();
	float trePointY = TreasureBoxPointMap.at("y").asFloat();
	auto treasureBox = TreasureBox::create
	(Vec2(trePointX, trePointY), _hero, this, _rocker);
	this->addChild(treasureBox);
	_treasureBoxVec.pushBack(treasureBox);


	////传送门位置
	TMXObjectGroup* objGroup2 = _map->getObjectGroup("Object");
	ValueMap PortalPointMap = objGroup2->getObject("Portal");
	float portalPointX = PortalPointMap.at("x").asFloat();
	float portalPointY = PortalPointMap.at("y").asFloat();
	_portal = TransferPortal::create
	(Vec2(portalPointX, portalPointY), _hero, this, _rocker);
	this->addChild(_portal);

	for (int i = 1; i < 5; i++) {
		TMXObjectGroup* objGroup3 = _map->getObjectGroup("Object");
		std::string number = StringUtils::format("%d", i);
		ValueMap SpeedUpPointMap = objGroup3->getObject(StringUtils::format("Speed%s", number));
		float acPointX = SpeedUpPointMap.at("x").asFloat();
		float acPointY = SpeedUpPointMap.at("y").asFloat();
		auto accelerateArea = AccelerateArea::create
		(Vec2(acPointX, acPointY), _hero, this);
		this->addChild(accelerateArea);
		_accelerateAreaVec.pushBack(accelerateArea);
	}

	TMXObjectGroup* objGroup4 = _map->getObjectGroup("Object");
	ValueMap ManagerMap = objGroup2->getObject("Manager");
	float PointX = ManagerMap.at("x").asFloat();
	float PointY = ManagerMap.at("y").asFloat();
	auto manager = MonsterManager::create(Vec2(PointX,PointY), this, _hero);
	manager->setTiledMap(_map);
	this->addChild(manager);
	_monsterManageerVec.pushBack(manager);
	return true;
}


//加载ui
/*
bool HelloWorld::loadUI(const char* file) {
	auto UI = cocostudio::GUIReader::getInstance()->
		widgetFromJsonFile(file);
	UI->setPosition(Point(100, 100));
	this->addChild(UI);
	return true;
}*/