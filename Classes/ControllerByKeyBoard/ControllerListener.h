#pragma once

#include "cocos2d.h"
USING_NS_CC;
class ControllerListener {
public:
	/*设置目标位置*/
	virtual void setTagPosition(int x, int y) = 0;

	/*获取目标位置*/
	virtual void getTagPosition() = 0;

};
