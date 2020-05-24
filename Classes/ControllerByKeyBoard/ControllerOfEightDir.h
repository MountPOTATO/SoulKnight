#pragma once
#include "ControllByKeyBoard.h"
#include "cocos2d.h"
 
USING_NS_CC;
class ControllerOfEightDir :public ControllByKeyboard {
public:
	CREATE_FUNC(ControllerOfEightDir);
	virtual bool init();
	virtual void update(float delta);

	/*�����ƶ��ٶ�*/
	void setiSpeed(int iSpeed);
private:
	int m_iSpeed;
	EventListenerKeyboard* listenerKey;

};

