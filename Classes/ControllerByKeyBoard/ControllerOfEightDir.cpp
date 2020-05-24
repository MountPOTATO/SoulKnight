#include "ControllerOfEightDir.h"
/*TODO:
将八个方向的移动实现；
*/

bool ControllerOfEightDir::init() {
	this->m_iSpeed = 0;
	this->scheduleUpdate();
	listenerKey= EventListenerKeyboard::create();
	return true;
}

void ControllerOfEightDir::update(float delta) {
	/*确定已经设置了监听对象*/
	if (m_controllerListener == NULL) {
		return;
	}
	listenerKey->onKeyPressed = ([=](EventKeyboard::KeyCode code, Event* event)
	{
		switch (code)
		{
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
			log("Down Arrow");
			break;
		}
		default:
			break;
		}
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKey, this);
}