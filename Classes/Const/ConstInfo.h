#ifndef __CONSTINFO_H__
#define __CONSTINFO_H__

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

#endif