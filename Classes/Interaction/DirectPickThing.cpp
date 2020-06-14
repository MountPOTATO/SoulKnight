#include "Interaction/DirectPickThing.h"
#include "Entity/Entity.h"
#include <cmath>
#include "HelloWorldScene.h"

DirectPickThing* DirectPickThing::create(Point position, Entity* hero, float stickRange,
	int blueNumber, int coinNumber, int generateRange, HelloWorld* helloWorldScene) {

	DirectPickThing* dpthing = new DirectPickThing;
	if (dpthing && dpthing->init(position, hero, stickRange, blueNumber, coinNumber, generateRange, helloWorldScene)) {
		dpthing->autorelease();
		return dpthing;
	}
	CC_SAFE_DELETE(dpthing);
	return NULL;
}

bool DirectPickThing::init(Point position, Entity* hero, float stickRange,
	int blueNumber, int coinNumber, int generateRange, HelloWorld* helloWorldScene) {

	if (!Node::init()) return false;
		
	this->setPosition(position);

	_stickRange = stickRange;
	_blueNumber = blueNumber;
	_generateRange = abs(generateRange);
	_pickThingScene = helloWorldScene;
	_hero = hero;


	Vector<Sprite*>& engVec = _pickThingScene->_energyVec;
	Vector<Sprite*>& coiVec = _pickThingScene->_coinVec;
	for (int i = 1; i <=blueNumber; i++) {
		Sprite* spBlue = Sprite::create("Energy.png");

		float deflection1 = rand() % (_generateRange * 2 + 1) - (_generateRange);
		float deflection2 = rand() % (_generateRange * 2 + 1) - (_generateRange);
		spBlue->setPosition(this->getPositionX() + deflection1, this->getPositionY() + deflection2);

		spBlue->setVisible(true);
		engVec.pushBack(spBlue);
		_pickThingScene->addChild(spBlue);
	}
	
	for (int i = -1; i >= -coinNumber; i--) {
		Sprite* spCoin =Sprite::create("Coin.png");

		float deflection1 = rand() % (_generateRange * 2 + 1) - (_generateRange);
		float deflection2 = rand() % (_generateRange * 2 + 1) - (_generateRange);
		spCoin->setPosition(this->getPositionX()+deflection1, this->getPositionY() + deflection2);
		spCoin->setVisible(true);
		coiVec.pushBack(spCoin);
		_pickThingScene->addChild(spCoin);
	}

	return true;
}


void DirectPickThing::updatePickThingSprite() {
	//������λ�ø��£�������
	auto i = _pickThingScene->_coinVec.begin();
	for (auto i = _pickThingScene-> _coinVec.begin(); i != _pickThingScene->_coinVec.end();) {
		//TODO:λ�ø���
		if ((*i)->getPosition().distance(_hero->getPosition()) <= _stickRange) {
			//TODO:���Ǽӽ��
			(*i)->setVisible(false);
			i=_pickThingScene->_coinVec.erase(i);

		}
		else {
			i++;
		}
	}

	for (auto i = _pickThingScene->_energyVec.begin(); i != _pickThingScene->_energyVec.end();) {
		//TODO:λ�ø���
		
		if ((*i)->getPosition().distance(_hero->getPosition()) <= _stickRange) {
			//TODO:���Ǽ�����
			(*i)->setVisible(false);
			i = _pickThingScene->_energyVec.erase(i);

		}
		else {
			i++;
		}
	}
}









//���̼����¼���ʹʰȡ������ʧ

//����ʰȡ���ߺ�״̬�ĸı䣬��Ҫcharater��Ĺ���