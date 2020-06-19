#include "Arms/Melee.h"

class Wand :public Melee {
public:
	static Wand* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);


};