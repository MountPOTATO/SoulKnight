

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
#include "LongRangeAttack/Bullet.h"
class Weapon;

class HelloWorld : public cocos2d::Scene
{
	//5.18����CCSYNTHESIZE ��������
	CC_SYNTHESIZE(HRocker*, _rocker, Rocker);


	

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	virtual void update(float delta);//����״̬
	void updateBullet();

	//������
	Vector<Bullet*> _bullets;
	Vector<Entity*> _currentUnit;



	//��ʼ��ҡ��
	void initHRocker();

	//�������:

	


	CC_SYNTHESIZE(OldPistol*, _testPistol, TestPistol);//��ʼ��һ����ս������

	CC_SYNTHESIZE(Fish*, _testFish, TestFish);//��ʼ��һ����ս������

	CC_SYNTHESIZE(SMG*, _testSMG, TestSMG);//��ʼ��һ����ս������

	CC_SYNTHESIZE(Shotgun*, _testShotgun, TestShotgun);//��ʼ��һ����ս������

	void test_InitPistol();
	void test_InitFish();
	void test_InitSMG();
	void test_InitShotgun();

private:
	
	
	




	//����װ��
	EventListenerTouchOneByOne* listenerTouch;
	EventListenerKeyboard* listenerKeyBoard;
	//��������
	
};

#endif // __HELLOWORLD_SCENE_H__
