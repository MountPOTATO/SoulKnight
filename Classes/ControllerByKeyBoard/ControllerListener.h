#pragma once

#include "cocos2d.h"
USING_NS_CC;
class ControllerListener {
public:
	/*设置目标位置*/
	virtual void setTagPosition(int x, int y) = 0;

	/*获取目标位置*/
	virtual Point getTagPosition() = 0;
	
	/*根据移动方向设置图片朝向,0为左 1为右*/
	virtual void setFaceDirByMoveDir(int dir)=0;
};
