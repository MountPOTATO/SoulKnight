#pragma once

#include "cocos2d.h"

USING_NS_CC;

// ��������������ţ����䣬��ӣ���buff�ȵ�
// �����źͱ����ͼƬ���У���Ӻ�buffͼƬ���ޣ�

class InterContent :public Layer
{
public:
	static cocos2d::Scene* createScene();  //���ԣ�֮���滻Ϊʵ�ʵ�ͼ
	virtual bool init();
	CREATE_FUNC(InterContent);
public:
	//���̼����¼��������Ƿ�Խ����������Ӧ
	//��̬Ч���������źͱ����ڽ�������������
private:                                   //����������ԣ�������ܻ��
};