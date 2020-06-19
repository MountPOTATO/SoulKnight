#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Arms/Weapon.h"
#include "Const/ConstInfo.h"
#include "Tools/CallBackTimeCounter.h"
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
	void setIsKnockBack(bool status);//�����Ƿ����ڱ�����
	void setIsInvincible(bool status);//�����Ƿ����޵�״̬

public:
	void setViewPointByCharacter();

	

	virtual void setTagPosition(int x,int y);
	void setTiledMap(TMXTiledMap* map);

	TMXTiledMap* getTiledMap() { return m_map; }

	bool isPosBlocked(Point dstPos );//�ж��ƶ��յ��Ƿ����ϰ��� fΪ���ϰ� 0�����޷��� 1,2,3,4������������
	void hit(int damage,Point enemyPos);//�յ��˺� ��������޵�ģʽ �����˺�����
	void die();//����˼�壬��ƨ��
	bool isInvincible;//�Ƿ����޵�״̬
	bool isKnockBack;//�Ƿ��ڱ�����״̬
	bool isAlive;//�Ƿ����
	int max_HP;//��������
	int max_MP;//��������
	int max_Armor;//��������


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