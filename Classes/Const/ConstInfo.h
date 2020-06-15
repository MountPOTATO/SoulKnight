#ifndef __CONSTINFO_H__
#define __CONSTINFO_H__

//ҡ�˵���Ϣ����
enum ERocker8Direction {
	rockerUp,
	rockerDown,
	rockerLeft,
	rockerRight,
	rockerUpLeft,
	rockerUpRight,
	rockerDownLeft,
	rockerDownRight,
	rockerStop
};

enum ERockerButtonPress {
	buttonAttack,
	buttonLimitBreak,
	buttonSwitch,
	buttonNone
};

//������Ӫ����
enum ESide {
	sideHero,
	sideMonster,
	sidePet,
	sideHelper
};



//����buffЧ��������
enum EWeaponBuffEffect {
	//��������Ļ���buff״̬,���ڴ����

	WbuffLimitBreak, //���У���ȷ����ֻ����Ե��������������ܸı�Ĵ��У������⹦�����ٻ��ȴ��в�ȷ����
	WbuffStrengthen,  //������ǿbuff
	WbuffClean,		//Ĭ��״̬

	WbuffCombine

};


//����buffЧ��������
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
//GlobalConst
#define HIT_WHEN_COLLIDE_WITH_ENEMY 1 //����ͨ������ײ��Ѫ��
#define KNOCKBACK_DISTANCE 80//�����˺��˵ľ���
#define KNOCKBACK_TIME 0.1f//�����˳�����ʱ��


#define INVINCIBLE_TIME 2.0f //���˺���޵�ʱ��
//Knight
#define KNIGHT_HP 10
#define KNIGHT_MP 10
#define KNIGHT_SPEED 5
#define KNIGHT_ARMOR 5





//Ranger
#define RANGER_HP 10
#define RANGER_SPEED 5
#define RANGER_ATK 5






//������������������
#define GUN "Gun"
#define MELEE "Melee"
#define GUN_OLDPISTOL "OldPistol"
#define GUN_SNIPER "Sniper"
#define GUN_SMG "SMG"
#define MELEE_FISH "Fish"
#define GUN_SHOTGUN "Shotgun"

#define RED "red"
#define BLUE "blue"

//һЩʱ����
#define SWITCH_TIMESPACE 1.0f
#define PICK_TIMESPACE 1.0f










#endif