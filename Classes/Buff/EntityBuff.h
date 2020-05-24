#ifndef __ENTITYBUFF_H__
#define __ENTITYBUFF_H__



#include "cocos2d.h"

USING_NS_CC;

//buffЧ��������
enum EEntityBuffEffect {
	//��������Ļ���buff״̬,���ڴ����
	EbuffFrozen,	//����	
	EbuffPoisoned,	//�ж�
	EbuffBurning,	//���գ���ը����
	EbuffSpeedUp,	//����
	EbuffSlowDown,	//����


	EbuffLimitBreak, //���У���ȷ����ֻ����Ե����������ܸı�Ĵ��У������⹦�����ٻ��ȴ��в�ȷ����
	EbuffInvincible,//�޵�(�����л���״̬?)

	EbuffClean			//Ĭ��״̬

};

class EntityBuff :public cocos2d::Sprite {
public:
	CC_SYNTHESIZE(EEntityBuffEffect, m_entityBuffEffect, EntityBuffEffect);//buff����

	//��������
	CC_SYNTHESIZE(INT32, m_defence, Defence); //����
	//TODO:�����к�������ģʽ�����ս�˺�������Զ�̹���������������BUFF�ȣ��Ӻ�������������


	CC_SYNTHESIZE(INT32, m_HP, HP)//Ѫ��
	CC_SYNTHESIZE(INT32, m_armor, Armor)//����
	CC_SYNTHESIZE(INT32, m_MP, MP)//ħ��
	CC_SYNTHESIZE(float, m_moveSpeed, MoveSpeed);//�ƶ��ٶ�


	CC_SYNTHESIZE(float, m_limitBreakRecoverSpeed, LimitBreakRecoverSpeed);//������ȴ�ٶ�

	//����ô����������

	CC_SYNTHESIZE(INT32, m_HPRecoverSpeed, HPRecoverSpeed)//Ѫ���Զ��ظ��ٶȣ��Ӻ������ܶ���(�����ܻ����
	CC_SYNTHESIZE(INT32, m_armorRecoverSpeed, ArmorRecoverSpeed)//�����Զ��ظ��ٶȣ��Ӻ������ܶ���
	CC_SYNTHESIZE(INT32, m_MPRecoverSpeed, MPRecoverSpeed)//Ѫ���Զ��ظ��ٶȣ��Ӻ������ܶ���

	//�����¼�
	CC_SYNTHESIZE(float, m_hardStrikeRate, HardStrikeRate);//�����ʣ��Ӻ������ܶ���


	//ʱ����
	CC_SYNTHESIZE(float, m_beginTime, BeginTime);	//��ʼʱ��
	CC_SYNTHESIZE(float, m_lastTime, LastTime);		//����ʱ��
	CC_SYNTHESIZE(float, m_endTime, EndTime);		//����ʱ��

	//TODO:������BUFF���ԣ��˴��б�Ҫ���
	//������ķ�����·ֺ���
	virtual bool init(EEntityBuffEffect entityBuffEffect,
		INT32 defence,
		INT32 HP, INT32 armor, INT32 MP,float moveSpeed, 
		float limitBreakRecoverSpeed,
		INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
		float hardStrikeRate,
		float lastTime
	);

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�

	//TODO:���vector��init��ʽ
	/*virtual bool init(ValueVector& data);*/

	//TODO:������BUFF���ԣ��˴��б�Ҫ�޸�
	static EntityBuff* create(EEntityBuffEffect entityBuffEffect,
		INT32 defence,
		INT32 HP, INT32 armor, INT32 MP, float moveSpeed,
		float limitBreakRecoverSpeed,
		INT32 HPRecoverSpeed, INT32 armorRecoverSpeed, INT32 MPRecoverSpeed,
		float hardStrikeRate,
		float lastTime
	);

};




#endif


