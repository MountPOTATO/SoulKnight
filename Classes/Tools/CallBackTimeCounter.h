#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CallBackTimeCounter :public Node {
public:
	CREATE_FUNC(CallBackTimeCounter);
	virtual bool init();
	virtual void update(float delta);
	void start(float fCBTime, std::function<void()>func);//start������һ������Ϊ��ʱ���ȣ��ڶ���Ϊ��ʱ��ʱ�ص���lambda����

private:
	float m_fTime;//���ڼ�ʱ
	float m_fCBTime;//�ص���ʱ��
	bool m_isCounting;//����Ƿ����ڼ�ʱ
	std::function<void()>m_func;
};