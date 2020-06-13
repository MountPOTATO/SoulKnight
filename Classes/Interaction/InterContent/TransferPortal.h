#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TransferPortal :public Layer
{
public:
	static Scene* createScene();
	bool init();                     //初始换传送门，实现动画效果
	CREATE_FUNC(TransferPortal);
	bool isToPushScene();            //判断是否要切换场景
	bool isColliedWithCharacter();
	
	//判断是否创建传送门，需要在主函数里进行实现


//public:
//	static Layer* layer;
};