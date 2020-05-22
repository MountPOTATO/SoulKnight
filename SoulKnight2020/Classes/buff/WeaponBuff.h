#ifndef __WEAPONBUFF_H__
#define __WEAPONBUFF_H__


#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

//buffЧ��������
enum EWeaponBuffEffect {
	//��������Ļ���buff״̬,���ڴ����

	WbuffLimitBreak, //���У���ȷ����ֻ����Ե��������������ܸı�Ĵ��У������⹦�����ٻ��ȴ��в�ȷ����
	WbuffStrengthen,  //������ǿbuff
	WbuffClean		//Ĭ��״̬

};

class WeaponBuff :public Sprite {
public:
	CC_SYNTHESIZE(EWeaponBuffEffect, m_weaponBuffEffect, WeaponBuffEffect);//buff����

	//��������

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
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//��ʼʱ��
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//����ʱ��
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//����ʱ��





	//TODO:������BUFF���ԣ��˴��б�Ҫ���
	//������ķ�����·ֺ���
	virtual bool init(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed,float attackRange,float hardStrikeRate,
		int energyCost,float precision,
		float lastTime
	);

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�
	virtual bool init(ValueVector& data);

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�
	static WeaponBuff* create(EWeaponBuffEffect weaponBuffEffect,
		INT32 attack, float attackSpeed, float attackRange, float hardStrikeRate,
		int energyCost, float precision,
		float lastTime
	);

};




#endif


