#include "StartScene.h"
#include "HelloWorldScene.h"
#include "Scene/WinScene.h"


USING_NS_CC;

Scene* WinScene::createScene()
{
	return WinScene::create();
}

//Promble loading
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

bool WinScene::init()
{
	if (!Scene::init())		return false;




	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//Start Bottom
	MenuItemImage* startMenu = MenuItemImage::create(
		"Scenes/StartScene/Start.png",
		"Scenes/StartScene/Start1.png",
		CC_CALLBACK_1(WinScene::menuStartCallBack, this)
	);

	if (startMenu == nullptr || startMenu->getContentSize().width <= 0 || startMenu->getContentSize().height <= 0) {
		problemLoading("'startMenu.png'");
	}
	else {

		startMenu->setPosition(Vec2(visibleSize.width / 2 - 300, visibleSize.width / 2 - 380));
	}

	MenuItemImage* endMenu = MenuItemImage::create(
		"Scenes/StartScene/End.png",
		"Scenes/StartScene/End1.png",
		CC_CALLBACK_1(WinScene::menuEndCallBack, this)
	);

	if (endMenu == nullptr || endMenu->getContentSize().width <= 0 || endMenu->getContentSize().height <= 0) {
		problemLoading("'endMenu.png'");
	}
	else {

		endMenu->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 - 222));
	}




	Menu* menu = Menu::create(startMenu, endMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	//background
	auto background = Sprite::create("Scenes/StartScene/WinScene.png");
	if (background == nullptr)
	{
		problemLoading("'WinScene.png'");
	}
	else {
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}


void WinScene::menuStartCallBack(cocos2d::Ref* pSender) {
	auto nextScene = StartScene::createScene();
	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;


	log("Touch Helo Menu Item %p", item);
}


void WinScene::menuEndCallBack(cocos2d::Ref* pSender) {
	Director::getInstance()->end();
}

