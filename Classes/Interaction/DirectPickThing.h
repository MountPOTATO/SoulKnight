#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Entity;
class HelloWorld;
//PickThing为拾取道具，拾取道具包括武器，红瓶，蓝瓶

class DirectPickThing :public Node
{
	CC_SYNTHESIZE(float, _stickRange,StickRange); //贴近吸收距离
	CC_SYNTHESIZE(INT32, _generateRange, GenerateRange);//随机生成距离的范围

	CC_SYNTHESIZE(INT32, _blueNumber, BlueNumber); //蓝的个数
	CC_SYNTHESIZE(INT32, _coinNumber, CoinNumber); //钱币的个数

	CC_SYNTHESIZE(HelloWorld*, _pickThingScene, PickThingScene);//场景

	CC_SYNTHESIZE(Entity*, _hero, Hero);//赋予的英雄

public:
	

	static DirectPickThing* create(Point position, Entity* hero, float stickRange,
		 int blueNumber,int coinNumber, int generateRange, HelloWorld* helloWorldScene);


	virtual bool init(Point position, Entity* hero, float stickRange,
		int blueNumber, int coinNumber, int generateRange, HelloWorld* helloWorldScene);

	void updatePickThingSprite();

	//键盘事件监听 未实现
	//主角拾取道具后状态的改变，需要charater类的功能

	
};