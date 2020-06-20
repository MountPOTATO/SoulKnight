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
	this->getSprite()->setVisible(true);//不活跃的怪物先不显示
	this->scheduleUpdate();//开启，如果严重影响帧数就考虑放到怪物活跃时再启用
	remainChargingDistance = CHARGER_MAX_CHARGES_ROUND;
	return true;
}

void Charger::update(float delta) {

	if (remainChargingDistance > 0 && isChargeBlocked == false) {
		isAiMoving = true;
		Point characterPos = m_character->getPosition();
		Point curPos = this->getPosition();//怪物自身的位置
		float x_distance = fabs(characterPos.x - curPos.x);
		float y_distance = fabs(characterPos.y - curPos.y);
		float xy_distance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
		if (xy_distance <= 1) { return; }
		float x_move = x_distance / xy_distance * CHARGER_CHARGE_SPEED;
		float y_move = y_distance / xy_distance * CHARGER_CHARGE_SPEED;//按比例获取x,y的移动距离

		Point dstPos = curPos;
		if (curPos.x <= characterPos.x && curPos.y <= characterPos.y) { dstPos += Point(x_move, y_move); }
		if (curPos.x <= characterPos.x && curPos.y >= characterPos.y) { dstPos += Point(x_move, -y_move); }
		if (curPos.x >= characterPos.x && curPos.y <= characterPos.y) { dstPos += Point(-x_move, y_move); }
		if (curPos.x >= characterPos.x && curPos.y >= characterPos.y) { dstPos += Point(-x_move, -y_move); }

		//检查是否被障碍物遮挡
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
		//随机走
		if (max_twist > 0) {

			auto curPos = this->getPosition();

			if (remainMovingDistance > 0) {
				isAiMoving = true;//进入移动模式
			   //进行一次移动

				//检测移动路径是否被挡住
				auto dstPos = Point(0, 0);//先随便生成一个点
				//计算出终点
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
				if (isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox))) { isAiMoving = false; return; }//移动路径被阻挡了 不能行动
				auto pos = tileCoordForPosition(curPos);
				auto mapSize = m_map->getMapSize();

				this->setPositionZ(pos.y - mapSize.height);

				Entity::setTagPosition(x, y);
				remainMovingDistance -= 1;

			}
			if (remainMovingDistance == 0) {
				//必须走完一整条随机移动再进行下一次冲撞
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

	//暂缺*/
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));

	int tiledGid = meta->getTileGIDAt(tiledPos);//获取这个格子的唯一标识



	//判断这个格子是否存在
	if (tiledGid != 0) {

		auto propMap = m_map->getPropertiesForGID(tiledGid).asValueMap();




		if (propMap.find("Collidable") != propMap.end()) {
			//获取格子的Collidable属性
			Value prop = propMap.at("Collidable");
			if (prop.asString().compare("true") == 0) {
				//发现这个格子属性为true，不让玩家继续移动
				return true;
			}
		}

	}
	return false;//反之，返回false
}
void Charger::calDistance() {
	if (isAiMoving == true) { return; }//如果正在执行上一个移动指令，就不要重复移动了
	auto dir = (int)(8 * CCRANDOM_0_1());//随机生成0-7
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
	}//储存对应的八向

	nextMovingDistance = (int)(CHARGER_MAX_MOVES_ROUND * CCRANDOM_0_1() + 1);//生成介于1-3的整数


}