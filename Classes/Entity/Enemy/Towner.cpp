#include "Entity/Enemy/Tower.h"
#include "LongRangeAttack/Bullet.h"
#include "Const/ConstInfo.h"
#include "HelloWorldScene.h"

float MyMathGetRad(Point point1, Point point2);

bool Tower::init() {
	Sprite* sprite = Sprite::create("Enemy\\Tower.png");
	this->bindSprite(sprite);
	setAnchorPoint(Point(0.5f, 0.5f));
	setSpeed(TOWER_SPEED);
	setHP(TOWER_HP);
	isAiMoving = false;
	m_monsterID = 2;
	this->isActivated = true;
	this->getSprite()->setVisible(true);//����Ծ�Ĺ����Ȳ���ʾ
	this->scheduleUpdate();//�������������Ӱ��֡���Ϳ��Ƿŵ������Ծʱ������

	return true;
}


void Tower::calDistance() {
	if (isAiMoving == true) { return; }//�������ִ����һ���ƶ�ָ��Ͳ�Ҫ�ظ��ƶ���
	auto dir = (int)(8 * CCRANDOM_0_1());//�������0-7
	log("%f", dir);
	switch (dir)
	{
	case 0:
		nextMovingDir = left;
		break;
	case 1:
		nextMovingDir = upLeft;
		break;
	case 2:
		nextMovingDir = up;
		break;
	case 3:
		nextMovingDir = upRight;
		break;
	case 4:
		nextMovingDir = right;
		break;
	case 5:
		nextMovingDir = downRight;
		break;
	case 6:
		nextMovingDir = down;
		break;
	case 7:
		nextMovingDir = downLeft;
		break;
	}//�����Ӧ�İ���

	nextMovingDistance = (int)(RANGER_MAX_MOVES_ROUND * CCRANDOM_0_1() + 1);//���ɽ���1-3������

}


void Tower::update(float delta) {
	
}

bool Tower::isPosBlocked(Point dstPos) {

	//��ȱ*/
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

