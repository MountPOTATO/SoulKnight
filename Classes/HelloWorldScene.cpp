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
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//test Entity can delete
	
	initHRocker();

	//此处修改,初始化一样武器实例,以SMG冲锋枪为例
	/*test_InitFish();*/
	/*test_InitPistol();*/
	test_InitSMG();
	//test_InitShotgun();

	//测试自动瞄准时加上，不需要测试时去掉,同时在update函数中添加相应的模块
	/*Entity* testEnermy=new Entity();
	Sprite* enermyImage = Sprite::create("HelloWorld.png");
	testEnermy->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 300);
	testEnermy->bindSprite(enermyImage);
	this->addChild(testEnermy);
	_currentUnit.pushBack(testEnermy);*/


	//测试地图和角色
	TMXTiledMap* map = TMXTiledMap::create("Maps/test.tmx");
	this->addChild(map);
	addCharacter(map);

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




void HelloWorld::update(float delta) {
	
	//注意：启用后要修改HelloWorld：：Init，添加相应的test——Init类
	/////////////////以冲锋枪SMG为例，update函数中测试Gun类，不需要可注释掉/////////////////////////
	_testSMG->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	_testSMG->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）或没有目标时手柄瞄准
	if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
		_testSMG->attack();//攻击，发射子弹
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



}

void HelloWorld::updateBullet() {
	//TODO:只添加了射击现象
	for (auto i = _bullets.begin(); i != _bullets.end();i++) {
		(*i)->setVisible(true);
		(*i)->calPosition();
	}
}

void HelloWorld::addCharacter(TMXTiledMap* map) {
	Character* m_Character = Character::create();
	Sprite* sprite = Sprite::create("Characters/Knight.png");
	m_Character->bindSprite(sprite);
	this->addChild(m_Character,0);

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

	
}
