#include"StartExplore.h"
#include <cstring>


USING_NS_CC;


Space* Space::create(Space* pre, const int mType, const int mDir)
{
	Space* room = new Space;
	if (room != nullptr&&room->init(pre,mType,mDir))
	{
		//room->autorelease();
		return room;
	}
	CC_SAFE_DELETE(room);
	return nullptr;
}

bool Space::init(Space* pre,const int mType, const int mDir)
{
		if (pre==nullptr)//创建的是第一个房间
		{
			this->count = 1;
			this->type = ROOM;
			this->map = createMapWithID(exitRightMaps[0]);
			this->mapID = exitRightMaps[0];
			this->exitInfo = {NONE,E_UNAPPENDED, E_UNAPPENDED, NONE, NONE};
			return true;
		}
		this->count = pre->count + 1;
		if (pre->type==ROOM)//创建走廊
		{
			this->type = mType;
			this->map = createMapWithID(corridors[mType]);
			this->mapID = corridors[mType];
			if (mapID == corridors[H_CORI])
			{
				exitInfo = { NONE,NONE,E_UNAPPENDED,NONE,E_UNAPPENDED };
			}

			else
			{
				exitInfo = { NONE,E_UNAPPENDED,NONE,E_UNAPPENDED,NONE };
			}
			return true;
		}
		//创建某种房间
		this->mapID = getRandomIDWithDir(mDir);
		if (mapID != "0")
		{
			this->map = createMapWithID(mapID);
			this->type = ROOM;
			if (mapID == "SquareRoom.tmx")
			{
				this->exitInfo = { NONE,E_UNAPPENDED, E_UNAPPENDED, NONE, NONE };
			}
			else if (mapID == "MonsterRoom4Exits.tmx")
			{
				this->exitInfo = {NONE,E_UNAPPENDED,E_UNAPPENDED,E_UNAPPENDED,E_UNAPPENDED};
			}
			return true;
		}
		return false;
}

/*Vec2 Space::adaptPos(Vec2 origin)
{
	return Vec2(origin.x + 196, origin.y - 20);
}*/

Space* Space::append(cocos2d::Node* scene,const int dir)
{
	if (this->type == ROOM)//房间接走廊
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto mapSize = map->getMapSize();
		Space* newCori;
		if (dir % 2)
			newCori = Space::create(this, V_CORI, dir);
		else
			newCori = Space::create(this, H_CORI, dir);
		auto roomMap = this->map;
		auto coriMap = newCori->map;
		scene->addChild(coriMap,0);
		auto anchorPoint = getAnchorPointWithDir(dir);
		coriMap->setAnchorPoint(anchorPoint);
		//auto roomPoints = roomMap->getObjectGroup("points");
		//auto roomExitPoint = roomPoints->getObject(getExitPointStr(dir));
		coriMap->setPosition(getExitPointPos(dir));
		newCori->resetAnchor(anchorPoint);
		return newCori;
	}
	else//走廊接房间
	{
		Space* newRoom = Space::create(this, ROOM, dir);
		if (newRoom != nullptr)
		{
			auto roomMap = newRoom->map;
			auto coriMap = this->map;
			scene->addChild(roomMap, 0);
			auto anchorPoint = getAnchorPointWithDir(dir);
			roomMap->setAnchorPoint(anchorPoint);
			roomMap->setPosition(getExitPointPos(dir));
			newRoom->resetAnchor(anchorPoint);
			return newRoom;
		}
		return nullptr;
	}
}

/*float Space::getExitPos(int dir)
{
	auto exitMarks=map->getObjectGroup("exitMark");
	auto exitMark = exitMarks->getObject(getExitObjectStr(dir));
	if (dir % 2)//上下型
		return exitMark.at("y").asFloat()+map->getPosition().y;
	else
		return exitMark.at("x").asFloat()+map->getPosition().x;
}*/

cocos2d::CCTMXTiledMap* Space::createMapWithID(std::string str)
{
	return CCTMXTiledMap::create(str);
}

void Space::resetAnchor(Vec2 psntAnchor)
{
	auto mapSize = map->getMapSize();
	auto psntPos = map->getPosition();
	auto tileSize = map->getTileSize();
	Point nPos = Point(psntPos.x - mapSize.width * psntAnchor.x * tileSize.width /2.0915,
		psntPos.y - mapSize.height * psntAnchor.y * tileSize.height/2.0915);
	map->setPosition(nPos);
	auto curPos=map->getPosition();
	map->setAnchorPoint(Vec2::ZERO);
}

Point Space::getExitPointPos(int dir)
{
	auto mapSize = map->getMapSize();
	auto mapPos = map->getPosition();
	auto tileSize = map->getTileSize();
	switch (dir) 
	{
	case(UP):
	{
		float x = mapPos.x + mapSize.width / 2 * tileSize.width/2.09;
		float y = mapPos.y + mapSize.height * tileSize.height/2.09;
		return Point(x, y);
	}
	case(DOWN):
	{
		float x = mapPos.x + mapSize.width / 2 * tileSize.width/2.09;
		float y = mapPos.y;
		return Point(x, y)+Point(0,10);
	}
	case(LEFT):
	{
		float x = mapPos.x;
		float y = mapPos.y + mapSize.height / 2 * tileSize.height/2.09;
		return Point(x,y)+Point(10,-2);
	}
	case (RIGHT):
	{
		float x = mapPos.x + mapSize.width * tileSize.width / 2.09;
		float y = mapPos.y + mapSize.height / 2 * tileSize.height/2.09;
		return Point(x,y)+Point(-9,-2);
	}
	default:
		return Point::ZERO;
	}
}

std::string Space::getExitObjectStr(const int dir)
{
	std::ostringstream foreMsg;
	std::string msg;
	foreMsg << "exit" << dir;
	msg = foreMsg.str();
	return msg;
}

std::string Space::getExitPointStr(const int dir)
{
	std::ostringstream foreMsg;
	std::string msg;
	foreMsg << "exit" << dir << "Middle";
	msg = foreMsg.str();
	//const char* finlMsg = msg.c_str();
	return msg;
}

Point Space::getAnchorPointWithDir(const int dir)//指对面接口指向的方向
{
	Point aP;
	switch (dir) 
	{
	case(1):
	{
		aP = Point(0.5, 1);
		break; 
	}
	case(2):
	{
		aP = Point(0, 0.5);
		break;
	}
	case(3):
	{
		aP = Point(0.5, 0);
		break;
	}
	case(4):
	{
		aP = Point(1, 0.5); 
		break;
	}
	default:
		aP = Vec2::ZERO;
	} 
	return aP;
}  

std::string Space::getRandomIDWithDir(const int dir)
{
	switch (dir) 
	{
	case(DOWN):
	{
		int max = exitUpMaps.size() - 1;
		if (max >= 0)
		{
			int target = random(0, max);
			return exitUpMaps[target];
		}
		break;
	}
	case(RIGHT):
	{
		int max = exitLeftMaps.size() - 1;
		if (max >= 0)
		{
			int target = random(0, max);
			return  exitLeftMaps[target];
		}
		break;
	}
	case(UP):
	{
		int max = exitDownMaps.size() - 1;
		if (max >= 0)
		{
			int target = random(0, max);
			return  exitDownMaps[target];
		}
		break;
	}
	case(LEFT):
	{
		int max = exitRightMaps.size() - 1;
		if (max >= 0)
		{
			int target = random(0, max);
			return  exitRightMaps[target];
		}
		break;
	}
	default:
		return "0";
	}
	return "0";
}