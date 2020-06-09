#pragma once
#include "cocos2d.h"

USING_NS_CC;

//PickThing为拾取道具，拾取道具包括武器，红瓶，蓝瓶

class PickThing :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PickThing);
	PickThing();
	~PickThing();
public:
	bool setVisible();
	//键盘事件监听 未实现
	//主角拾取道具后状态的改变，需要charater类的功能
private:
	bool isVisible;
};