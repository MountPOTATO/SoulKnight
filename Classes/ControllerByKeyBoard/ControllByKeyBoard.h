#pragma once
#include "cocos2d.h"
#include "ControllerListener.h"
USING_NS_CC;
class ControllByKeyboard :public Node {
public:
	/*设置监听对象*/
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;//已设置的监听对象

};