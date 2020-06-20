#include "Entity/Monster.h"
#include "LongRangeAttack/Bullet.h"
#include "HelloWorldScene.h"

float MyMathGetRad(Point point1, Point point2);

bool Monster::init() {

	return true;
}
void Monster::setTiledMap(TMXTiledMap* map) {
	m_map = map;
	this->meta = m_map->getLayer("MonsterMeta");
	this->meta->setVisible(false);
}

bool Monster::isCollideWithCharacter(Character* character) {
	Rect entityRect = character->getBoundingBox();
	Rect monsterRect = this->getBoundingBox();
	Point monsterPos = getPosition();
	return entityRect.intersectsRect(monsterRect);
}

int Monster::getHP() {
	return m_HP;
}

int Monster::getSpeed() {
	return m_Speed;
}
float Monster::getAtkSpeed() {
	return m_AtkSpeed;
}
int Monster::getAtk() {
	return m_Atk;
}
void Monster::setHP(int hp) {
	m_HP = hp;
}
void Monster::setSpeed(int speed) {
	m_Speed = speed;
}
void Monster::setAtkSpeed(float atkSpeed) {
	m_AtkSpeed = atkSpeed;
}
void Monster::setAtk(int atk){
	m_Atk = atk;
}

void Monster::attack(HelloWorld* currentScene) {
	auto currentTime = GetCurrentTime() / 1000.f;

	if (currentTime - _lastAttackTime <= _attackTimeSpace) return;

	_lastAttackTime = currentTime;
	_attackTimeSpace = CCRANDOM_0_1() * 4 + 4;

	if (currentScene) {
		if (this->m_monsterID == 1) {
			Bullet* bullet = Bullet::create("BulletImage\\RangerBullet.png", 450.f,
				this, MyMathGetRad(this->getPosition(), currentScene->getHero()->getPosition())
			);
			if (bullet) {
				bullet->setVisible(true);
				bullet->setScale(1.2f);
				bullet->setTiledMap(this->m_map);
				currentScene->addChild(bullet);
				currentScene->_enemyBullet.pushBack(bullet);
			}
		}
		if (this->m_monsterID == 2) {
			for (int i = 0; i < 8; i++) {
				Bullet* bullet = Bullet::create("BulletImage\\TowerBullet.png", 200.f,
					this, i*PI/4);
				if (bullet) {
					bullet->setVisible(true);
					bullet->setScale(1.2f);
					bullet->setTiledMap(this->m_map);
					currentScene->addChild(bullet);
					currentScene->_enemyBullet.pushBack(bullet);
				}
			}
		}
	}


}

void Monster::bindCharacter(Character* character) {
	m_character = character;
}

Point Monster::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = pos.x / tiledSize.width;
	int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;


	return Point(x, y);
}

float MyMathGetRad(Point point1, Point point2) {
	//获得两点x,y距离
	float xd = point2.x - point1.x;
	float yd = point1.y - point2.y;
	//斜边长度计算
	float hypo = sqrt(pow(xd, 2) + pow(yd, 2));
	//获得余弦值
	float cos = xd / hypo;
	//获得rad
	float rad = acos(cos);
	//取反ss
	if (yd > 0) {
		rad = -rad;
	}
	return rad;
}