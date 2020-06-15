#ifndef __TREASUREBOX_H__
#define __TREASUREBOX_H__


#include "cocos2d.h"
#include "Interaction/InterContent/ManualPickObject.h"



USING_NS_CC;

class TreasureBox :public ManualPickObject
{
	CC_SYNTHESIZE(bool, _isunUsed, IsUnUsed);
	CC_SYNTHESIZE(int, _randID, RandID);

public:
	static TreasureBox* create
	(Point position, Entity* hero, HelloWorld* scene, HRocker* rocker);

	virtual bool init
	(Point position, Entity* hero, HelloWorld* scene, HRocker* rocker);

	void updateTreasureBoxState();

	bool judgeIsToOpen();

	bool isUnUsed() { return _isunUsed == true; }

	void generateRandomObject();

};

#endif