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

 std::vector<std::string> exitRightMaps;
 std::vector<std::string> exitLeftMaps;
 std::vector<std::string> exitUpMaps;
 std::vector<std::string> exitDownMaps;
 std::vector<std::string>  corridors;


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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//test Entity can delete
	
	//initHRocker();

	//此处修改,初始化一样武器实例,以SMG冲锋枪为例
	/*test_InitFish();*/
	/*test_InitPistol();*/

	//test_InitShotgun();

	//测试自动瞄准时加上，不需要测试时去掉,同时在update函数中添加相应的模块
	/*Entity* testEnermy=new Entity();
	Sprite* enermyImage = Sprite::create("HelloWorld.png");
	testEnermy->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 300);
	testEnermy->bindSprite(enermyImage);
	this->addChild(testEnermy);
	_currentUnit.pushBack(testEnermy);*/


	//测试地图和角色
	//先放人物再放武器
	appliedSpace = *(new std::vector<Space*>);
	placement = *(new std::vector<std::vector<int>>(5,std::vector<int>(5,EMPTY)));
	roomCount = 0;
	typeNum =*(new std::vector<int>(5));
	knight = Sprite::create("Knight.png");
	this->addChild(knight, 1);
	knight->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//typeNum = { 0 };
	initMaps();
	//auto map = appliedSpace[0];
	//auto knight=addCharacter(map,1);

	//test_InitShotgun();
	//_testShotgun->setTiledMap(map);
	//_testShotgun->setOwner(knight);


	this->scheduleUpdate();
	//listenerTouch = EventListenerTouchOneByOne::create();
	//listenerTouch->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listenerKeyBoard= EventListenerKeyboard::create();
	listenerKeyBoard->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyBoard, this);
	//这里和下面的键盘监听是测试地图用的

    return true;
}


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)

{
	//判断 keyCode 枚举来区分所按下的按键
	switch (keyCode) {
	case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW):
	{
		//for (int j = 0; j < appliedSpace.size(); j++)
		{
			auto map = appliedSpace[0]->getMap();
			map->setPosition(map->getPosition() + Vec2(-200, 0));
		}
		break;
	}
	case (EventKeyboard::KeyCode::KEY_UP_ARROW):
	{
		//for (int j = 0; j < appliedSpace.size(); j++)
		{
			auto map = appliedSpace[0]->getMap();
			map->setPosition(map->getPosition() + Vec2(0, -200));
		}
		break;
	}
	case (EventKeyboard::KeyCode::KEY_LEFT_ARROW):
	{
		//for (int j = 0; j < appliedSpace.size(); j++)
		{
			auto map = appliedSpace[0]->getMap();
			map->setPosition(map->getPosition() + Vec2(200, 0));
		}
		break;
	}
	case (EventKeyboard::KeyCode::KEY_DOWN_ARROW):
	{
		//for (int j = 0; j < appliedSpace.size(); j++)
		{
			auto map = appliedSpace[0]->getMap();
			map->setPosition(map->getPosition() + Vec2(0, 200));
		}
		break;
	}
	}

}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
	delete& typeNum;
	delete& appliedSpace;
	delete& placement;
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}


/*void HelloWorld::initHRocker()
{
	_rocker = HRocker::createHRocker("rocker.png", "rockerBG.png", Vec2(200, 100));
	this->addChild(_rocker);
	_rocker->startRocker(true);

}




//测试函数：初始化武器实例（破旧的手枪，鱼（尚方宝剑），冲锋枪，霰弹枪）
void HelloWorld::test_InitPistol() {
	_testPistol = OldPistol::create
	("GunImage\\OldPistol.png", "GunImage\\OldPistolReverse.png", this, sideHero, true);
	this->addChild(_testPistol);
	_testPistol->startWeapon(true);
}
void HelloWorld::test_InitFish() {
	_testFish = Fish::create
	("MeleeImage\\Fish.png", "MeleeImage\\FishReverse.png", this, sideHero, true);
	this->addChild(_testFish);
	_testFish->startWeapon(true);
}
void HelloWorld::test_InitSMG() {
	_testSMG = SMG::create
	("GunImage\\SMG.png", "GunImage\\SMGReverse.png", this, sideHero, true);
	this->addChild(_testSMG);
	_testSMG->startWeapon(true);
}
void HelloWorld::test_InitShotgun() {
	_testShotgun = Shotgun::create
	("GunImage\\Shotgun.png", "GunImage\\ShotgunReverse.png", this, sideHero, true);
	this->addChild(_testShotgun);
	_testShotgun->startWeapon(true);
}
*/



void HelloWorld::update(float delta) {
	/*
	//注意：启用后要修改HelloWorld：：Init，添加相应的test——Init类
	/////////////////以冲锋枪SMG为例，update函数中测试Gun类，不需要可注释掉/////////////////////////
	_testShotgun->updateCurrentLocation();
	_testShotgun->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	_testShotgun->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）或没有目标时手柄瞄准
	if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
		_testShotgun->attack();//攻击，发射子弹
	}
	updateBullet();//更新飞行物
	/////////////////////////////////////////////////////////////////////////////////////////////

	
	/////////////////以冲锋枪SMG为例，update函数中测试Gun类的自动瞄准，不需要可注释掉////////////////
	//auto i = _currentUnit.begin();
	//(*i)->setPosition((*i)->getPositionX()+1, (*i)->getPositionY());
	//_testSMG->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	//_testSMG->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
	//	_testSMG->attack();//攻击，发射子弹
	//}
	//updateBullet();//更新飞行物
	/////////////////////////////////////////////////////////////////////////////////////////////
	*/
	updateMap();//更新地图
	

}

void HelloWorld::findCurMap(Sprite* player)//找到主角当前地图
{
	CCTMXTiledMap* map = curMap;
	auto playerWorldPos = (player->getParent())->convertToWorldSpace(player->getPosition());
	for (int i = 0; i < appliedSpace.size(); i++)
	{
		if (appliedSpace[i]->isInBound(playerWorldPos))
		{
			map = appliedSpace[i]->getMap();
			break;
		}
	}
	if (map == curMap)
		return;
	else if (map != nullptr)
	{
		curMap = map;
		auto playerLocalPos = map->convertToNodeSpace(playerWorldPos);
		player->setPosition(playerLocalPos);
		player->setParent(NULL);
		map->addChild(player);
		log("Map changes!");
	}
	
}

void HelloWorld::updateMap()
{
	findCurMap(knight);
}

bool HelloWorld::initMaps()
{
	//std::string startRoom = "StartRoom.tmx";
	std::string verticalCorridor = "VerticalCorridor.tmx";
	std::string horizontalCorridor = "HorizontalCorridor.tmx";
	//std::string monsterRoom4Exits = "MonsterRoom4Exits.tmx";
	exitDownMaps = {"D1.tmx","D1.tmx","D1.tmx","DR.tmx","UD.tmx","DL.tmx","UDL.tmx","DLR.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx"};
	exitRightMaps = { "R1.tmx","R1.tmx","R1.tmx","DR.tmx","UR.tmx","LR.tmx","ULR.tmx","DLR.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
	exitUpMaps = { "U1.tmx","U1.tmx","U1.tmx","UD.tmx","UR.tmx","UL.tmx","ULR.tmx","UDL.tmx","UDR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
	exitLeftMaps = { "L1.tmx","L1.tmx","L1.tmx","DL.tmx","LR.tmx","UL.tmx","ULR.tmx","UDL.tmx","DLR.tmx","UDLR1.tmx","UDLR2.tmx","UDLR3.tmx" };
	corridors = { verticalCorridor,horizontalCorridor };
	auto firstRoom = Space::create(this);
	if (firstRoom != nullptr)
	{
		auto firstMap = firstRoom->getMap();
		//auto firstMap = CCTMXTiledMap::create(squareRoom);
		if (firstMap != nullptr)
		{
			this->addChild(firstMap, 0);
			placement[0][2] = FULL;
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			firstMap->setAnchorPoint(Vec2(0.5, 0.5));
			firstMap->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height/2 + origin.y));
			auto mapSize = firstMap->getMapSize();
			auto tileSize = firstMap->getTileSize();
			//firstMap->setPosition(Vec2(origin.x+20, visibleSize.height/2+ origin.y));
			auto curAnc = firstMap->getAnchorPoint();
			auto curPos = firstMap->getPosition();
			firstRoom->resetAnchor(Vec2(0.5, 0.5));
			firstRoom->setCover(Rect(firstMap->getPosition(),Size(mapSize.width*tileSize.width/2.0915,mapSize.height*tileSize.height/2.0915)));
			this->curMap = firstMap;
			this->appliedSpace.push_back(firstRoom);
			typeNum[1]++;
			roomCount++;
		}
		else
		{
			log("Map access failed!");
			return false;
		}
	}
	else 
	{
		log("Room building failed!");
		return false;
	}
	//while (roomCount < 9)
	{
		for (int j = 0; j < appliedSpace.size(); j++)
		{
			appliedSpace[j]->getCover();
			for (int i = 1; i <= 4; i++)
			{
				if (i > 4)
				{
					log("exitInfo out of range.");
				}
				else
				{
					if (appliedSpace[j]!=nullptr&&appliedSpace[j]->exitInfo[i] == E_UNAPPENDED)//存在出口未延伸
					{
						Space* temp = appliedSpace[j]->append(this, i);
						if (temp != nullptr)
						{
							temp->count = appliedSpace.size();
							this->appliedSpace.push_back(temp);
							appliedSpace[j]->exitInfo[i] = E_APPENDED;
							int otherExit = i > 2 ? i - 2 : i + 2;
							appliedSpace[appliedSpace.size() - 1]->exitInfo[otherExit] = E_APPENDED;
						}
					}
				}
			}
		}
	}
	
}

bool HelloWorld::roomNotFull(int type)
{
	switch (type)
	{
	case(1):
		return true;
		//return typeNum[type] < 5 ? true : false;
	case(2):
		return typeNum[type] < 4 ? true : false;
	case(3):
		return typeNum[type] < 2 ? true : false;
	case(4):
		return typeNum[type] < 2 ? true : false;
	default:
		return false;
	}
}





/*
void HelloWorld::updateBullet() {
	//TODO:只添加了射击现象
	for (auto i = _bullets.begin(); i != _bullets.end();i++) {
		(*i)->setVisible(true);
		(*i)->calPosition();
	}
}

Character* HelloWorld::addCharacter(TMXTiledMap* map,int HeroID) {
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
*/