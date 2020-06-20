#pragma once
#include "Entity/Character.h"

class Knight :public Character {
public:
	CREATE_FUNC(Knight);
	virtual bool init();

public:
	bool UseSkill();
	
private:
	int HeroID = 1;//仅仅是个标识，应该没什么实际用处

};