#include "TreasureBox.h"

Scene* TreasureBox::createScene()
{
	auto scene = Scene::create();

	auto layer = TreasureBox::create();
	scene->addChild(layer);
	return scene;
}

bool TreasureBox::init()
{
	Sprite* treaBox = Sprite::create("treasureBox.png");
	Size size = Director::getInstance()->getVisibleSize();
	treaBox->setTag(1);
	treaBox->setPosition(size.width / 2, size.height / 2);
	this->addChild(treaBox);
	/*treaBox->setScale(5.0);*/

	log("is run?");

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
				treaBoxOpen->setPosition(Vec2(size.width / 2, size.height / 2));
				this->addChild(treaBoxOpen);
				//�������ڱ�����Ӧ�ó���һЩ���� �����ƿ ���� ��ҵ�
			}
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,treaBox);
	return true;
}

bool TreasureBox::isToOpen()
{
	//�ж������Ƿ��ڱ����Աߣ����Ƿ�ﵽ��������
	//�ﵽΪtrue������Ϊfalse
	return true;
}