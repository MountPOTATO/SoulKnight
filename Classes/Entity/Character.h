#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Arms/Weapon.h"
#include "Const/ConstInfo.h"
#include "Tools/CallBackTimeCounter.h"
#define  halfOfHitBox 18//顾名思义是人物碰撞体积的一半 严格来说是20像素，为了能流畅通过20像素的缝隙做了些牺牲

enum EnumState{
	enStateInvincible,//无敌状态
	enStateUninvincibel,//非无敌状态

};





class Character :public Entity {
public:
	CREATE_FUNC(Character);
	Character();
	~Character();
	virtual bool init();
	virtual void update(float delta);
public:
	void setHP(int hp);
	void setMP(int mp);
	void setArmor(int armor);
	void setSpeed(int speed);
	void setMaxHP(int hp);
	void setMaxMP(int mp);
	void setMaxArmor(int armor);
	int getHP();
	int getMP();
	int getArmor();
	int getSpeed();
	void setIsKnockBack(bool status);//设置是否正在被击退
	void setIsInvincible(bool status);//设置是否处于无敌状态

public:
	void setViewPointByCharacter();

	

	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap* map);

	TMXTiledMap* getTiledMap() { return m_map; }

	bool isPosBlocked(Point dstPos );//判断移动终点是否有障碍物 f为无障碍 0代表无方向 1,2,3,4代表左上右下
	void hit(int damage,Point enemyPos);//收到伤害 进入短暂无敌模式 传递伤害方向
	void die();//顾名思义，嗝屁了
	bool isInvincible;//是否处于无敌状态
	bool isKnockBack;//是否处于被击退状态
	bool isAlive;//是否活着
	int max_HP;//生命上限
	int max_MP;//蓝量上限
	int max_Armor;//护甲上限


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