#pragma once

#include "cocos2d.h"
USING_NS_CC;

class FlowWord : public Node {
public:
    CREATE_FUNC(FlowWord);
    virtual bool init();

public:
	void showWord(const char* text, Point pos);//用于生成飘字，(文本，位置）
private:
	Label* m_textLab;
};

