#pragma once

#include "cocos2d.h"

USING_NS_CC;

#define pi 3.1415926535

//����������ܰ��� ���ټ��ٴ����ش̣���Ȧ�ȵ�
//���������ͼƬ����

class SpecialEffectArea :public Layer
{
public:
	cocos2d::Scene* createScene();
	bool init();
	CREATE_FUNC(SpecialEffectArea);
public:
	//��ͬ������������⹦��
	//���ټ��ٴ����ش̣���Ȧ��Ҫ�漰��character�࣬�����ı����ǵ�����
	//���ټ��ٴ���Ҫʱ���ʱ����������Ҫlambda����
private:
	//��������
	//����ټ��ٴ����ٶȸı���
	//�ش̺Ͷ�Ȧ�Ŀ�Ѫ
	//����������ʵ��
};