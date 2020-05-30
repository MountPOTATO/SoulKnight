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

	//�˴��޸�
	/*test_InitGun();*/
	test_InitMelee();

	//�����Զ���׼ʱ���ϣ�����Ҫ����ʱȥ��
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
	
	//ע�⣺���ú�Ҫ�޸�HelloWorld����Init�������Ӧ��test����Init��
	/////////////////////////////////update�����в���Gun�࣬����Ҫ��ע�͵�//////////////////////////
	//_testGun->updateTarget();//Gunʵ�� ���³��ڹ������꣬������Լ�����Ĺ���
	//_testGun->updateImageRotation(_rocker);//Gunʵ�� ��������ָ���Զ���׼����û��Ŀ��ʱ�ֱ���׼
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//���¹�����
	//	_testGun->attack();//�����������ӵ�
	//}
	//updateBullet();//���·�����
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////update�����в���Melee�࣬����Ҫ��ע�͵�//////////////////////////
	_testMelee->updateTarget();//Meleeʵ�� ���³��ڹ������꣬����Χ�ڵĹ������Melee��ԱVector��
	_testMelee->updateImageRotation(_rocker); //Meleeʵ������������ָ���Զ���׼��
	if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//���¹�����
		_testMelee->attack();//������Ŀǰֻ����ת360�ȵĹ�������
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////update�����в���Gun����Զ���׼������Ҫ��ע�͵�//////////////////////////
	//auto i = _currentUnit.begin();
	//(*i)->setPosition((*i)->getPositionX()+1, (*i)->getPositionY());
	//_testGun->updateTarget();//Gunʵ�� ���³��ڹ������꣬������Լ�����Ĺ���
	//_testGun->updateImageRotation(_rocker);//Gunʵ�� ��������ָ���Զ���׼��
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//���¹�����
	//	_testGun->attack();//�����������ӵ�
	//}
	//updateBullet();//���·�����
	/////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////update�����в���Melee����Զ���׼������Ҫ��ע�͵�//////////////////////////
	//auto i = _currentUnit.begin();
	//(*i)->setPosition((*i)->getPositionX(), (*i)->getPositionY() + 1);
	//_testMelee->updateTarget();//Gunʵ�� ���³��ڹ������꣬������Լ�����Ĺ���
	//_testMelee->updateImageRotation(_rocker);//Gunʵ�� ��������ָ���Զ���׼��
	//if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {//���¹�����
	//	_testMelee->attack();//�����������ӵ�
	//}
	//updateBullet();//���·�����
	/////////////////////////////////////////////////////////////////////////////////////////////
}

void HelloWorld::updateBullet() {
	//TODO:ֻ������������
	for (auto i = _bullets.begin(); i != _bullets.end();i++) {
		(*i)->setVisible(true);
		(*i)->calPosition();
	}
}