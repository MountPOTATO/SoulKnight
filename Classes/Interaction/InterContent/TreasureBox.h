#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TreasureBox :public Layer
{
public:
	static Scene* createScene();

	bool init();
	CREATE_FUNC(TreasureBox);
	bool isToOpen();
};