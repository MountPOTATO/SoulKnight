#pragma once

#include "Entity/Monster.h"
#include "cocos2d.h"

#include "Const/ConstInfo.h"

class HelloWorld;



class Mummy :public Monster {
public:
	CREATE_FUNC(Mummy);
	virtual bool init();
	void update(float delta);
public:
	void chargeTowardsPos(Point dstPos);//��ĳ��������ٳ��
	void calDistance();//�����ƶ�
	bool isAiMoving;//�Ƿ����������ƶ�
	bool isPosBlocked(Point dstPos);
	int max_twist = 3;

public:
	MovingDir nextMovingDir;//���浱ǰ�ƶ�����
	int nextMovingDistance;//Ԥ�Ƶ�����ƶ�����
	int remainChargingDistance;
	int remainMovingDistance;
	bool isChargeBlocked;

private:
	int monsterID = 2;//����Ϊ��ʶ
	int _HP;
	int _Speed;
};