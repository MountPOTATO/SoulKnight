#pragma once

#include "cocos2d.h"
#include "ControllerListener.h"
#include "ControllByKeyBoard.h"
USING_NS_CC;
class Entity :public Node,public ControllerListener {
public:
	CREATE_FUNC(Entity);
	Entity();
	~Entity();

public:
	void bindSprite(Sprite* sprite);//�󶨾������
	Sprite* getSprite();//��ȡ�Ѿ��󶨵ľ������
	void setController(ControllByKeyboard* controller);
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

private:
	Sprite* m_sprite;//�󶨵ľ���
	ControllByKeyboard* m_controller;
};