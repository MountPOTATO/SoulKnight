#include "Arms/Gun.h"

class SMG :public Gun {
public:
	static SMG* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);



};