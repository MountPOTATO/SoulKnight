#pragma once

#include "cocos2d.h"
USING_NS_CC;
class ControllerListener {
public:
	/*����Ŀ��λ��*/
	virtual void setTagPosition(int x, int y) = 0;

	/*��ȡĿ��λ��*/
	virtual void getTagPosition() = 0;

};
