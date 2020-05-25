#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
}
Entity::~Entity(){}

void Entity::bindSprite(Sprite* sprite) {
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size sizeOfSprite = m_sprite->getContentSize();
	m_sprite->setPosition(Point(sizeOfSprite.width * 0.5f, sizeOfSprite.height * 0.5f));//确保精灵锚点与实体锚点一致
	this->setContentSize(sizeOfSprite);//将该实体的大小改为与精灵大小一致

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