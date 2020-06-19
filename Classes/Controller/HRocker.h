#ifndef __HROCKER_H__
#define __HROCKER_H__

#include "cocos2d.h"
#include <functional>
#include <Const/ConstInfo.h>


USING_NS_CC;

//标识摇杆与摇杆背景的tag

#define TAG_ROCKER 0
#define TAG_ROCKER_BG 1


//控制器类
class HRocker :public Layer {
	CC_SYNTHESIZE(bool, isCanMove, IsCanMove);
	CC_SYNTHESIZE(float, _angle, Angle);
	
public:
	//创建摇杆：输入摇杆图片，摇杆背景图片，起始点坐标
	static HRocker* createHRocker
		(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//启动摇杆，显示，启用监听
	void startRocker(bool _isStopOther);
	//停止摇杆，隐藏，取消监听
	void stopRocker();
	ERocker8Direction getRockerDirection()const { return m_direction; }
	ERockerButtonPress getRockerPressButton()const { return m_pressButton; }

	void updatePosition(Point position) { setPosition(position); }

	bool isPressSwitch() {	return m_pressSwitch == true;	}
	bool isPressSkill() { return m_pressLimitBreak == true; }
private:
	EventListenerTouchOneByOne* listener;
	EventListenerKeyboard* listenerKeyboard;
	//自定义初始化
	void rockerInit
		(const char* rockerImageName, const char* rockerBGImageName, Point position);
	//极坐标（r，angle）的直角转换（x，y)
	Point getAnglePosition(float r, float angle);
	//摇杆背景坐标
	Point rockerBGPosition;
	//摇杆背景半径
	float rockerBGRadius;
	//获取摇杆坐标与用户触屏点角度
	float getRad(Point point1, Point point2);

	//输入事件:
	//鼠标的触屏事件
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//键盘的敲击事件
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* envet);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, int type);
	virtual bool updateDirection();
	//生成
	CREATE_FUNC(HRocker);

	//状态栏
	bool m_upState, m_downState, m_leftState, m_rightState;
	ERocker8Direction m_direction;
	

	bool m_pressAttack, m_pressLimitBreak, m_pressSwitch;

	

	ERockerButtonPress m_pressButton;//按键输入
	
	
};


#endif