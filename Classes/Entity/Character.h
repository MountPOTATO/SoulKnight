#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Arms/Weapon.h"
#include "Const/ConstInfo.h"
#define  halfOfHitBox 18//����˼����������ײ�����һ�� �ϸ���˵��20���أ�Ϊ��������ͨ��20���صķ�϶����Щ����

enum EnumState{
	enStateInvincible,//�޵�״̬
	enStateUninvincibel,//���޵�״̬

};





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
	void setIsKnockBack(bool status);

public:
	void setViewPointByCharacter();
	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap* map);
	bool isPosBlocked(Point dstPos );//�ж��ƶ��յ��Ƿ����ϰ��� fΪ���ϰ� 0�����޷��� 1,2,3,4������������
	void hit(int damage,Point enemyPos);//�յ��˺� ��������޵�ģʽ �����˺�����
	bool isInvincible;//�Ƿ����޵�״̬
	bool isKnockBack;//�Ƿ��ڱ�����״̬
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