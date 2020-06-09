#include "ControllerOfEightDir.h"
#include "math.h"
/*TODO:
将八个方向的移动实现；
*/

bool ControllerOfEightDir::init() {
	
	this->m_iSpeed = 0;
	this->scheduleUpdate();	
	auto listenerKey = EventListenerKeyboard::create();
	listenerKey->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event)
	{
		keys[code] = true;//发现有个键被按下，将map中该键对应的bool值更新为true
	};
	listenerKey->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event)
	{
		keys[code] = false;//发现有个键被松开，将map中该键对应的bool值更新为false
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
	return true;
}
void ControllerOfEightDir::setiSpeed(int iSpeed) {
	m_iSpeed = iSpeed;
}

void ControllerOfEightDir::update(float delta) {
	/*确定已经设置了监听对象*/
	
	if (m_controllerListener == NULL) {
		return;
	}
	Point pos = m_controllerListener->getTagPosition();
	Point orgPos = pos;
	auto moveLeft = cocos2d::EventKeyboard::KeyCode::KEY_A;
	auto moveRight= cocos2d::EventKeyboard::KeyCode::KEY_D;
	auto moveUp = cocos2d::EventKeyboard::KeyCode::KEY_W;
	auto moveDown = cocos2d::EventKeyboard::KeyCode::KEY_S;
	if (keys[moveLeft]&&keys[moveUp]) {//左上
		
		pos.x -= m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//更新位置
		pos.y += m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveRight]&&keys[moveUp]){//右上
 		pos.x += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//更新位置
		pos.y += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveRight] && keys[moveDown]) {//右下
 		pos.x += m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//更新位置
		pos.y -= m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveLeft] && keys[moveDown]) {//左下
 		pos.x -= m_iSpeed / 1.414; m_controllerListener->setTagPosition(pos.x, pos.y);
		pos = m_controllerListener->getTagPosition();//更新位置
		pos.y -= m_iSpeed / 1.414;m_controllerListener->setTagPosition(pos.x, pos.y);
		
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveLeft]) {//左
 		pos.x -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
		m_controllerListener->setFaceDirByMoveDir(0);
 	}
	else if (keys[moveUp]) {//上
 		pos.y += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
 	}
	else if (keys[moveRight]) {//右
 		pos.x += m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
		m_controllerListener->setFaceDirByMoveDir(1);
 	}
	else if (keys[moveDown]) {//下
 		pos.y -= m_iSpeed;
		m_controllerListener->setTagPosition(pos.x, pos.y);
	}

	m_controllerListener->setTagPosition(pos.x, pos.y);
	
	//m_controllerListener->setTagPosition(pos.x, pos.y+=2);//测试用的自动往上走
}

 