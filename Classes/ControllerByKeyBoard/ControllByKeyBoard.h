#pragma once
#include "cocos2d.h"
#include "ControllerListener.h"
USING_NS_CC;
class ControllByKeyboard :public Node {
public:
	/*���ü�������*/
	void setControllerListener(ControllerListener* controllerListener);
protected:
	ControllerListener* m_controllerListener;//�����õļ�������

};