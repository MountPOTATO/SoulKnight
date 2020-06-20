#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Character;

class StatusBar:public Node
{
	CC_SYNTHESIZE(Character*, theHero, TheHero);
public:
	static StatusBar* create(Point position, Character* hero,int color);
	bool init(Point position, Character* hero,int color);

	void updateStatusBar(int color);
	void setStatusBar(const CCRect& rect);
private:
	float scale;
	char str[20] = {0};

	Label* statusLabel;
};
