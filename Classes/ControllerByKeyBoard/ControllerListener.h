#pragma once

#include "cocos2d.h"
USING_NS_CC;
class ControllerListener {
public:
	/*����Ŀ��λ��*/
	virtual void setTagPosition(int x, int y) = 0;

	/*��ȡĿ��λ��*/
	virtual Point getTagPosition() = 0;
	
	/*�����ƶ���������ͼƬ����,0Ϊ�� 1Ϊ��*/
	virtual void setFaceDirByMoveDir(int dir)=0;
};
