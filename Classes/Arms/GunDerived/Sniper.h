#include "Arms/Gun.h"

class Sniper :public Gun {
public:
	static Sniper* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);



};