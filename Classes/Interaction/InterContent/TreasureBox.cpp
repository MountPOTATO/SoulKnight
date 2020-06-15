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
		case EventKeyboard::KeyCode::KEY_Y:   //yΪ������ͬʱҲ�ǽ�������,����ĺ����ǿ�����
			log("is there");
			/*node->setScale(1.0);*/
			node->removeFromParentAndCleanup(true);  //��������� ��������Ҳ���Կ��Ƕ���Ч��
			{                                        //����û���㹻��ͼƬ
				/*isToOpen();*/
				Sprite* treaBoxOpen = Sprite::create("treasureBoxOpen.png");
				Size size = Director::getInstance()->getVisibleSize();
				treaBoxOpen->setPosition(position);
				this->addChild(treaBoxOpen);
				treaBoxOpen->setVisible(true);
				//�������ڱ�����Ӧ�ó���һЩ���� �����ƿ ���� ��ҵ�
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
			//Ʈ����Ч���룬����Ʈ��״̬

		}
		return;
	}
	else {
		if (_rocker->getRockerPressButton() == ERockerButtonPress::buttonAttack) {
			_isPressed = true;
			

			//ֹͣƮ��
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