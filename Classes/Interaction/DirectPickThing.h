#ifndef _DIRECTPICKTHING_H_
#define _DIRECTPICKTHING_H_
#include "cocos2d.h"

USING_NS_CC;

class Entity;
class HelloWorld;
//自动拾取物体，包括金币，能量

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



	
};

#endif