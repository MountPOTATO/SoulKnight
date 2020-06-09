#include "Character.h"

Character::Character() {}
Character::~Character() {}



bool Character::init() {
	max_HP = 1; max_MP = 1; max_Armor = 1;
	m_HP = max_HP;
	m_MP = max_MP;
	m_Armor = max_Armor;
	m_Speed = 1;
	m_Weapon1 = NULL;
	m_Weapon2 = NULL;
	isInvincible = false;
	isKnockBack = false;
	setAnchorPoint(Point(0.5f, 0.5f));
	this->scheduleUpdate();
	
	
	return true;
}





//设置四维
void Character::setHP(int hp) {
	m_HP = hp;
}
void Character::setMP(int mp) {
	m_MP = mp;
}
void Character::setArmor(int armor) {
	m_Armor = armor;
}
void Character::setSpeed(int speed) {//设置角色速度
	m_Speed = speed;
	 
}
void Character::setMaxHP(int hp) {
	max_HP = hp;
}
void Character::setMaxMP(int mp) {
	max_MP = mp;
}
void Character::setMaxArmor(int armor) {
	max_Armor = armor;
}
void Character::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("Meta");
	this->meta->setVisible(false);
}
void Character::setIsKnockBack(bool status) {
	isKnockBack = status;
}
void Character::setIsInvincible(bool status) {
	isInvincible = status;
}
//
int Character::getHP() { return m_HP; }
int Character::getMP() { return m_MP; }
int Character::getArmor() { return m_Armor; }
int Character::getSpeed() { return m_Speed; }

//以玩家为中心设置视角
void Character::setViewPointByCharacter() {
	if (getSprite() == NULL) { return; }
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* parent = (Layer*)getParent();//
	Point characterPos = getPosition();//获取主角坐标
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);
	Point viewPos = centerPos - characterPos;
	 
	parent->setPosition(viewPos);

}

void Character::setTagPosition(int x, int y) {
	if (isKnockBack) { return; }//正在被击退时不能行动
	if (isPosBlocked(Point(x+halfOfHitBox, y+ halfOfHitBox))) { return; }
	if (isPosBlocked(Point(x+ halfOfHitBox, y- halfOfHitBox))) { return; }
	if (isPosBlocked(Point(x- halfOfHitBox, y+ halfOfHitBox))) { return; }
	if (isPosBlocked(Point(x- halfOfHitBox, y- halfOfHitBox))) { return; }//移动路径被阻挡了 不能行动
	auto pos = tileCoordForPosition(this->getPosition());
	auto mapSize = m_map->getMapSize();
	
	this->setPositionZ(pos.y - mapSize.height);

	Entity::setTagPosition(x, y);
	setViewPointByCharacter();
}

bool Character::isPosBlocked(Point dstPos) {
	/*int dir;
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

Point Character::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;


	return Point(x, y);
}




void Character::hit(int damage,Point enemyPos) {
	if (getSprite() == NULL) { return; }
	if (this->isInvincible) { return; }//还处于无敌状态，不造成伤害

	//未处于无敌状态，扣血，进入无敌状态，击退
	this->setIsInvincible(true);
	Blink* invincibleBlink = Blink::create(INVINCIBLE_TIME, INVINCIBLE_TIME*6);
	this->runAction(invincibleBlink);//无敌闪烁动画

	CallBackTimeCounter* invincibleTimer = CallBackTimeCounter::create();
	this->addChild(invincibleTimer);
	invincibleTimer->start(INVINCIBLE_TIME, [&]() {
		setIsInvincible(false); });//定时结束后将无敌状态取消

	
	//造成伤害 有护甲先扣护甲，没护甲再扣血
	if (m_Armor >= damage) { m_Armor-=damage; }
	else {
		int overKill = damage - m_Armor;
		m_Armor=0;
		m_HP-=overKill;
	}//护甲值先消耗殆尽，多余伤害由红条承受
	
	if (m_HP <= 0) { m_HP = 0; }

	//击退效果
	setIsKnockBack(true);
	int knockBackDir;//1234分别代表左上右下
	Point characterPos = this->getPosition();
	Point dstPos = enemyPos - characterPos;
	if (dstPos.x <= 0 && abs(dstPos.y) <= abs(dstPos.x)) { knockBackDir = 3; }
	else if (dstPos.y >= 0 && abs(dstPos.x) <= dstPos.y) { knockBackDir = 4; }
	else if (dstPos.x >= 0 && abs(dstPos.y) <= dstPos.x) { knockBackDir = 1; }
	else if (dstPos.y <= 0 && abs(dstPos.x) <= abs(dstPos.y)) { knockBackDir = 2; }

	Point knockPos;
	switch (knockBackDir)
	{
	case 1:
		knockPos =Point(-KNOCKBACK_DISTANCE, 0);
		break;
	case 2:
		knockPos =Point(0, KNOCKBACK_DISTANCE);
		break;
	case 3:
		knockPos =Point(KNOCKBACK_DISTANCE, 0);
		break;
	case 4:
		knockPos = Point(0, -KNOCKBACK_DISTANCE);
		break;
	default:
		break;
	}
	
	auto resetKnockBackStatus = [&]() {
		setIsKnockBack(false);
	};
	//确定被击退路径上没障碍物
	int tempDistance = KNOCKBACK_DISTANCE;
	Point curPos = this->getPosition();
	int x = curPos.x + knockPos.x;
	int y = curPos.y + knockPos.y;

	while (isPosBlocked(Point(x + halfOfHitBox, y + halfOfHitBox))||
		isPosBlocked(Point(x + halfOfHitBox, y - halfOfHitBox))||
		isPosBlocked(Point(x - halfOfHitBox, y + halfOfHitBox))||
		isPosBlocked(Point(x - halfOfHitBox, y - halfOfHitBox)))//矩形四角均没障碍物
	{
		tempDistance -= 1;
		switch (knockBackDir)
		{
		case 1:
			knockPos = Point(-tempDistance, 0);
			break;
		case 2:
			knockPos = Point(0, tempDistance);
			break;
		case 3:
			knockPos = Point(tempDistance, 0);
			break;
		case 4:
			knockPos = Point(0, -tempDistance);
			break;
		default:
			break;
		}
		x = curPos.x + knockPos.x;
		y = curPos.y + knockPos.y;
	}
	//生成击退动作
	auto knockBackMove = MoveBy::create(KNOCKBACK_TIME, knockPos);
	auto smoothViewMove = MoveBy::create(KNOCKBACK_TIME, -knockPos);
	CallFunc* callFunc = CallFunc::create(resetKnockBackStatus);//动画结束后将击退状态设为f
	Layer* parent = (Layer*)getParent();
	
	auto moveAction = Sequence::create(knockBackMove,callFunc,NULL);//暂时没做出加速度效果
	parent->runAction(smoothViewMove);
	runAction(moveAction);
}

void Character::update(float delta) {
	
}