#pragma once
#include "ControllByKeyBoard.h"
#include "cocos2d.h"
 
USING_NS_CC;
class ControllerOfEightDir :public ControllByKeyboard {
public:
	CREATE_FUNC(ControllerOfEightDir);
	virtual bool init();
	virtual void update(float delta);

	/*设置控制器中记录的移动速度*/
	void setiSpeed(int iSpeed);

	
private:
	int m_iSpeed;
	EventListenerKeyboard* listenerKey;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//保存每个按键状态：true为按住，false为松开
};

