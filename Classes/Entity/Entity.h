#pragma once

#include "cocos2d.h"
#include "ControllerByKeyBoard/ControllerListener.h"
#include "ControllerByKeyBoard/ControllByKeyBoard.h"
#include "Const/ConstInfo.h"
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
	virtual void setFaceDirByMoveDir(int dir);
private:
	Sprite* m_sprite;//�󶨵ľ���
	ControllByKeyboard* m_controller;
};