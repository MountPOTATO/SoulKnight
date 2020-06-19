#include "Entity/Enemy/Ranger.h"

bool Ranger::init() {
	Sprite* sprite = Sprite::create("Enemy\\Ranger.png");
	this->bindSprite(sprite);
	setAnchorPoint(Point(0.5f, 0.5f));
	setSpeed(RANGER_SPEED);
	setHP(RANGER_HP);
	isAiMoving = false;

	this->isActivated = true;
	this->getSprite()->setVisible(true);//不活跃的怪物先不显示
	this->scheduleUpdate();//开启，如果严重影响帧数就考虑放到怪物活跃时再启用

	return true;
}

 int Ranger::attack() {
	 
}

 void Ranger::calDistance() {
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

 void Ranger::update(float delta) {
	 //移动 
	 auto curPos = this->getPosition();
	 this->calDistance();
	 if (remainMovingDistance > 0) {
		 isAiMoving = true;//进入移动模式
		//进行一次移动
		 remainMovingDistance -= 1;
		 //检测移动路径是否被挡住
		 auto dstPos = Point(0, 0);//先随便生成一个点
		 //计算出终点
		 switch (nextMovingDir)
		 {
		 case left:
			 dstPos = curPos + Point(-RANGER_SPEED, 0);
			 break;
		 case upLeft:
			 dstPos = curPos + Point(-RANGER_SPEED / 1.414, RANGER_SPEED / 1.414);
			 break;
		 case up:
			 dstPos = curPos + Point(0, RANGER_SPEED);
			 break;
		 case upRight:
			 dstPos = curPos + Point(RANGER_SPEED / 1.414, RANGER_SPEED / 1.414);
			 break;
		 case right:
			 dstPos = curPos + Point(RANGER_SPEED, 0);
			 break;
		 case downRight:
			 dstPos = curPos + Point(RANGER_SPEED / 1.414, -RANGER_SPEED / 1.414);
			 break;
		 case down:
			 dstPos = curPos + Point(0, -RANGER_SPEED);
			 break;
		 case downLeft:
			 dstPos = curPos + Point(-RANGER_SPEED / 1.414, -RANGER_SPEED / 1.414);
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
	 }
	 if (remainMovingDistance == 0) { isAiMoving = false; remainMovingDistance = RANGER_MAX_MOVES_ROUND; }
	 return;



	 //攻击
	 //攻击那部分似乎已经写在helloworld里了
 }

 bool Ranger::isPosBlocked(Point dstPos) {

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