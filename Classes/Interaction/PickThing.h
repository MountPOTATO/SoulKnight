#pragma once
#include "cocos2d.h"

USING_NS_CC;

//PickThingΪʰȡ���ߣ�ʰȡ���߰�����������ƿ����ƿ

class PickThing :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(PickThing);
	PickThing();
	~PickThing();
public:
	bool setVisible();
	//�����¼����� δʵ��
	//����ʰȡ���ߺ�״̬�ĸı䣬��Ҫcharater��Ĺ���
private:
	bool isVisible;
};