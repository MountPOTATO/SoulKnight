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
	this->getSprite()->setVisible(true);//不活跃的怪物先不显示
	this->scheduleUpdate();//开启，如果严重影响帧数就考虑放到怪物活跃时再启用

	return true;
}


void Tower::calDistance() {
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

	nextMovingDistance = (int)(RANGER_MAX_MOVES_ROUND * CCRANDOM_0_1() + 1);//生成介于1-3的整数

}


void Tower::update(float delta) {
	
}

bool Tower::isPosBlocked(Point dstPos) {

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

