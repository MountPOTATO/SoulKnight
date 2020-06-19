#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"

class HelloWorld;



class Charger :public Monster {
public:
	CREATE_FUNC(Charger);
	virtual bool init();
	void update(float delta);
public:
	void chargeTowardsPos(Point dstPos);//��ĳ��������ٳ��
	void calDistance();//�����ƶ�
	bool isAiMoving;//�Ƿ����������ƶ�
	bool isPosBlocked(Point dstPos);


public:
	MovingDir nextMovingDir;//���浱ǰ�ƶ�����
	int nextMovingDistance;//Ԥ�Ƶ�����ƶ�����
	int remainChargingDistance;
	int remainMovingDistance;


private:
	int monsterID = 1;//����Ϊ��ʶ
	int _HP;
	int _Speed;
};