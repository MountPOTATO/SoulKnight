#ifndef __WEAPONBUFF_H__
#define __WEAPONBUFF_H__


#include "cocos2d.h"
#include "Const/ConstInfo.h"
using namespace cocos2d;
USING_NS_CC;


class WeaponBuff :public Sprite {
public:
	CC_SYNTHESIZE(EWeaponBuffEffect, m_weaponBuffEffect, WeaponBuffEffect);//buff����

	//��������
	CC_SYNTHESIZE(bool, m_isTempBuff, IsTempBuff);//�Ƿ�Ϊ��ʱ��buff����limitBreak��
	//��������
	CC_SYNTHESIZE(INT32, m_attack, Attack); //������
		//TODO:����������������ʽ�����ս��Զս��Ԫ�أ�ħ���ȣ��Ӻ�������������
	CC_SYNTHESIZE(float, m_attackSpeed, AttackSpeed);//�����ٶ�(��������֮����ʱ��)
	CC_SYNTHESIZE(float, m_attackRange, AttackRange);//������Χ
	CC_SYNTHESIZE(float, m_hardStrikeRate, HardStrikeRate);//�����ʣ��Ӻ������ܶ���

	//��������
	CC_SYNTHESIZE(int, m_energyCost, EnergyCost);//��������
	CC_SYNTHESIZE(float, m_precision, Precision);//��׼��


	//ʱ����
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//��ʼʱ�䣬-1����������buff��û����ʼʱ��
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//����ʱ��,-1Ϊ����
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//����ʱ��,-1����������buff��û�н���ʱ��

	bool isATempWeaponBuff()const { return m_isTempBuff; }
	INT32 getWeaponBuffAttack()const { return m_attack; }
	float getWeaponBuffAttackSpeed()const { return m_attackSpeed; }
	float getWeaponBuffAttackRange()const { return m_attackRange; }
	float getWeaponBuffHardStrikeRate()const { return m_hardStrikeRate; }
	int getWeaponBuffEnergyCost()const { return m_energyCost; }
	float getWeaponBuffPrecision()const { return m_precision; }
	float getWeaponBuffLastTime()const { return m_lastTime; }
	float getWeaponBuffEndTime()const { return m_endTime; }



	//TODO:������BUFF���ԣ��˴��б�Ҫ���
	//������ķ�����·ֺ���
	virtual bool init(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed,float attackRange,float hardStrikeRate,
		int energyCost,float precision,
		float lastTime
	);

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�
	/*virtual bool init(ValueVector& data);*/

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�
	static WeaponBuff* create(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
		int energyCost, float precision,
		float lastTime
	);

	//����̬������buff
	
};




#endif


