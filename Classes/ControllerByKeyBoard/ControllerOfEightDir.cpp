#include "ControllerOfEightDir.h"
#include "math.h"
/*TODO:
���˸�������ƶ�ʵ�֣�
*/

bool ControllerOfEightDir::init() {
	
	this->m_iSpeed = 0;
	this->scheduleUpdate();	
	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event)
	{
		keys[code] = true;//�����и��������£���map�иü���Ӧ��boolֵ����Ϊtrue
	};
	listenerKey->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event)
	{
		keys[code] = false;//�����и������ɿ�����map�иü���Ӧ��boolֵ����Ϊfalse
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
	return true;
}
void ControllerOfEightDir::setiSpeed(int iSpeed) {
	m_iSpeed = iSpeed;
}

void ControllerOfEightDir::update(float delta) {
	/*ȷ���Ѿ������˼�������*/
	if (m_controllerListener == NULL) {
		return;
	}
	auto moveLeft = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
	auto moveRight= cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
	auto moveUp = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
	auto moveDown = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
	if (keys[moveLeft]&&keys[moveUp]) {//����
		Point pos = m_controllerListener->getTagPosition();
		pos.x -= sqrt(m_iSpeed); pos.y += sqrt(m_iSpeed);
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveRight]&&keys[moveUp]){//����
		Point pos = m_controllerListener->getTagPosition();
		pos.x += sqrt(m_iSpeed); pos.y += sqrt(m_iSpeed);
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveRight] && keys[moveDown]) {//����
		Point pos = m_controllerListener->getTagPosition();
		pos.x += sqrt(m_iSpeed); pos.y -= sqrt(m_iSpeed);
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveLeft] && keys[moveDown]) {//����
		Point pos = m_controllerListener->getTagPosition();
		pos.x -= sqrt(m_iSpeed); pos.y -= sqrt(m_iSpeed);
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveLeft]) {//��
		Point pos = m_controllerListener->getTagPosition();
		pos.x -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveUp]) {//��
		Point pos = m_controllerListener->getTagPosition();
		pos.y += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveRight]) {//��
		Point pos = m_controllerListener->getTagPosition();
		pos.x += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	else if (keys[moveDown]) {//��
		Point pos = m_controllerListener->getTagPosition();
		pos.y -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}
	
}