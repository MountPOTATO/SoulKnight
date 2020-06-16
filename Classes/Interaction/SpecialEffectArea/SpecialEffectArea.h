#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define pi 3.1415926535

//机关区域可能包括 加速减速带，地刺，毒圈等等
//机关区域的图片暂无

class SpecialEffectArea :public Layer
{
public:
	cocos2d::Scene* createScene();
	bool init();
	CREATE_FUNC(SpecialEffectArea);
public:
	//不同机关区域的特殊功能
	//加速减速带，地刺，毒圈需要涉及到character类，用来改变主角的属性
	//加速减速带需要时间计时器，可能需要lambda函数
private:
	//具体属性
	//如加速减速带的速度改变量
	//地刺和毒圈的扣血
	//可在子类里实现
};