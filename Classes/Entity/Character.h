#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Arms/Weapon.h"
class Character :public Entity {
public:
	CREATE_FUNC(Character);
	Character();
	~Character();
	virtual bool init();

public:
	void setHP(int hp);
	void setMP(int mp);
	void setArmor(int armor);
	void setSpeed(int speed);
	int getHP();
	int getMP();
	int getArmor();
	int getSpeed();

public:
	void setViewPointByCharacter();
	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap* map);
	bool isPosBlocked(Point dstPos );//判断移动终点是否有障碍物 f为无障碍 0代表无方向 1,2,3,4代表左上右下

private:
	Weapon* m_Weapon1;
	Weapon* m_Weapon2;
	int m_HP;
	int m_MP;
	int m_Armor;
	int m_Speed;
	TMXLayer* meta;
	Point tileCoordForPosition(Point pos);

private:
	TMXTiledMap* m_map;

};