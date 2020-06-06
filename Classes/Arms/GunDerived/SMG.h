#include "Arms/Gun.h"

class SMG :public Gun {
public:
	static SMG* create(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);

	virtual bool init(const char* weaponImageName1, const char* weaponImageName2,
		HelloWorld* currentScene, ESide side, bool _heroOwned);



	void setOwner(Entity* owner) { _owner = owner; }

	void updateCurrentLocation();

public:
	void setTiledMap(TMXTiledMap* map) {
		m_map = map;
		this->meta = m_map->getLayer("Meta");
		this->meta->setVisible(false);
	}
	Point tileCoordForPosition(Point pos) {
		Size mapTiledNum = m_map->getMapSize();
		Size tiledSize = m_map->getTileSize();
		int x = pos.x / tiledSize.width;
		int y = (mapTiledNum.height * tiledSize.height - pos.y) / tiledSize.height;
		return Point(x, y);
	}
	void setWeaponTiledMap(TMXTiledMap* map) {
		m_map = map;
		this->meta = m_map->getLayer("Meta");
		this->meta->setVisible(false);
	}



private:
	TMXTiledMap* m_map;
	TMXLayer* meta;
};