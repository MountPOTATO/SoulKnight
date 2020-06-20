#ifndef __CONSTINFO_H__
#define __CONSTINFO_H__

#include "cocos2d.h"
#include <vector>
#include<string>


USING_NS_CC;

class Weapon;

class HRocker;

//摇杆的信息输入
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

//武器阵营归属
enum ESide {
	sideHero,
	sideMonster,
	sidePet,
	sideHelper
};



//人物buff效果的体现
enum EWeaponBuffEffect {
	//几个设想的基础buff状态,可在此添加

	WbuffLimitBreak, //大招（不确定，只是针对单纯武器基础性能改变的大招，对特殊功能如召唤等大招不确定）
	WbuffStrengthen,  //武器加强buff
	WbuffClean,		//默认状态

	WbuffCombine

};


//人物buff效果的体现
enum EEntityBuffEffect {
	//几个设想的基础buff状态,可在此添加
	EbuffFrozen,	//冻结	
	EbuffPoisoned,	//中毒
	EbuffBurning,	//火烧（爆炸？）
	EbuffSpeedUp,	//加速
	EbuffSlowDown,	//减速


	EbuffLimitBreak, //大招（不确定，只是针对单纯基础性能改变的大招，对特殊功能如召唤等大招不确定）
	EbuffInvincible,//无敌(可能有护盾状态?)

	EbuffClean			//默认状态

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
#define HIT_WHEN_COLLIDE_WITH_ENEMY 1 //与普通敌人相撞扣血量
#define KNOCKBACK_DISTANCE 20//被击退后退的距离
#define KNOCKBACK_TIME 0.1f//被击退持续的时间


#define INVINCIBLE_TIME 2.0f //受伤后的无敌时间
//Knight
#define KNIGHT_HP 10
#define KNIGHT_MP 200
#define KNIGHT_SPEED 6
#define KNIGHT_ARMOR 5





#define CHARGER_HP 25
#define CHARGER_SPEED 1
#define CHARGER_CHARGE_SPEED 2
#define CHARGER_ATK 0 //预想的是直接用碰撞伤害 
#define CHARGER_MAX_MOVES_ROUND 50
#define CHARGER_MAX_CHARGES_ROUND 100//最大冲撞距离
#define CHARGER_MOVE_PAUSE_TIME 3.0f

#define MUMMY_HP 8
#define MUMMY_SPEED 2
#define MUMMY_CHARGE_SPEED 5
#define MUMMY_ATK 0 //预想的是直接用碰撞伤害 
#define MUMMY_MAX_MOVES_ROUND 50
#define MUMMY_MAX_CHARGES_ROUND 300//最大冲撞距离
#define MUMMY_MOVE_PAUSE_TIME 3.0f


//Ranger
#define RANGER_HP 15
#define RANGER_SPEED 2
#define RANGER_ATK 3

#define RANGER_MAX_MOVES_ROUND 50//每次进行移动时最大移动的距离 为 MAX_MOVES_ROUND*RANGER_SPEED 
#define RANGER_MOVE_PAUSE_TIME 3.0f//进行完一轮移动后原地等待的时间

#define TOWER_HP 25
#define TOWER_SPEED 2
#define TOWER_ATK 4

#define TOWER_MAX_MOVES_ROUND 50//每次进行移动时最大移动的距离 为 MAX_MOVES_ROUND*RANGER_SPEED 
#define TOWER_MOVE_PAUSE_TIME 3.0f//进行完一轮移动后原地等待的时间


//武器类型名与所属名
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

//一些时间间隔
#define SWITCH_TIMESPACE 0.6f
#define PICK_TIMESPACE 0.7f




//controller的标识
#define CONTROLLER_TAG 9999
//pause的标识
#define PAUSE_TAG 8999

//加速区域加速后的速度
#define ACCELERATE_KNIGHT_SPEED 9

//加速时间
#define ACCELERATE_TIME 1.2f
#define ACCELERATE_TOUCHRANGE  27.0f

//状态框创建标识
#define QHP 1
#define QARMOR 2
#define QMP 3

//状态框标识
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
#define HIT_WHEN_COLLIDE_WITH_ENEMY 1 //与普通敌人相撞扣血量
#define KNOCKBACK_DISTANCE 80//被击退后退的距离
#define KNOCKBACK_TIME 0.1f//被击退持续的时间

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