#include "ControllerOfEightDir.h"
/*TODO:
���˸�������ƶ�ʵ�֣�
*/

bool ControllerOfEightDir::init() {
	this->m_iSpeed = 0;
	this->scheduleUpdate();
	listenerKey= EventListenerKeyboard::create();
	return true;
}

void ControllerOfEightDir::update(float delta) {
	/*ȷ���Ѿ������˼�������*/
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