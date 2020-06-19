#include "PauseLayer.h"
#include "SimpleAudioEngine.h" 
#include "Scene/StartScene.h"

Scene* PauseLayer::createScene(CCRenderTexture* sqr)
{
	/*log("has create");*/
	Scene* scene = Scene::create();

	Layer* pauseLayer = PauseLayer::create();
	pauseLayer->setPosition(480, 320);
	scene->addChild(pauseLayer);

	Sprite* sp = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	sp->setPosition(Vec2(0,0));
	sp->setFlipY(true);
	pauseLayer->addChild(sp,0);
	
	Sprite* stopLayer = Sprite::create("Pause/stopLayer.png");
	stopLayer->setPosition(0, 0);
	pauseLayer->addChild(stopLayer, 1);
	
	return scene;

}

bool PauseLayer::init()
{

	MenuItemImage* homePage = MenuItemImage::create(
		"Pause/homePage.png",
		"Pause/homePage.png",
		CC_CALLBACK_1(PauseLayer::menuHomePage, this)
	);
	homePage->setScale(0.27);
	homePage->setPosition(-170, -100);

	MenuItemImage* resume = MenuItemImage::create(
		"Pause/resume.png",
		"Pause/resume.png",
		CC_CALLBACK_1(PauseLayer::menuResume, this)
	);
	resume->setPosition(0, -95);

	MenuItemImage* onMusic = MenuItemImage::create("Pause/continueMusic.png", "Pause/continueMusic.png");
	MenuItemImage* offMusic = MenuItemImage::create("Pause/stopMusic.png", "Pause/stopMusic.png");
	
	MenuItemToggle* music = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(PauseLayer::menuMusic, this),
		onMusic, offMusic, NULL
	);

	music->setPosition(170, -100);

	Menu* menu = Menu::create(homePage,resume,music, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu,2);

	return true;
}

void PauseLayer::menuHomePage(cocos2d::Ref* pSender)
{
	/*log("nice!!");*/
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/button.mp3", false);
	Director::getInstance()->replaceScene(StartScene::createScene());
	Director::getInstance()->resume();
}

void PauseLayer::menuResume(cocos2d::Ref* pSender)
{
	/*log("resume");*/
	auto audioEffect = CocosDenshion::SimpleAudioEngine::getInstance();
	audioEffect->playEffect("Audio/button.mp3", false);
	Director::getInstance()->popScene();
	Director::getInstance()->resume();
}

void PauseLayer::menuMusic(cocos2d::Ref* pSender)
{
	/*log("music");*/
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