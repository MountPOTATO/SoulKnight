#pragma once

#include "cocos2d.h"

USING_NS_CC;

class NormalBox :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NormalBox);
	NormalBox();
	~NormalBox();
public:
	bool isColliedWithBullet(); //判断是否被子弹击中，箱子是否消失			
	bool setVisible();          //设置箱子是否可见
private:
	bool isVisible;
};