#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Entity;
class HelloWorld;
//PickThingΪʰȡ���ߣ�ʰȡ���߰�����������ƿ����ƿ

class DirectPickThing :public Node
{
	CC_SYNTHESIZE(float, _stickRange,StickRange); //�������վ���
	CC_SYNTHESIZE(INT32, _generateRange, GenerateRange);//������ɾ���ķ�Χ

	CC_SYNTHESIZE(INT32, _blueNumber, BlueNumber); //���ĸ���
	CC_SYNTHESIZE(INT32, _coinNumber, CoinNumber); //Ǯ�ҵĸ���

	CC_SYNTHESIZE(HelloWorld*, _pickThingScene, PickThingScene);//����

	CC_SYNTHESIZE(Entity*, _hero, Hero);//�����Ӣ��

public:
	

	static DirectPickThing* create(Point position, Entity* hero, float stickRange,
		 int blueNumber,int coinNumber, int generateRange, HelloWorld* helloWorldScene);


	virtual bool init(Point position, Entity* hero, float stickRange,
		int blueNumber, int coinNumber, int generateRange, HelloWorld* helloWorldScene);

	void updatePickThingSprite();

	//�����¼����� δʵ��
	//����ʰȡ���ߺ�״̬�ĸı䣬��Ҫcharater��Ĺ���

	
};