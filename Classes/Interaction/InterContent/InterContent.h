#pragma once

#include "cocos2d.h"

USING_NS_CC;

// 交互物，包括传送门，宝箱，随从，和buff等等
// 传送门和宝箱的图片已有，随从和buff图片暂无；

class InterContent :public Layer
{
public:
	static cocos2d::Scene* createScene();  //测试，之后替换为实际地图
	virtual bool init();
	CREATE_FUNC(InterContent);
public:
	//键盘监听事件，主角是否对交互物产生反应
	//动态效果，传送门和宝箱在交互后会产生动作
private:                                   //交互物的属性，后面可能会加
};