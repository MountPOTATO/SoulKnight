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

#endif