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
	void bindSprite(Sprite* sprite);//绑定精灵对象
	Sprite* getSprite();//获取已经绑定的精灵对象
	void setController(ControllByKeyboard* controller);
	virtual void setTagPosition(int x, int y);
	virtual Point getTagPosition();
	virtual void setFaceDirByMoveDir(int dir);
private:
	Sprite* m_sprite;//绑定的精灵
	ControllByKeyboard* m_controller;
};