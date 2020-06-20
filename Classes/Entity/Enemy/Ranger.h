#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
class HelloWorld;



class Ranger :public Monster {
public:
	CREATE_FUNC(Ranger);
	virtual bool init();
	void update(float delta);
public:
	int attack();
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