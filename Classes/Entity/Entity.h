#pragma once

#include "cocos2d.h"
USING_NS_CC;
class Entity :public Node {
public:
	CREATE_FUNC(Entity);
	Entity();
	~Entity();

public:
	void bindSprite(Sprite* sprite);//�󶨾������
	Sprite* getSprite();//��ȡ�Ѿ��󶨵ľ������

private:
	Sprite* m_sprite;//�󶨵ľ���
};