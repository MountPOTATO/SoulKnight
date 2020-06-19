#include "Arms/Melee.h"

class Fish :public Melee {
public:
	static Fish* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);



};