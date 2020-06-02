#include "Character.h"

Character::Character() {}
Character::~Character() {}



bool Character::init() {
	m_HP = 1;
	m_MP = 1;
	m_Armor = 1;
	m_Speed = 2;
	setAnchorPoint(Point(0.5f, 0.5f));

	
	
	return true;
}





//������ά
void Character::setHP(int hp) {
	m_HP = hp;
}
void Character::setMP(int mp) {
	m_MP = mp;
}
void Character::setArmor(int armor) {
	m_Armor = armor;
}
void Character::setSpeed(int speed) {//���ý�ɫ�ٶ�
	m_Speed = speed;
	 
}
void Character::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}
//
int Character::getHP() { return m_HP; }
int Character::getMP() { return m_MP; }
int Character::getArmor() { return m_Armor; }
int Character::getSpeed() { return m_Speed; }

//�����Ϊ���������ӽ�
void Character::setViewPointByCharacter() {
	if (getSprite() == NULL) { return; }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* parent = (Layer*)getParent();//
	Point characterPos = getPosition();//��ȡ��������
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPos = centerPos - characterPos;
	parent->setPosition(viewPos);

}

void Character::setTagPosition(int x, int y) {
	if (isPosBlocked(Point(x, y))) { return; }

	Entity::setTagPosition(x, y);
	setViewPointByCharacter();
}

bool Character::isPosBlocked(Point dstPos) {
	int dir;
	Point curPos=this->getPosition();
	if ((dstPos.x - curPos.x) < 0) { dir = 1; }
	else if ((dstPos.y - curPos.y) > 0) { dir = 2; }
	else if ((dstPos.x - curPos.x) > 0) { dir = 3; }
	else if ((dstPos.y - curPos.y) < 0) { dir = 4; }
	else { dir = 0; }
	switch (dir)
	{
	case 1:
		dstPos.x -= 20;
		break;
	case 2:
		dstPos.y += 20;
		break;
	case 3:
		dstPos.x += 20;
		break;
	case 4:
		dstPos.y -= 20;
		break;
	case 0:
		break;
	default:
		break;
	}
	//��ȱ
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	int tiledGid = meta->getTileGIDAt(tiledPos);//��ȡ������ӵ�Ψһ��ʶ
	
												
	//�ж���������Ƿ����
	if (tiledGid != 0) {
		 
	auto propMap = m_map->getPropertiesForGID(tiledGid).asValueMap();


		

		if (propMap.find("Collidable") != propMap.end()) {
			//��ȡ���ӵ�Collidable����
			Value prop = propMap.at("Collidable");
			if (prop.asString().compare("true") == 0) {
				//���������������Ϊtrue��������Ҽ����ƶ�
				return true;
			}
		}
		 
	}
	return false;//��֮������false
}

Point Character::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;

	 
	return Point(x, y);
}