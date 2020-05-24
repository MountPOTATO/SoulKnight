#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CallBackTimeCounter :public Node {
public:
	CREATE_FUNC(CallBackTimeCounter);
	virtual bool init();
	virtual void update(float delta);
	void start(float fCBTime, std::function<void()>func);//start函数第一个参数为计时长度，第二个为到时间时回调的lambda函数

private:
	float m_fTime;//用于计时
	float m_fCBTime;//回调的时间
	bool m_isCounting;//标记是否正在计时
	std::function<void()>m_func;
};