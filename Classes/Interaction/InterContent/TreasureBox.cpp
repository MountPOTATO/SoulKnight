#include "TreasureBox.h"
#include "Entity/Entity.h"
#include "Controller/HRocker.h"
#include "HelloWorldScene.h"

#include "Interaction/InterContent/PickWeapon.h"

TreasureBox* TreasureBox::create(Point position, Entity* hero, HelloWorld* scene, HRocker* rocker)
{
	TreasureBox* treasurebox = new(std::nothrow)TreasureBox;
	if (treasurebox && treasurebox->init(position, hero, scene, rocker)) {
		treasurebox->autorelease();
		return treasurebox;
	}
	CC_SAFE_DELETE(treasurebox);
	return NULL;
}

bool TreasureBox::init(Point position, Entity* hero, HelloWorld* scene, HRocker* rocker)
{
	setPosition(position);

	Sprite* treaBox = Sprite::create("treasureBox.png");
	Size size = Director::getInstance()->getVisibleSize();
	treaBox->setTag(1);
	treaBox->setPosition(0,0);
	treaBox->setVisible(true);

	this->addChild(treaBox);
	/*treaBox->setScale(5.0);*/
	_hero = hero;
	_rocker = rocker;

	_isPressed = false;
	_isNearHero = false;
	_isunUsed = true;
	_pickThingScene = scene;


	srand((unsigned)time(NULL));
	_randID = rand() % 4 + 1;


	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode code, Event* e)
	{
		auto node = this->getChildByTag(1);
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_Y:   //y为攻击，同时也是交互按键,这里的含义是开宝箱
			log("is there");
			/*node->setScale(1.0);*/
			node->removeFromParentAndCleanup(true);  //清理掉宝箱 或者这里也可以考虑动画效果
			{                                        //但还没有足够的图片
				/*isToOpen();*/
				Sprite* treaBoxOpen = Sprite::create("treasureBoxOpen.png");
				Size size = Director::getInstance()->getVisibleSize();
				treaBoxOpen->setPosition(position);
				this->addChild(treaBoxOpen);
				treaBoxOpen->setVisible(true);
				//接下来在宝箱中应该出现一些奖励 如红蓝瓶 武器 金币等
			}
			break;
		default:
			break;
		}
	};


	return true;
}



void TreasureBox::updateTreasureBoxState()
{
	if (!_isNearHero) {
		if (this->getPosition().distance(_hero->getPosition()) <= 17.0f
			&& _rocker->getRockerPressButton() != ERockerButtonPress::buttonAttack) {
			_isNearHero = true;
			//飘字特效加入，进入飘字状态

		}
		return;
	}
	else {
		if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isPressed = true;
			

			//停止飘字
		}
		return;
	}
}


void TreasureBox::generateRandomObject() {

	Sprite* spTre = (Sprite*)getChildByTag(1);
	spTre->setVisible(false);


	Sprite* treaBoxOpen = Sprite::create("treasureBoxOpen.png");
	Size size = Director::getInstance()->getVisibleSize();
	treaBoxOpen->setPosition(0,0);
	this->addChild(treaBoxOpen);
	treaBoxOpen->setVisible(true);





	if (_randID == 1) {

		auto pickWeapon = PickWeapon::create
		(this->getPosition(), _hero, _pickThingScene, GUN, GUN_SNIPER, _rocker);
		_pickThingScene->addChild(pickWeapon);
		_pickThingScene->_pickableWeaponVec.pushBack(pickWeapon);
	}
	if (_randID == 2) {

		auto pickWeapon = PickWeapon::create
		(this->getPosition(), _hero, _pickThingScene, GUN, GUN_SMG, _rocker);
		_pickThingScene->addChild(pickWeapon);
		_pickThingScene->_pickableWeaponVec.pushBack(pickWeapon);
	}
	if (_randID == 3) {

		auto pickWeapon = PickWeapon::create
		(this->getPosition(), _hero, _pickThingScene, GUN, GUN_SHOTGUN, _rocker);
		_pickThingScene->addChild(pickWeapon);
		_pickThingScene->_pickableWeaponVec.pushBack(pickWeapon);
	}
	if (_randID == 4) {

		auto pickWeapon = PickWeapon::create
		(this->getPosition(), _hero, _pickThingScene,MELEE,MELEE_FISH, _rocker);
		_pickThingScene->addChild(pickWeapon);
		_pickThingScene->_pickableWeaponVec.pushBack(pickWeapon);
	}

	_isunUsed = false;
}