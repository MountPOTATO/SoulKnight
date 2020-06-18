#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
USING_NS_CC;

class MonsterManager :public Node {
public:
	CREATE_FUNC(MonsterManager);
	virtual bool init();

	virtual void update(float delta);

	void bindCharacter(Character* character);
public:
	void createMonster(int MonsterID,Point monsterSpawnPoint);//根据id创建怪物
	void spawnLotsOfMonsters(Point spawnCenterPoint,float rad,int spawnNum);//生成范围中心点 生成半径 生成个数
	bool isPosBlocked(Point dstPos);
	TMXTiledMap* m_map;
	TMXLayer* meta;
	void setTiledMap(TMXTiledMap* map);
	Point tileCoordForPosition(Point pos);
		
private:

	Character* m_Character;
	Vector<Monster*>m_MonsterArray;//存放怪物列表
};