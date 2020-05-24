#include "Entity.h"

Entity::Entity() {
	m_sprite = NULL;
}
Entity::~Entity(){}

void Entity::bindSprite(Sprite* sprite) {
	this->m_sprite = sprite;
	this->addChild(m_sprite);

	Size sizeOfSprite = m_sprite->getContentSize();
	m_sprite->setPosition(Point(sizeOfSprite.width * 0.5f, sizeOfSprite.height * 0.5f));//ȷ������ê����ʵ��ê��һ��
	this->setContentSize(sizeOfSprite);//����ʵ��Ĵ�С��Ϊ�뾫���Сһ��

}

Sprite* Entity::getSprite() {
	return this->m_sprite;
}