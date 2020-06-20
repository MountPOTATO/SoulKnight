#pragma once
#include "Entity/Monster.h"
#include "cocos2d.h"
#include "Entity/Enemy/Ranger.h"
#include "Entity/Enemy/Charger.h"
USING_NS_CC;

class HelloWorld;
class Character;

class MonsterManager :public Node {
public:

	static MonsterManager* create(Point pos, HelloWorld* scene, Character* character);
	bool initWithData(Point pos, HelloWorld* scene, Character* character);

	CREATE_FUNC(MonsterManager);

	virtual bool init();

	virtual void update(float delta);

	void bindCharacter(Character* character);
public:
	void createMonster(int MonsterID,Point monsterSpawnPoint);//根据id创建怪物
	void spawnLotsOfMonsters(Point spawnCenterPoint,float rad,int spawnNum);//生成范围中心点 生成半径 生成个数
	bool isPosBlocked(Point dstPos);
	bool isUsed()const { return m_isUsed == true; }
	TMXTiledMap* m_map;
	TMXLayer* meta;
	void setTiledMap(TMXTiledMap* map);
	Point tileCoordForPosition(Point pos);
	HelloWorld* currentScene;	
private:
	
	Character* m_Character;
	
	Vector<Monster*>m_MonsterArray;//存放怪物列表
	bool m_isUsed = false;
};