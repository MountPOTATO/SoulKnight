#include "Entity/Enemy/Charger.h"


bool Charger::init() {
	Sprite* sprite = Sprite::create("Enemy\\Charger.png");
	this->bindSprite(sprite);
	setAnchorPoint(Point(0.5f, 0.5f));
	setSpeed(CHARGER_SPEED);
	setHP(CHARGER_HP);
	isAiMoving = false;
	m_monsterID = 3;
	isChargeBlocked = false;
	this->isActivated = true;
	this->getSprite()->setVisible(true);//����Ծ�Ĺ����Ȳ���ʾ
	this->scheduleUpdate();//�������������Ӱ��֡���Ϳ��Ƿŵ������Ծʱ������
	remainChargingDistance = CHARGER_MAX_CHARGES_ROUND;
	return true;
}

void Charger::update(float delta) {

	if (remainChargingDistance > 0 && isChargeBlocked == false) {
		isAiMoving = true;
		Point characterPos = m_character->getPosition();
		Point curPos = this->getPosition();//���������λ��
		float x_distance = fabs(characterPos.x - curPos.x);
		float y_distance = fabs(characterPos.y - curPos.y);
		float xy_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
		if (xy_distance <= 1) { return; }
		float x_move = x_distance / xy_distance * CHARGER_CHARGE_SPEED;
		float y_move = y_distance / xy_distance * CHARGER_CHARGE_SPEED;//��������ȡx,y���ƶ�����

		Point dstPos = curPos;
		if (curPos.x <= characterPos.x && curPos.y <= characterPos.y) { dstPos += Point(x_move, y_move); }
		if (curPos.x <= characterPos.x && curPos.y >= characterPos.y) { dstPos += Point(x_move, -y_move); }
		if (curPos.x >= characterPos.x && curPos.y <= characterPos.y) { dstPos += Point(-x_move, y_move); }
		if (curPos.x >= characterPos.x && curPos.y >= characterPos.y) { dstPos += Point(-x_move, -y_move); }

		//����Ƿ��ϰ����ڵ�
		auto x = dstPos.x;
		auto y = dstPos.y;
		if (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))) {
			isAiMoving = false; isChargeBlocked = true;
		}
		if (isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))) {
			isAiMoving = false; isChargeBlocked = true;
		}
		if (isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))) {
			isAiMoving = false; isChargeBlocked = true;
		}
		if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) {
			isAiMoving = false; isChargeBlocked = true;
		}
		if (!isChargeBlocked) {
			auto pos = tileCoordForPosition(curPos);
			auto mapSize = m_map->getMapSize();

			this->setPositionZ(pos.y - mapSize.height);

			Entity::setTagPosition(x, y);
			remainChargingDistance -= 1;
			if (remainChargingDistance == 0) {
				remainChargingDistance = CHARGER_MAX_CHARGES_ROUND;
				isChargeBlocked = true;
				isAiMoving = false;
			}
			return;
		}

	}
	if (!isAiMoving) { this->calDistance(); isAiMoving = true; }
	if (isChargeBlocked) {
		//�����
		if (max_twist > 0) {

			auto curPos = this->getPosition();

			if (remainMovingDistance > 0) {
				isAiMoving = true;//�����ƶ�ģʽ
			   //����һ���ƶ�

				//����ƶ�·���Ƿ񱻵�ס
				auto dstPos = Point(0, 0);//���������һ����
				//������յ�
				switch (nextMovingDir)
				{
				case left:
					dstPos = curPos + Point(-CHARGER_SPEED, 0);
					break;
				case upLeft:
					dstPos = curPos + Point(-CHARGER_SPEED / 1.414, CHARGER_SPEED / 1.414);
					break;
				case up:
					dstPos = curPos + Point(0, CHARGER_SPEED);
					break;
				case upRight:
					dstPos = curPos + Point(CHARGER_SPEED / 1.414, CHARGER_SPEED / 1.414);
					break;
				case right:
					dstPos = curPos + Point(CHARGER_SPEED, 0);
					break;
				case downRight:
					dstPos = curPos + Point(CHARGER_SPEED / 1.414, -CHARGER_SPEED / 1.414);
					break;
				case down:
					dstPos = curPos + Point(0, -CHARGER_SPEED);
					break;
				case downLeft:
					dstPos = curPos + Point(-CHARGER_SPEED / 1.414, -CHARGER_SPEED / 1.414);
					break;
				default:
					break;
				}
				auto x = dstPos.x;
				auto y = dstPos.y;
				if (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))) { isAiMoving = false; return; }
				if (isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))) { isAiMoving = false; return; }
				if (isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))) { isAiMoving = false; return; }
				if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) { isAiMoving = false; return; }//�ƶ�·�����赲�� �����ж�
				auto pos = tileCoordForPosition(curPos);
				auto mapSize = m_map->getMapSize();

				this->setPositionZ(pos.y - mapSize.height);

				Entity::setTagPosition(x, y);
				remainMovingDistance -= 1;

			}
			if (remainMovingDistance == 0) {
				//��������һ��������ƶ��ٽ�����һ�γ�ײ
				max_twist -= 1; this->calDistance();
				remainMovingDistance = CHARGER_MAX_MOVES_ROUND;
			}
		}
		if (max_twist == 0) {
			max_twist = 3; isChargeBlocked = false;

		}
	}


}

bool Charger::isPosBlocked(Point dstPos) {

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
void Charger::calDistance() {
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

	nextMovingDistance = (int)(CHARGER_MAX_MOVES_ROUND * CCRANDOM_0_1() + 1);//���ɽ���1-3������


}