#pragma once
#include "ControllByKeyBoard.h"
#include "cocos2d.h"
 
USING_NS_CC;
class ControllerOfEightDir :public ControllByKeyboard {
public:
	CREATE_FUNC(ControllerOfEightDir);
	virtual bool init();
	virtual void update(float delta);

	/*���ÿ������м�¼���ƶ��ٶ�*/
	void setiSpeed(int iSpeed);

	
private:
	int m_iSpeed;
	EventListenerKeyboard* listenerKey;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//����ÿ������״̬��trueΪ��ס��falseΪ�ɿ�
};

