#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TransferPortal :public Layer
{
public:
	static Scene* createScene();
	bool init();                     //��ʼ�������ţ�ʵ�ֶ���Ч��
	CREATE_FUNC(TransferPortal);
	bool isToPushScene();            //�ж��Ƿ�Ҫ�л�����
	bool isColliedWithCharacter();
	
	//�ж��Ƿ񴴽������ţ���Ҫ�������������ʵ��


//public:
//	static Layer* layer;
};