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
		case EventKeyboard::KeyCode::KEY_Y:   //y为攻击，同时也是交互按键,这里的含义是开宝箱
			log("is there");
			/*node->setScale(1.0);*/
			node->removeFromParentAndCleanup(true);  //清理掉宝箱 或者这里也可以考虑动画效果
			{                                        //但还没有足够的图片
				/*isToOpen();*/
				Sprite* treaBoxOpen = Sprite::create("treasureBoxOpen.png");
				Size size = Director::getInstance()->getVisibleSize();
				treaBoxOpen->setPosition(Vec2(size.width / 2, size.height / 2));
				this->addChild(treaBoxOpen);
				//接下来在宝箱中应该出现一些奖励 如红蓝瓶 武器 金币等
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
	//判断主角是否在宝箱旁边，即是否达到交互距离
	//达到为true，否则为false
	return true;
}