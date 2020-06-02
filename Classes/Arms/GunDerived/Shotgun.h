#include "Arms/Gun.h"

class Shotgun :public Gun {
public:
	static Shotgun* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool heroOwned);

	virtual bool runShootingAction();
};