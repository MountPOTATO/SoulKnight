#pragma once

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer :public Layer
{
public:
	static Scene* createScene(CCRenderTexture* sqr);
	bool init();

	CREATE_FUNC(PauseLayer);

	void menuHomePage(cocos2d::Ref* pSender);
	void menuResume(cocos2d::Ref* pSender);
	void menuMusic(cocos2d::Ref* pSender);
};
