#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h"
#include <functional>
#include <Const/ConstInfo.h>


USING_NS_CC;

//��ʶҡ����ҡ�˱�����tag

#define TAG_ROCKER 0
#define TAG_ROCKER_BG 1


//��������
class HRocker :public Layer {
	CC_SYNTHESIZE(bool, isCanMove, IsCanMove);
	CC_SYNTHESIZE(float, _angle, Angle);
	
public:
	//����ҡ�ˣ�����ҡ��ͼƬ��ҡ�˱���ͼƬ����ʼ������
	static HRocker* createHRocker
		(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//����ҡ�ˣ���ʾ�����ü���
	void startRocker(bool _isStopOther);
	//ֹͣҡ�ˣ����أ�ȡ������
	void stopRocker();
	ERocker8Direction getRockerDirection()const { return m_direction; }
	ERockerButtonPress getRockerPressButton()const { return m_pressButton; }

	void updatePosition(Point position) { setPosition(position); }

	bool isPressSwitch() {	return m_pressSwitch == true;	}
	bool isPressSkill() { return m_pressLimitBreak == true; }
private:
	EventListenerTouchOneByOne* listener;
	EventListenerKeyboard* listenerKeyboard;
	//�Զ����ʼ��
	void rockerInit
		(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//�����꣨r��angle����ֱ��ת����x��y)
	Point getAnglePosition(float r, float angle);
	//ҡ�˱�������
	Point rockerBGPosition;
	//ҡ�˱����뾶
	float rockerBGRadius;
	//��ȡҡ���������û�������Ƕ�
	float getRad(Point point1, Point point2);

	//�����¼�:
	//���Ĵ����¼�
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//���̵��û��¼�
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, int type);
	virtual bool updateDirection();
	//����
	CREATE_FUNC(HRocker);

	//״̬��
	bool m_upState, m_downState, m_leftState, m_rightState;
	ERocker8Direction m_direction;
	

	bool m_pressAttack, m_pressLimitBreak, m_pressSwitch;

	

	ERockerButtonPress m_pressButton;//��������
	
	
};


#endif