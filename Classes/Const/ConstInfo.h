#ifndef __CONSTINFO_H__
#define __CONSTINFO_H__

#include "cocos2d.h"
#include <vector>
#include<string>


USING_NS_CC;

class Weapon;

class HRocker;

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


enum MovingDir {
	left,
	upLeft,
	up,
	upRight,
	right,
	downRight,
	down,
	downLeft,
};
//GlobalConst
#define HIT_WHEN_COLLIDE_WITH_ENEMY 1 //����ͨ������ײ��Ѫ��
#define KNOCKBACK_DISTANCE 20//�����˺��˵ľ���
#define KNOCKBACK_TIME 0.1f//�����˳�����ʱ��


#define INVINCIBLE_TIME 2.0f //���˺���޵�ʱ��
//Knight
#define KNIGHT_HP 10
#define KNIGHT_MP 200
#define KNIGHT_SPEED 6
#define KNIGHT_ARMOR 5





#define CHARGER_HP 25
#define CHARGER_SPEED 1
#define CHARGER_CHARGE_SPEED 2
#define CHARGER_ATK 0 //Ԥ�����ֱ������ײ�˺� 
#define CHARGER_MAX_MOVES_ROUND 50
#define CHARGER_MAX_CHARGES_ROUND 100//����ײ����
#define CHARGER_MOVE_PAUSE_TIME 3.0f

#define MUMMY_HP 8
#define MUMMY_SPEED 2
#define MUMMY_CHARGE_SPEED 5
#define MUMMY_ATK 0 //Ԥ�����ֱ������ײ�˺� 
#define MUMMY_MAX_MOVES_ROUND 50
#define MUMMY_MAX_CHARGES_ROUND 300//����ײ����
#define MUMMY_MOVE_PAUSE_TIME 3.0f


//Ranger
#define RANGER_HP 15
#define RANGER_SPEED 2
#define RANGER_ATK 3

#define RANGER_MAX_MOVES_ROUND 50//ÿ�ν����ƶ�ʱ����ƶ��ľ��� Ϊ MAX_MOVES_ROUND*RANGER_SPEED 
#define RANGER_MOVE_PAUSE_TIME 3.0f//������һ���ƶ���ԭ�صȴ���ʱ��

#define TOWER_HP 25
#define TOWER_SPEED 2
#define TOWER_ATK 4

#define TOWER_MAX_MOVES_ROUND 50//ÿ�ν����ƶ�ʱ����ƶ��ľ��� Ϊ MAX_MOVES_ROUND*RANGER_SPEED 
#define TOWER_MOVE_PAUSE_TIME 3.0f//������һ���ƶ���ԭ�صȴ���ʱ��


//������������������
#define GUN "Gun"
#define MELEE "Melee"
#define GUN_OLDPISTOL "OldPistol"
#define GUN_SNIPER "Sniper"
#define GUN_SMG "SMG"
#define MELEE_FISH "Fish"
#define MELEE_WAND "Wand"
#define GUN_SHOTGUN "Shotgun"

#define RED "red"
#define BLUE "blue"

//һЩʱ����
#define SWITCH_TIMESPACE 0.6f
#define PICK_TIMESPACE 0.7f




//controller�ı�ʶ
#define CONTROLLER_TAG 9999
//pause�ı�ʶ
#define PAUSE_TAG 8999

//����������ٺ���ٶ�
#define ACCELERATE_KNIGHT_SPEED 9

//����ʱ��
#define ACCELERATE_TIME 1.2f
#define ACCELERATE_TOUCHRANGE  27.0f

//״̬�򴴽���ʶ
#define QHP 1
#define QARMOR 2
#define QMP 3

//״̬���ʶ
#define STATUS_BOX_TAG 7999

struct HeroInfo {
	int hp;
	int mp;
	int armor;
	Weapon* wp1;
	Weapon* wp2;
	Weapon* curwp;
};


//GlobalConst
#define HIT_WHEN_COLLIDE_WITH_ENEMY 1 //����ͨ������ײ��Ѫ��
#define KNOCKBACK_DISTANCE 80//�����˺��˵ľ���
#define KNOCKBACK_TIME 0.1f//�����˳�����ʱ��

//space type
#define V_CORI 0
#define H_CORI 1
#define ROOM 2

//space exit info
#define NONE 0
#define E_UNAPPENDED 1
#define E_APPENDED 2

////placeSize
#define PLACE_SIZE 4


#define DOWN 1
#define RIGHT 2
#define UP 3
#define LEFT 4

#define EMPTY 0
#define FULL 1
#define APPOINTED 2




extern std::vector<std::string> exitRightMaps;
extern std::vector<std::string> exitLeftMaps;
extern std::vector<std::string> exitUpMaps;
extern std::vector<std::string> exitDownMaps;
extern std::vector<std::string>  corridors;





#endif