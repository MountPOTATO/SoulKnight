#include "FlowWord.h"

bool FlowWord::init() 
{
	m_textLab = Label::create("", "Arial", 20);
	m_textLab->setColor(ccc3(255, 0, 0));
	m_textLab->setAnchorPoint(ccp(1, 0));
	m_textLab->setVisible(false);

	this->addChild(m_textLab);
	return true;
}

void FlowWord::showWord( const char* text, Point pos ) 
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* ��������������Ŵ����С */
	auto moveUp = MoveBy::create(0.7f, Point(0, 20));
	auto sineEase = EaseExponentialOut::create(moveUp);//������һ���Ч��

    auto callFunc = CallFunc::create([&](){
        /* �����������Ӹ��ڵ���ɾ������ */
        m_textLab->setVisible(false);
        m_textLab->removeFromParentAndCleanup(true);
    });

    auto actions = Sequence::create(sineEase, callFunc, NULL);

	m_textLab->runAction(actions);
}


