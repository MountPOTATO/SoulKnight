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
	Point pos = m_controllerListener->getTagPosition();
	Point orgPos = pos;
	auto moveLeft = cocos2d::EventKeyboard::KeyCode::KEY_A;
	auto moveRight= cocos2d::EventKeyboard::KeyCode::KEY_D;
	auto moveUp = cocos2d::EventKeyboard::KeyCode::KEY_W;
	auto moveDown = cocos2d::EventKeyboard::KeyCode::KEY_S;
	if (keys[moveLeft]&&keys[moveUp]) {//����
		
		pos.x -= m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//����λ��
		pos.y += m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveRight]&&keys[moveUp]){//����
 		pos.x += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//����λ��
		pos.y += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveRight] && keys[moveDown]) {//����
 		pos.x += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//����λ��
		pos.y -= m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveLeft] && keys[moveDown]) {//����
 		pos.x -= m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//����λ��
		pos.y -= m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveLeft]) {//��
 		pos.x -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveUp]) {//��
 		pos.y += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
 	}
	else if (keys[moveRight]) {//��
 		pos.x += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveDown]) {//��
 		pos.y -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}

	m_controllerListener->setTagPosition(pos.x, pos.y);
	
	//m_controllerListener->setTagPosition(pos.x, pos.y+=2);//�����õ��Զ�������
}

 