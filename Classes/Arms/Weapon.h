#ifndef __WEAPON_H___
#define __WEAPON_H___

#include "cocos2d.h"
#include "Buff/WeaponBuff.h"
#include "HelloWorldScene.h"
#include <string>
#include <iostream>
using namespace cocos2d;


//TODO:�����Ƶ�ר�ŵĳ�������
enum ESide {
	sideHero,
	sideMonster,
	sidePet,
	sideHelper
};

enum EWeaponDirection {
	weaponUp,
	weaponDown,
	weaponLeft,
	weaponRight,
	weaponUpLeft,
	weaponUpRight,
	weaponDownLeft,
	weaponDownRight,
	weaponStop,//û�м�������״̬
	weaponAttackingEnermy//��⵽���˴���ʱ���״̬
};

class Weapon :public Sprite {
private:
	bool m_upState, m_downState, m_leftState, m_rightState;
	//�������ԣ�
	//���е����ԣ��ɱ䶯��
	CC_SYNTHESIZE(INT32, _attack, Attack); //������
		//TODO:����������������ʽ�����ս��Զս��Ԫ�أ�ħ���ȣ��Ӻ�������������
	
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);//�����ٶ�(��������֮����ʱ��)
	CC_SYNTHESIZE(float, _attackRange, AttackRange);//������Χ
	CC_SYNTHESIZE(float, _hardStrikeRate, HardStrikeRate);//�����ʣ��Ӻ������ܶ���
	CC_SYNTHESIZE(int, _energyCost, EnergyCost);//��������
	CC_SYNTHESIZE(float, _precision, Precision);//��׼��

	//���е����ԣ����ɱ䶯��
	CC_SYNTHESIZE(String,_weaponName, WeaponName);
	CC_SYNTHESIZE(INT32, _weaponPrice, WeaponPrice);

	//������������Ϣ
	/*CC_SYNTHESIZE(HelloWorld*, _currentScene, CurrentScene);*/	
	CC_SYNTHESIZE(ESide, _side, Side);//����������
	//CC_SYNTHESIZE(Entity*, _target, Target);//����������

	//ʱ����Ϣ
	CC_SYNTHESIZE(float, _lastAttackTime, LastAttackTime);

	//����״̬
	CC_SYNTHESIZE(bool, _heroOwned, HeroOwned);//�Ƿ�Ӣ�������У���������Ӧһϵ�м������룬��������Ӧ����͹�������
	CC_SYNTHESIZE(bool, _isAttacking, IsAttacking);
	CC_SYNTHESIZE(bool, _isCanMove, IsCanMove);//�Ƿ���Զ�(���̲�����ʱ�����Զ�)




	CC_SYNTHESIZE(EWeaponDirection, _ewDirection, EwDirection);

	EventListenerKeyboard* listenerKeyboard;//���̼���
	virtual bool onPressKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool onReleaseKey(EventKeyboard::KeyCode keyCode, Event* event);
	virtual bool updateState(EventKeyboard::KeyCode keyCode, int type);
	virtual bool updateDirection();

	/*Point getAnglePosition(float r, float angle);*/

public:

	Vector<WeaponBuff*> _vecWeaponBuff;


	virtual void takeBuff(WeaponBuff* weaponBuff);
	virtual void cancelBuff(WeaponBuff* weaponBuff);
	virtual void deleteTempBuff();
	virtual void clearBuff();

	virtual bool attack();//TODO:����̬��ʽ

	
	//void stopWeapon();TODO

	static Weapon* create
	(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool _heroOwned);
	virtual bool init
	(const char* weaponImageName1, const char* weaponImageName2, ESide side, bool _heroOwned);
	void startWeapon(bool _isStopOther);

	void showWeaponPicture(int type);//1����ָ���ұߵ�ͼƬ��2����ָ����ߣ����򣩵�ͼƬ
	
	const char* getVisiblePictureSide()const;//����ұ�ͼ���ӷ���"right",��֮"left";

	Sprite* getVisiblePicture()const;

	//get��������
	float getAttackRange()const { return _attackRange; }

protected:

	//TODO:�༭InitBasicInfo
	/*virtual void initBasicInfo(ESide side);*/

};



#endif