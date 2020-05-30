#include "HRocker.h"

//TODO:���ϳ���
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

//����ҡ�ˣ�����ҡ��ͼƬ��ҡ�˱���ͼƬ����ʼ������
void HRocker::rockerInit(const char* rockerImageName,
	const char* rockerBGImageName,
	Point position) {
	//���ҡ�˵ı���ͼƬ,ҡ������ͼƬ
	//TODO:ȱ�٣����������ܣ���������ͼƬ����
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

	//ҡ������͸��������
	spRocker->setOpacity(240);
	spRockerBG->setOpacity(100);
	//ҡ�˱���ͼ�������ã��뾶����
	rockerBGPosition = position;
	rockerBGRadius = spRockerBG->getContentSize().width * 0.4;

	//ö�ٳ�ʼ״̬(���ӣ�һ��ʼ����빥��״̬
	m_direction = ERocker8Direction::rockerStop;
	m_pressButton = ERockerButtonPress::buttonNone;

	//����������
	listener = EventListenerTouchOneByOne::create();
	listenerKeyboard = EventListenerKeyboard::create();

	//�����¼��İ�
	listener->onTouchBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);

	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(HRocker::onPressKey, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(HRocker::onReleaseKey, this);

	listener->setSwallowTouches(true);
}

//����ҡ�ˣ���ʾ�����ü���
void HRocker::startRocker(bool _isStopOther) {
	//�����ȡ
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	//������ӻ�
	spRocker->setVisible(true);
	spRockerBG->setVisible(true);

	//TODO:�˴����Ƽ�����ʽ
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithFixedPriority(listenerKeyboard, 2);
	//listener����
}

void HRocker::stopRocker() {
	//�����ȡ
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	//��������
	spRocker->setVisible(false);
	spRockerBG->setVisible(false);

	//ȡ������
	//TODO:����������
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listenerKeyboard);//��
}

//�����꣨r��angle����ֱ��ת����x��y)
Point HRocker::getAnglePosition(float r, float angle) {
	return ccp(r * cos(angle), r * sin(angle));
}
float HRocker::getRad(Point point1, Point point2) {
	//�������x,y����
	float xd = point2.x - point1.x;
	float yd = point1.y - point2.y;
	//б�߳��ȼ���
	float hypo = sqrt(pow(xd, 2) + pow(yd, 2));
	//�������ֵ
	float cos = xd / hypo;
	//���rad
	float rad = acos(cos);
	//ȡ��ss
	if (yd > 0) {
		rad = -rad;
	}
	return rad;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//�����¼�
bool HRocker::onTouchBegan(Touch* touch, Event* event) {
	//��ȡ�����������뾫��
	Point touchPoint = touch->getLocation();
	Sprite* sprite = (Sprite*)getChildByTag(TAG_ROCKER);

	//�ж����ƶ�����
	if (sprite->boundingBox().containsPoint(touchPoint)) {
		isCanMove = true;
	}

	return true;
}

void HRocker::onTouchMoved(Touch* touch, Event* event) {
	//���ɶ�ʱ�ж�
	if (!isCanMove) return;
	//��ȡ�����������뾫��
	Point touchPoint = touch->getLocation();
	Sprite* sprite = (Sprite*)getChildByTag(TAG_ROCKER);

	//�ǶȻ�ȡ
	_angle = getRad(rockerBGPosition, touchPoint);

	//�����Ľ��ڽ����ж����ݴ����
	float xd = touchPoint.x - rockerBGPosition.x;
	float yd = touchPoint.y - rockerBGPosition.y;
	//Բ�ľ���
	float r = sqrt(pow(xd, 2) + pow(yd, 2));

	if (r < rockerBGRadius) {
		//����ڽ���,�����ƶ�
		sprite->setPosition(touchPoint);
	}
	else {
		//����ڽ���,�����ƶ�
		Point adjustPoint = ccpAdd
		(getAnglePosition(rockerBGRadius, _angle), ccp(rockerBGPosition.x, rockerBGPosition.y));
		sprite->setPosition(adjustPoint);
	}

}

void HRocker::onTouchEnded(Touch* touch, Event* event) {
	if (!isCanMove) return;
	//�����ȡ
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);

	spRocker->stopAllActions();
	//����
	Point originPosition = spRockerBG->getPosition();
	spRocker->runAction(MoveTo::create(0.02, originPosition));

	//���ÿɶ�״̬Ϊfalse
	isCanMove = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////

//��������

bool HRocker::onPressKey(EventKeyboard::KeyCode keyCode, Event* event) {
	updateState(keyCode, PRESS);//PRESS
	//�����ȡ
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	spRocker->stopAllActions();
	//�޸Ŀ��ƶ�״̬
	isCanMove = true;

	//������Ӧָ�����������λ��
	Point pressPoint;

	//��������û�ж�ʱ���
	if (m_direction == ERocker8Direction::rockerStop) {
		isCanMove = false;
		return false;//?
	}

	switch (m_direction) {
		//���ϼ�
	case(ERocker8Direction::rockerUp): {
		//�����겻������������ԭ�������ϼ��ϰ뾶
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGRadius);
		break;
	}
									   //���¼�
	case(ERocker8Direction::rockerDown): {
		//�����겻������������ԭ�������ϼ�ȥ�뾶
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGRadius);
		break;
	}
										 //�����
	case(ERocker8Direction::rockerLeft): {
		//��������ԭ�������ϼ�ȥ�뾶�������겻��
		pressPoint = Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y);
		break;
	}
										 //���Ҽ�
	case(ERocker8Direction::rockerRight): {
		//��������ԭ�������ϼ��ϰ뾶�������겻��
		pressPoint = Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y);
		break;
	}
										  //б��ͬ��
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

	//������������
	_angle = getRad(rockerBGPosition, pressPoint);
	spRocker->setPosition
	(ccpAdd(getAnglePosition(rockerBGRadius, _angle),
		ccp(rockerBGPosition.x, rockerBGPosition.y)));

	return true;
}

bool HRocker::onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event) {
	updateState(keyCode, RELEASE);//RELEASE
	//�ж��ƶ���
	if (!isCanMove) return true;
	//��������û�ж�ʱ���
	if (m_direction == ERocker8Direction::rockerStop) {
		//�����ȡ
		Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
		Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
		//����λ��
		spRocker->stopAllActions();
		spRocker->runAction(MoveTo::create(0.02, spRockerBG->getPosition()));
		isCanMove = false;
		return true;
	}
	Sprite* spRocker = (Sprite*)getChildByTag(TAG_ROCKER);
	Sprite* spRockerBG = (Sprite*)getChildByTag(TAG_ROCKER_BG);
	spRocker->stopAllActions();
	isCanMove = true;

	//������Ӧָ�����������λ��
	Point pressPoint;
	
	switch (m_direction) {
		//���ϼ�
	case(ERocker8Direction::rockerUp): {
		//�����겻������������ԭ�������ϼ��ϰ뾶
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y + rockerBGRadius);
		break;
	}
									   //���¼�
	case(ERocker8Direction::rockerDown): {
		//�����겻������������ԭ�������ϼ�ȥ�뾶
		pressPoint = Point(rockerBGPosition.x, rockerBGPosition.y - rockerBGRadius);
		break;
	}
										 //�����
	case(ERocker8Direction::rockerLeft): {
		//��������ԭ�������ϼ�ȥ�뾶�������겻��
		pressPoint = Point(rockerBGPosition.x - rockerBGRadius, rockerBGPosition.y);
		break;
	}
										 //���Ҽ�
	case(ERocker8Direction::rockerRight): {
		//��������ԭ�������ϼ��ϰ뾶�������겻��
		pressPoint = Point(rockerBGPosition.x + rockerBGRadius, rockerBGPosition.y);
		break;
	}
										  //б��ͬ��
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
	//������������
	_angle = getRad(rockerBGPosition, pressPoint);
	spRocker->setPosition
	(ccpAdd(getAnglePosition(rockerBGRadius, _angle),
		ccp(rockerBGPosition.x, rockerBGPosition.y)));
	return true;
}

//����״̬
bool HRocker::updateState(EventKeyboard::KeyCode keyCode, int type) {
	//����ָ����
	//TODO:��Ҫ�����޸ļ�λϵͳ�Ļ�ע���޸Ĵ˴�KEY_W,KEY_S,KEY_A,KEY_D
	//��Եļ�λ״̬����ͬʱ��ͬ
	switch (keyCode) {
		//δ֪����ⲻ��J??
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

	//����m_direction����
	updateDirection();
	return true;
}

//����m_direction����
bool HRocker::updateDirection() {
	//�Ÿ�����ö�ٵĶԺ�����
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