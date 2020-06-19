#pragma once

#include "cocos2d.h"

USING_NS_CC;

class NormalBox :public Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NormalBox);
	NormalBox();
	~NormalBox();
public:
	bool isColliedWithBullet(); //�ж��Ƿ��ӵ����У������Ƿ���ʧ			
	bool setVisible();          //���������Ƿ�ɼ�
private:
	bool isVisible;
};