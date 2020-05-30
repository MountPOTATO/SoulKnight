#include "HRocker.h"

//TODO:整合常量
#define PRESS 1
#define RELEASE 2

const float PI = 3.14;
HRocker* HRocker::createHRocker(const char* rockerImageName,
								const char* rockerBGImageName,
								Point position) {
	HRocker* layerRocker = HRocker::create();
	if (layerRocker) {
		layerRocker->rockerInit(rockerImageName, rockerBGImageName, position);
		return layerRocker;
	}

	CC_SAFE_DELETE(layerRocker);
	return NULL;
}

//创建摇杆：输入摇杆图片，摇杆背景图片，起始点坐标
void HRocker::rockerInit(const char* rockerImageName,
	const char* rockerBGImageName,
	Point position) {
	//添加摇杆的背景图片,摇杆向轮图片
	//TODO:缺少：攻击，技能，互动键的图片设置
	Sprite* spRocker = Sprite::create(rockerImageName);
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);

	spRocker->setPosition(position);
	spRocker->setVisible(false);
	spRockerBG->setPosition(position);
	spRockerBG->setVisible(false);

	m_pressAttack=m_upState = m_downState = m_leftState = m_rightState = false;
	m_pressAttack = m_pressLimitBreak = m_pressSwitch = false;
	this->addChild(spRocker, 0, TAG_ROCKER);
	this->addChild(spRockerBG, 1, TAG_ROCKER_BG);

	//摇杆向轮透明度设置
	spRocker->setOpacity(240);
	spRockerBG->setOpacity(100);
	//摇杆背景图坐标设置，半径设置
	rockerBGPosition = position;
	rockerBGRadius = spRockerBG->getContentSize().width * 0.4;

	//枚举初始状态(不加，一开始便进入攻击状态
	m_direction = ERocker8Direction::rockerStop;
	m_pressButton = ERockerButtonPress::buttonNone;

	//创建监听器
	listener = EventListenerTouchOneByOne::create();
	listenerKeyboard = EventListenerKeyboard::create();

	//监听事件的绑定
	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);

	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HRocker::onPressKey, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HRocker::onReleaseKey, this);

	listener->setSwallowTouches(true);
}

//启动摇杆，显示，启用监听
void HRocker::startRocker(bool _isStopOther) {
	//精灵获取
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	//精灵可视化
	spRocker->setVisible(true);
	spRockerBG->setVisible(true);

	//TODO:此处完善监听形式
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithFixedPriority(listenerKeyboard, 2);
	//listener待定
}

void HRocker::stopRocker() {
	//精灵获取
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	//精灵隐藏
	spRocker->setVisible(false);
	spRockerBG->setVisible(false);

	//取消监听
	//TODO:后续的完善
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerKeyboard);//？
}

//极坐标（r，angle）的直角转换（x，y)
Point HRocker::getAnglePosition(float r, float angle) {
	return ccp(r * cos(angle), r * sin(angle));
}
float HRocker::getRad(Point point1, Point point2) {
	//获得两点x,y距离
	float xd = point2.x - point1.x;
	float yd = point1.y - point2.y;
	//斜边长度计算
	float hypo = sqrt(pow(xd, 2) + pow(yd, 2));
	//获得余弦值
	float cos = xd / hypo;
	//获得rad
	float rad = acos(cos);
	//取反ss
	if (yd > 0) {
		rad = -rad;
	}
	return rad;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//触碰事件
bool HRocker::onTouchBegan(Touch* touch, Event* event) {
	//获取触屏点坐标与精灵
	Point touchPoint = touch->getLocation();
	Sprite* sprite = (Sprite*)getChildByTag(TAG_ROCKER);

	//判定可移动开关
	if (sprite->boundingBox().containsPoint(touchPoint)) {
		isCanMove = true;
	}

	return true;
}

void HRocker::onTouchMoved(Touch* touch, Event* event) {
	//不可动时判定
	if (!isCanMove) return;
	//获取触屏点坐标与精灵
	Point touchPoint = touch->getLocation();
	Sprite* sprite = (Sprite*)getChildByTag(TAG_ROCKER);

	//角度获取
	_angle = getRad(rockerBGPosition, touchPoint);

	//触碰的界内界外判定与容错设计
	float xd = touchPoint.x - rockerBGPosition.x;
	float yd = touchPoint.y - rockerBGPosition.y;
	//圆心距离
	float r = sqrt(pow(xd, 2) + pow(yd, 2));

	if (r < rockerBGRadius) {
		//如果在界内,向轮移动
		sprite->setPosition(touchPoint);
	}
	else {
		//如果在界外,向轮移动
		Point adjustPoint = ccpAdd
		(getAnglePosition(rockerBGRadius, _angle), ccp(rockerBGPosition.x, rockerBGPosition.y));
		sprite->setPosition(adjustPoint);
	}

}

void HRocker::onTouchEnded(Touch* touch, Event* event) {
	if (!isCanMove) return;
	//精灵获取
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);

	spRocker->stopAllActions();
	//调整
	Point originPosition = spRockerBG->getPosition();
	spRocker->runAction(MoveTo::create(0.02, originPosition));

	//重置可动状态为false
	isCanMove = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////

//键盘输入

bool HRocker::onPressKey(EventKeyboard::KeyCode keyCode, Event* event) {
	updateState(keyCode, PRESS);//PRESS
	//精灵获取
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	spRocker->stopAllActions();
	//修改可移动状态
	isCanMove = true;

	//按下相应指令后向球所在位置
	Point pressPoint;

	//单独考虑没有动时情况
	if (m_direction == ERocker8Direction::rockerStop) {
		isCanMove = false;
		return false;//?
	}

	switch (m_direction) {
		//按上键
	case(ERocker8Direction::rockerUp): {
		//横坐标不动，纵坐标在原来基础上加上半径
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGRadius);
		break;
	}
									   //按下键
	case(ERocker8Direction::rockerDown): {
		//横坐标不动，纵坐标在原来基础上减去半径
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGRadius);
		break;
	}
										 //按左键
	case(ERocker8Direction::rockerLeft): {
		//横坐标在原来基础上减去半径，纵坐标不动
		pressPoint = Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y);
		break;
	}
										 //按右键
	case(ERocker8Direction::rockerRight): {
		//横坐标在原来基础上加上半径，纵坐标不动
		pressPoint = Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y);
		break;
	}
										  //斜向同理
	case(ERocker8Direction::rockerUpLeft): {
		pressPoint =
			Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y + rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerUpRight): {
		pressPoint =
			Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y + rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerDownLeft): {
		pressPoint =
			Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y - rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerDownRight): {
		pressPoint =
			Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y - rockerBGRadius);
		break;
	}
	};

	//更新向轮坐标
	_angle = getRad(rockerBGPosition, pressPoint);
	spRocker->setPosition
	(ccpAdd(getAnglePosition(rockerBGRadius, _angle),
		ccp(rockerBGPosition.x, rockerBGPosition.y)));

	return true;
}

bool HRocker::onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event) {
	updateState(keyCode, RELEASE);//RELEASE
	//判定移动性
	if (!isCanMove) return true;
	//单独考虑没有动时情况
	if (m_direction == ERocker8Direction::rockerStop) {
		//精灵获取
		Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
		Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
		//更新位置
		spRocker->stopAllActions();
		spRocker->runAction(MoveTo::create(0.02, spRockerBG->getPosition()));
		isCanMove = false;
		return true;
	}
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	spRocker->stopAllActions();
	isCanMove = true;

	//按下相应指令后向球所在位置
	Point pressPoint;
	
	switch (m_direction) {
		//按上键
	case(ERocker8Direction::rockerUp): {
		//横坐标不动，纵坐标在原来基础上加上半径
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGRadius);
		break;
	}
									   //按下键
	case(ERocker8Direction::rockerDown): {
		//横坐标不动，纵坐标在原来基础上减去半径
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGRadius);
		break;
	}
										 //按左键
	case(ERocker8Direction::rockerLeft): {
		//横坐标在原来基础上减去半径，纵坐标不动
		pressPoint = Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y);
		break;
	}
										 //按右键
	case(ERocker8Direction::rockerRight): {
		//横坐标在原来基础上加上半径，纵坐标不动
		pressPoint = Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y);
		break;
	}
										  //斜向同理
	case(ERocker8Direction::rockerUpLeft): {
		pressPoint =
			Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y + rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerUpRight): {
		pressPoint =
			Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y + rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerDownLeft): {
		pressPoint =
			Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y - rockerBGRadius);
		break;
	}
	case(ERocker8Direction::rockerDownRight): {
		pressPoint =
			Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y - rockerBGRadius);
		break;
	}
	default:break;
	}
	//更新向轮坐标
	_angle = getRad(rockerBGPosition, pressPoint);
	spRocker->setPosition
	(ccpAdd(getAnglePosition(rockerBGRadius, _angle),
		ccp(rockerBGPosition.x, rockerBGPosition.y)));
	return true;
}

//更新状态
bool HRocker::updateState(EventKeyboard::KeyCode keyCode, int type) {
	//按键指定：
	//TODO:若要开发修改键位系统的话注意修改此处KEY_W,KEY_S,KEY_A,KEY_D
	//相对的键位状态不能同时相同
	switch (keyCode) {
		//未知：检测不到J??
	case(EventKeyboard::KeyCode::KEY_Y): {
		if (type == PRESS) { m_pressAttack = true; }
		else if (type == RELEASE) { m_pressAttack = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_U): {
		if (type == PRESS) { m_pressLimitBreak = true; }
		else if (type == RELEASE) { m_pressLimitBreak = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_I): {
		if (type == PRESS) { m_pressSwitch = true; }
		else if (type == RELEASE) { m_pressSwitch = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_W): {
		if (type == PRESS) { m_upState = true; m_downState = false; }
		else if (type == RELEASE) { m_upState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_S): {
		if (type == PRESS) { m_upState = false; m_downState = true; }
		else if (type == RELEASE) { m_downState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_A): {
		if (type == PRESS) { m_leftState = true; m_rightState = false; }
		else if (type == RELEASE) { m_leftState = false; }
		break;
	}
	case(EventKeyboard::KeyCode::KEY_D): {
		if (type == PRESS) { m_leftState = false; m_rightState = true; }
		else if (type == RELEASE) { m_rightState = false; }
		break;
	}	
	default:break;
	}

	//更新m_direction函数
	updateDirection();
	return true;
}

//更新m_direction函数
bool HRocker::updateDirection() {
	//九个输入枚举的对号入座
	if (m_pressAttack) m_pressButton = ERockerButtonPress::buttonAttack;
	else if (m_pressLimitBreak) m_pressButton = ERockerButtonPress::buttonLimitBreak;
	else if (m_pressSwitch) m_pressButton = ERockerButtonPress::buttonSwitch;
	else m_pressButton = ERockerButtonPress::buttonNone;
	if (m_upState) {
		if (m_leftState) {
			m_direction = ERocker8Direction::rockerUpLeft;
		}
		else if (m_rightState) {
			m_direction = ERocker8Direction::rockerUpRight;
		}
		else {
			m_direction = ERocker8Direction::rockerUp;
		}
	}
	else if (m_downState) {
		if (m_leftState) {
			m_direction = ERocker8Direction::rockerDownLeft;
		}
		else if (m_rightState) {
			m_direction = ERocker8Direction::rockerDownRight;
		}
		else {
			m_direction = ERocker8Direction::rockerDown;
		}
	}
	else {
		if (m_leftState) {
			m_direction = ERocker8Direction::rockerLeft;
		}
		else if (m_rightState) {
			m_direction = ERocker8Direction::rockerRight;
		}
		else {
			m_direction = ERocker8Direction::rockerStop;
		}
	}
	

	return true;
}