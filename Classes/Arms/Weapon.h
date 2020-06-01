#ifndef __WEAPON_H___
#define __WEAPON_H___

#include "cocos2d.h"
#include "Buff/WeaponBuff.h"
#include "Controller/HRocker.h"


#include <string>
#include <iostream>
#include <Const/ConstInfo.h>
#include "Entity/Entity.h"


using namespace cocos2d;

#define PRESS 1
#define RELEASE 2

#define TAG_WEAPON1 1
#define TAG_WEAPON2 2


class HelloWorld;


//TODO:�����Ƶ�ר�ŵĳ�������



class Weapon :public Node {
private:
	bool m_upState, m_downState, m_leftState, m_rightState;
	//�������ԣ�
	//���е����ԣ��ɱ䶯��
	CC_SYNTHESIZE(INT32, _attack, Attack); //������
	CC_SYNTHESIZE(INT32, _precision, Precision);//��׼��,ƫ�ƽ�
	CC_SYNTHESIZE(INT32, _energyCost, EnergyCost);//��������
	CC_SYNTHESIZE(INT32, _weaponPrice, WeaponPrice);//�����̵�۸�	
		//TODO:����������������ʽ�����ս��Զս��Ԫ�أ�ħ���ȣ��Ӻ�������������	
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);//�����ٶ�(��������֮����ʱ��)
	CC_SYNTHESIZE(float, _attackRange, AttackRange);//������Χ
	CC_SYNTHESIZE(float, _hardStrikeRate, HardStrikeRate);//�����ʣ��Ӻ������ܶ���
	CC_SYNTHESIZE(float, _bulletFlyingSpeed, BulletFlyingSpeed);//���룬�����ӵ��������ڹ���״̬�µķ���״̬)
	//���е����ԣ����ɱ䶯��
	CC_SYNTHESIZE(String,_weaponName, WeaponName);
	
	//������������Ϣ
	CC_SYNTHESIZE(HelloWorld*, _currentScene, CurrentScene);	
	CC_SYNTHESIZE(ESide, _side, Side);//������������Ӫ
	CC_SYNTHESIZE(Entity*, _target, Target);//����������

	CC_SYNTHESIZE(Entity*, _owner, Owner);//������������Ӫ

	//ʱ����Ϣ
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);

	


	//�Ƕ���Ϣ
	CC_SYNTHESIZE(float, _mathAngle, MathAngle);
	CC_SYNTHESIZE(float, _targetMathRad, TargetMathRad);
	float getWeaponTargetMathRad()const { return _targetMathRad; }

	//����״̬
	CC_SYNTHESIZE(bool, _heroOwned, HeroOwned);//�Ƿ�Ӣ�������У���������Ӧһϵ�м������룬��������Ӧ����͹�������
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);//�Ƿ��ڹ���
	CC_SYNTHESIZE(bool, _isCanMove, IsCanMove);//�Ƿ���Զ�(���̲�����ʱ�����Զ�)
	CC_SYNTHESIZE(bool, _hasAnimation, HasAnimation);//�Ƿ��ж��������У���ʱ����ͼƬ���£�

	bool hasMeleeAnimation()const { return _hasAnimation; }



	


public:

	Vector<WeaponBuff*> _vecWeaponBuff;//��������Buff��

	//��Buff�Ĳ���
	virtual void takeBuff(WeaponBuff* weaponBuff);
	virtual void cancelBuff(WeaponBuff* weaponBuff);
	virtual void deleteTempBuff();
	virtual void clearBuff();

	//�����Լ���������Ҫ��get����
	virtual bool attack();//TODO:����̬��ʽ
	INT32 getWeaponAttack()const { return _attack; }
	HelloWorld* getWeaponCurrentScene() { return this->_currentScene; }
	//void stopWeapon();TODO
	float getWeaponBulletFlyingSpeed()const { return _bulletFlyingSpeed; }



	//�Ƕ���Ϣ��
	float getRad(Point point1, Point point2)const;

	//������ʼ��start��stop
	static Weapon* create
	(const char* weaponImageName1, const char* weaponImageName2,
	  HelloWorld* currentScene,ESide side, bool _heroOwned);

	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2,
	  HelloWorld* currentScene, ESide side, bool heroOwned);
	void startWeapon(bool _isStopOther);
	void stopWeapon(bool _isStopOther);


	void showWeaponPicture(int type);//1����ָ���ұߵ�ͼƬ��2����ָ����ߣ����򣩵�ͼƬ
	
	const char* getVisiblePictureSide()const;//����ұ�ͼ���ӷ���"right",��֮"left";

	Sprite* getVisiblePicture()const;

	void updateImageRotation(HRocker* rocker);

	virtual void updateTarget();


	//λ�ø������
	virtual void setWeaponTagPosition(int x, int y);
	virtual Point getWeaponTagPosition()const { return getPosition(); }
	virtual void setViewPointByWeapon();//������Ϊ��������ӽ�

protected:

	//TODO:�༭InitBasicInfo
	/*virtual void initBasicInfo(ESide side);*/

};



#endif