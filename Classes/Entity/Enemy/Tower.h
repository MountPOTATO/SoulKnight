#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
#include "Const/ConstInfo.h"
class HelloWorld;


class Tower :public Monster {
public:
	CREATE_FUNC(Tower);
	virtual bool init();
	void update(float delta);
public:


	void calDistance();//�����ƶ�
	bool isAiMoving;//�Ƿ����������ƶ�
	bool isPosBlocked(Point dstPos);


public:

	MovingDir nextMovingDir;//���浱ǰ�ƶ�����
	int nextMovingDistance;//Ԥ�Ƶ�����ƶ�����
	int remainMovingDistance;//ʣ���ƶ�����

private:
	int monsterID = 1;//����Ϊ��ʶ
	int _HP;
	int _Speed;

};