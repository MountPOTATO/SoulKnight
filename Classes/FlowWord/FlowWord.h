#pragma once

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node {
public:
    CREATE_FUNC(FlowWord);
    virtual bool init();

public:
	void showWord(const char* text, Point pos);//��������Ʈ�֣�(�ı���λ�ã�
private:
	Label* m_textLab;
};

