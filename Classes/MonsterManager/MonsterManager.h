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
	void createMonster(int MonsterID,Point monsterSpawnPoint);//����id��������
	void spawnLotsOfMonsters(Point spawnCenterPoint,float rad,int spawnNum);//���ɷ�Χ���ĵ� ���ɰ뾶 ���ɸ���
	bool isPosBlocked(Point dstPos);
	bool isUsed()const { return m_isUsed == true; }
	TMXTiledMap* m_map;
	TMXLayer* meta;
	void setTiledMap(TMXTiledMap* map);
	Point tileCoordForPosition(Point pos);
	HelloWorld* currentScene;	
private:
	
	Character* m_Character;
	
	Vector<Monster*>m_MonsterArray;//��Ź����б�
	bool m_isUsed = false;
};