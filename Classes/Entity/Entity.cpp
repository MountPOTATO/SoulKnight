#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
}
Entity::~Entity(){}

void Entity::bindSprite(Sprite* sprite) {
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size sizeOfSprite = m_sprite->getContentSize();
	//������ͼƬ��С��70���أ�����ʵ����ײ��40����̫��̱��
	sizeOfSprite.width = 40;
	sizeOfSprite.height = 40;
	m_sprite->setPosition(Point(sizeOfSprite.width * 0.5f, sizeOfSprite.height * 0.5f));//ȷ������ê����ʵ��ê��һ��
	this->setContentSize(sizeOfSprite);//����ʵ��Ĵ�С��Ϊ�뾫���Сһ��

}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}

void Entity::setController(ControllByKeyboard* controller) {
	this->m_controller = controller;
	m_controller->setControllerListener(this);
	

}
Point Entity::getTagPosition() {
	return getPosition();
}

void Entity::setTagPosition(int x, int y) {
	setPosition(Point(x, y));
}

void Entity::setFaceDirByMoveDir(int dir) {
	if (dir == 0) {
		m_sprite->setFlippedX(true);
	}
	else {
		m_sprite->setFlippedX(false);
	}
}