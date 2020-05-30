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

	//此处修改
	/*test_InitGun();*/
	test_InitMelee();

	//测试自动瞄准时加上，不需要测试时去掉
	/*Entity* testEnermy=new Entity();
	Sprite* enermyImage = Sprite::create("HelloWorld.png");
	testEnermy->setPosition(visibleSize.width / 2 - 300, visibleSize.height / 2 - 300);
	testEnermy->bindSprite(enermyImage);
	this->addChild(testEnermy);
	_currentUnit.pushBack(testEnermy);*/


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





void HelloWorld::test_InitGun() {
	_testGun = Gun::create("initWeapon.png", "initWeaponReverse.png", this,sideHero, true);
	this->addChild(_testGun);
	_testGun->startWeapon(true);	
}

void HelloWorld::test_InitMelee() {
	_testMelee = Melee::create("fish.png", "fishReverse.png", this, sideHero, true);
	this->addChild(_testMelee);
	_testMelee->startWeapon(true);
}




void HelloWorld::update(float delta) {
	
	//注意：启用后要修改HelloWorld：：Init，添加相应的test——Init类
	/////////////////////////////////update函数中测试Gun类，不需要可注释掉//////////////////////////
	//_testGun->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	//_testGun->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）或没有目标时手柄瞄准
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
	//	_testGun->attack();//攻击，发射子弹
	//}
	//updateBullet();//更新飞行物
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////update函数中测试Melee类，不需要可注释掉//////////////////////////
	_testMelee->updateTarget();//Melee实例 更新场内怪物坐标，将范围内的怪物存入Melee成员Vector中
	_testMelee->updateImageRotation(_rocker); //Melee实例，更新武器指向（自动瞄准）
	if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
		_testMelee->attack();//攻击，目前只有旋转360度的攻击动画
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////update函数中测试Gun类的自动瞄准，不需要可注释掉//////////////////////////
	//auto i = _currentUnit.begin();
	//(*i)->setPosition((*i)->getPositionX()+1, (*i)->getPositionY());
	//_testGun->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	//_testGun->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
	//	_testGun->attack();//攻击，发射子弹
	//}
	//updateBullet();//更新飞行物
	/////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////update函数中测试Melee类的自动瞄准，不需要可注释掉//////////////////////////
	//auto i = _currentUnit.begin();
	//(*i)->setPosition((*i)->getPositionX(), (*i)->getPositionY() + 1);
	//_testMelee->updateTarget();//Gun实例 更新场内怪物坐标，标记离自己最近的怪物
	//_testMelee->updateImageRotation(_rocker);//Gun实例 更新武器指向（自动瞄准）
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//按下攻击键
	//	_testMelee->attack();//攻击，发射子弹
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