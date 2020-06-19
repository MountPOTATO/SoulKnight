#include "StartScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h" 
#include "Scene/LoseScene.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	return StartScene::create();
}

//Promble loading
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartGameScene.cpp\n");
}

bool StartScene::init()
{
	if (!Scene::init())		return false;
	
	//声音
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (!audio->isBackgroundMusicPlaying()) {
		audio->playBackgroundMusic("Audio/StartGame.mp3", true);
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();//得到屏幕大小
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//获得可视区域的出发点坐标，在处理相对位置时，确保节点在不同分辨率下的位置一致。

	//Start Bottom
	MenuItemImage* startMenu = MenuItemImage::create(
		"Scenes/StartScene/Start.png",
		"Scenes/StartScene/Start1.png",
		CC_CALLBACK_1(StartScene::menuStartCallBack, this)
	);

	if (startMenu == nullptr ||startMenu->getContentSize().width <= 0 ||startMenu->getContentSize().height <= 0){
		problemLoading("'startMenu.png'");
	}
	else{

		startMenu->setPosition(Vec2(visibleSize.width / 2 - 230, visibleSize.width / 2 - 380));
	}

	MenuItemImage* endMenu = MenuItemImage::create(
		"Scenes/StartScene/End.png",
		"Scenes/StartScene/End1.png",
		CC_CALLBACK_1(StartScene::menuEndCallBack, this)
	);

	if (endMenu == nullptr ||endMenu->getContentSize().width <= 0 ||endMenu->getContentSize().height <= 0){
		problemLoading("'endMenu.png'");
	}
	else{
	
		endMenu->setPosition(Vec2(visibleSize.width / 2 - 55, visibleSize.height / 2 -225));
	}


	auto onMusic = MenuItemImage::create("Scenes/StartScene/stopMusic.png", "Scenes/StartScene/stopMusic.png");
	auto offMusic = MenuItemImage::create("Scenes/StartScene/continueMusic.png", "Scenes/StartScene/continueMusic.png");

	MenuItemToggle* musicMenu = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(StartScene::menuMusicCallBack, this),
		offMusic, onMusic, NULL
	);
	musicMenu->setPosition(Vec2(visibleSize.width/2-400, visibleSize.height/2-225));

	Menu* menu = Menu::create(startMenu, endMenu, musicMenu, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//background
	auto background = Sprite::create("Scenes/StartScene/BackGround.png");
	if (background == nullptr)
	{
		problemLoading("'BackGround.png'");
	}
	else{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, 0);
	}

	return true;
}


void StartScene::menuStartCallBack(cocos2d::Ref* pSender){
	auto nextScene = HelloWorld::createScene();
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/button.mp3", false);

	Director::getInstance()->replaceScene(
		TransitionSlideInT::create(1.0f / 60, nextScene));
	MenuItem* item = (MenuItem*)pSender;


	log("Touch Helo Menu Item %p", item);
}


void StartScene::menuEndCallBack(cocos2d::Ref* pSender){
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/button.mp3", false);

	Director::getInstance()->end();
}


void StartScene::menuMusicCallBack(cocos2d::Ref* pSender)
{
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/button.mp3", false);

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying()) {
		audio->pauseBackgroundMusic();
	}
	else {

		audio->resumeBackgroundMusic();
	}
}