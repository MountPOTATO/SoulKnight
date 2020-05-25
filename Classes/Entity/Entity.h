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
	void bindSprite(Sprite* sprite);//绑定精灵对象
	Sprite* getSprite();//获取已经绑定的精灵对象
	void setController(ControllByKeyboard* controller);
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();

private:
	Sprite* m_sprite;//绑定的精灵
	ControllByKeyboard* m_controller;
};