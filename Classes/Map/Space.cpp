#include"HelloWorldScene.h"
#include"Space.h"
#include<string>
#include <cstring>


USING_NS_CC;


Space* Space::create(HelloWorld* scene,Space* pre, const int mType, const int mDir)
{
	Space* room = new Space;
	if (room != nullptr&&room->init(scene,pre,mType,mDir))
	{
		//room->autorelease();
		return room;
	}
	CC_SAFE_DELETE(room);
	return nullptr;
}

bool Space::init(HelloWorld*scene,Space* pre,const int mType, const int mDir)
{
	this->exitInfo = *(new std::vector<int>(5));
	if (pre == nullptr)//创建的是第一个房间
	{
		this->count = 0;
		this->type = ROOM;
		//std::string startRoom = "StartRoom.tmx";
		this->map = createMapWithID("R1.tmx");
		this->mapID = "R1.tmx";
		this->place = Vec2(0, 2);
		this->exitInfo[0] = NONE;
		this->exitInfo[DOWN] =NONE;
		this->exitInfo[RIGHT] = E_UNAPPENDED;
		this->exitInfo[UP] = NONE;
		this->exitInfo[LEFT] = NONE;
		return true;
	}
	if (pre->type == ROOM)//创建走廊
	{
		this->place = pre->place;
		//scene->placement[place]
		this->type = mType;
		this->map = createMapWithID(corridors[mType]);
		this->mapID = corridors[mType];
		if (mapID == corridors[H_CORI])
		{
			this->exitInfo[0] = NONE;
			this->exitInfo[DOWN] = NONE;
			this->exitInfo[RIGHT] = E_UNAPPENDED;
			this->exitInfo[UP] = NONE;
			this->exitInfo[LEFT] = E_UNAPPENDED;
		}
		else
		{
			this->exitInfo[0] = NONE;
			this->exitInfo[DOWN] = E_UNAPPENDED;
			this->exitInfo[RIGHT] = NONE;
			this->exitInfo[UP] = E_UNAPPENDED;
			this->exitInfo[LEFT] = NONE;
		}
		return true;
	}
	//创建某种房间
	//这里决定接的房间有几个出口
	this->setPlace(scene, pre, mDir);
	int exitNum=0;
	if ((scene->roomNotFull(2) || scene->roomNotFull(3) || scene->roomNotFull(4)))
	{
		for (int i = DOWN; i <= LEFT; i++)
		{
			if (isDirAvailable(scene, this->place, i))
				exitNum++;
		}
		exitNum++;
		if (!scene->roomNotFull(exitNum))
		{
			while (exitNum > 1 && !scene->roomNotFull(exitNum))
				exitNum--;
		}
	}
	else
		exitNum = 1;
	this->mapID = this->getRandomIDWithDir(scene,mDir, exitNum);
	scene->typeNum[exitNum]++;
	if (this->mapID != "0")
	{
		this->map = createMapWithID(mapID);
		this->type = ROOM;
		this->exitInfo[0] = 0;
		this->exitInfo[DOWN] = isExitExist(this->mapID, "D") ? E_UNAPPENDED : NONE;
		this->exitInfo[RIGHT] = isExitExist(this->mapID, "R") ? E_UNAPPENDED : NONE;
		this->exitInfo[UP] = isExitExist(this->mapID, "U") ? E_UNAPPENDED : NONE;
		this->exitInfo[LEFT] = isExitExist(this->mapID, "L") ? E_UNAPPENDED : NONE;
		if (exitInfo[DOWN]&&scene->placement[place.x][place.y - 1==EMPTY])
			scene->placement[place.x][place.y - 1] = APPOINTED;
		if (exitInfo[UP]&& scene->placement[place.x][place.y + 1] ==EMPTY)
			scene->placement[place.x][place.y + 1] = APPOINTED;
		if (exitInfo[LEFT]&& scene->placement[place.x - 1][place.y] ==EMPTY)
			scene->placement[place.x - 1][place.y] = APPOINTED;
		if (exitInfo[RIGHT]&& scene->placement[place.x + 1][place.y] ==EMPTY)
			scene->placement[place.x + 1][place.y] = APPOINTED;
		return true;
	}
	return false;
}

bool Space::setPlace(HelloWorld* scene, Space* pre, const int dir)
{
	auto prePlace = pre->place;
	switch (dir)
	{
	case(DOWN):
		place = prePlace+Vec2(0,-1);
		break;
	case(UP):
		place = prePlace + Vec2(0, 1);
		break;
	case(LEFT):
		place = prePlace + Vec2(-1, 0);
		break;
	case(RIGHT):
		place = prePlace + Vec2(1, 0);
		break;
	}
	if (place.x >= 0 && place.y >= 0 && place.x < PLACE_SIZE && place.y < PLACE_SIZE )//&& scene->placement[place.x][place.y] == EMPTY)
	{
		scene->placement[place.x][place.y] = FULL;
		return true;
	}
	place = Vec2();
	return false;

}

bool Space::isExitExist(const std::string str,const char* target)
{
	if (strstr(str.c_str(), target) == NULL)
		return false;
	else
		return true;
}



Space* Space::append(HelloWorld* scene, const int dir)
{
	if (this->type == ROOM)//房间接走廊
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		auto mapSize = map->getMapSize();
		Space* newCori;
		if (dir % 2)
			newCori = Space::create(scene,this, V_CORI, dir);
		else
			newCori = Space::create(scene,this, H_CORI, dir);
		newCori->parentDir = dir;
		auto roomMap = this->map;
		auto coriMap = newCori->map;
		scene->addChild(newCori,0);
		scene->addChild(coriMap,0);
		auto anchorPoint = getAnchorPointWithDir(dir);
		coriMap->setAnchorPoint(anchorPoint);
		auto exitPos=getExitPointPos(dir);
		coriMap->setPosition(exitPos);
		newCori->resetAnchor(anchorPoint);
		return newCori;
	}
	else//走廊接房间
	{
		Space* newRoom = Space::create(scene,this, ROOM, dir);
		if (newRoom != nullptr)
		{
			scene->roomCount++;
			auto roomMap = newRoom->map;
			auto coriMap = this->map;
			scene->addChild(newRoom, 0);
			scene->addChild(roomMap, 0);
			auto anchorPoint = getAnchorPointWithDir(dir);
			roomMap->setAnchorPoint(anchorPoint);
			auto exitPos = getExitPointPos(dir);
			roomMap->setPosition(exitPos);
			newRoom->resetAnchor(anchorPoint);
			return newRoom;
		}
		return nullptr;
	}
}

bool Space::isInBound(Point pos)
{
	auto mapPos=map->getPosition();
	auto mapSize = map->getMapSize();
	auto tileSize = map->getTileSize();
	if (pos.x >= mapPos.x && pos.y >= mapPos.y&&\
		pos.x <= mapPos.x + mapSize.width * tileSize.width/* / 2.0915*/&&\
		pos.y<=mapPos.y+mapSize.height*tileSize.height/* / 2.0915*/)
		return true;
	return false;
}

CCTMXTiledMap* Space::createMapWithID(std::string str)
{
	return CCTMXTiledMap::create(str);
}

void Space::resetAnchor(Vec2 psntAnchor)
{
	auto mapSize = map->getMapSize();
	auto psntPos = map->getPosition();
	auto tileSize = map->getTileSize();
	Point nPos = Point(psntPos.x - mapSize.width * psntAnchor.x * tileSize.width/* / 2.0915*/,
		psntPos.y - mapSize.height * psntAnchor.y * tileSize.height/* / 2.0915*/);
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
		float x = mapPos.x + mapSize.width / 2 * tileSize.width/* / 2.0915*/;
		float y = mapPos.y + mapSize.height * tileSize.height/* / 2.0915*/;
		return Point(x, y)+Point(0,-30);
	}
	case(DOWN):
	{
		float x = mapPos.x + mapSize.width / 2 * tileSize.width/* / 2.0915*/;
		float y = mapPos.y;
		return Point(x, y)+Point(0,25);
	}
	case(LEFT):
	{
		float x = mapPos.x;
		float y = mapPos.y + mapSize.height / 2 * tileSize.height/* / 2.0915*/;
		return Point(x, y) + Point(20,-2);
	}
	case (RIGHT):
	{
		float x = mapPos.x + mapSize.width * tileSize.width/* / 2.0915*/;
		float y = mapPos.y + mapSize.height / 2 * tileSize.height/* / 2.0915*/;
		return Point(x, y) + Point(-25, -2);//-25
	}
	default:
		return Point::ZERO;
	}
}


Point Space::getAnchorPointWithDir(const int dir)//指对面接口指向的方向
{
	Point aP;
	switch (dir) 
	{
	case(1):
	{
		aP = Point(0.5, 1);//////////////0.5
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

bool Space::isDirAvailable(HelloWorld* scene, Vec2 plc,int dir)
{
	std::vector<std::vector<int>>vec = scene->placement;
	switch (dir)
	{
	case(DOWN):
	{
		if (plc.y - 1 >= 0 && plc.y - 1 < PLACE_SIZE)
		{
			if (vec[plc.x][plc.y - 1] == 0)
				return true;
			else
				return false;
		}
		else 
			return false;
	}
	case(UP):
	{
		if (plc.y + 1 >= 0 && plc.y + 1 < PLACE_SIZE && (!vec[plc.x][plc.y + 1]))
			return true;
		else return false;
	}
	case(LEFT):
	{
		if (plc.x - 1 >= 0 && plc.x - 1 < PLACE_SIZE&& (!vec[plc.x-1][plc.y]))
			return true;
		else return false;
	}
	case(RIGHT):
	{
		if (plc.x + 1 >= 0 && plc.x + 1 < PLACE_SIZE && (!vec[plc.x + 1][plc.y]))
			return true;
		else return false;
	}
	}
}

std::string Space::getRandomIDWithDir(HelloWorld* scene,const int dir,const int exitNum)
{
	switch (dir) 
	{
	case(DOWN):
	{
		bool randable = false;
		int unDir_1=0, unDir_2 = 0;//不能有新房间的方向
		if (exitNum == 4||exitNum==1)
			randable = true;
		else
		{
			for (int i = DOWN; i < LEFT; i++)
			{
				if (i != UP && !isDirAvailable(scene, this->place, i))
				{
					if (unDir_1)
						unDir_2 = i;
					else
						unDir_1 = i;
				}
			}
			if (unDir_1)
			{
				int j = 0;
				for (int i = DOWN; i < LEFT; i++)
				{
					if (exitNum == 2)
					{
						if (i != UP && i != unDir_1 && i != unDir_2)
							break;
					}
					else
						if (i == unDir_1)
							break;
					if (i != UP)
						j++;
				}

				return exitUpMaps[3 * (exitNum - 1) + j];
			}
			else
				randable = true;
		}
		if (randable)
		{
			int max = (3 * exitNum) - 1;
			if (exitUpMaps.size() - 1 >= max)
			{
				int target = random(3 * (exitNum - 1), max);
				return exitUpMaps[target];
			}
		}
		break;
	}
	case(RIGHT):
	{
		bool randable = false;
		int unDir_1 = 0, unDir_2 = 0;//不能有新房间的方向
		if (exitNum == 4 || exitNum == 1)
			randable = true;
		else
		{
			for (int i = DOWN; i < LEFT; i++)
			{
				if (i != LEFT && !isDirAvailable(scene, this->place, i))
				{
					if (unDir_1)
						unDir_2 = i;
					else
						unDir_1 = i;
				}
			}
			if (unDir_1)
			{
				int j = 0;
				for (int i = DOWN; i < LEFT; i++)
				{
					if (exitNum == 2)
					{
						if (i != LEFT && i != unDir_1 && i != unDir_2)
							break;
					}
					else
						if (i == unDir_1)
							break;
					if (j != LEFT)
						j++;
				}
				return exitLeftMaps[3 * (exitNum - 1) + j];
			}
			else
				randable = true;
		}
		if (randable)
		{
			int max = (3 * exitNum) - 1;
			if (exitLeftMaps.size() - 1 >= max)
			{
				int target = random(3 * (exitNum - 1), max);
				return exitLeftMaps[target];
			}
		}
		break;
	}
	case(UP):
	{bool randable = false;
	int unDir_1 = 0, unDir_2 = 0;//不能有新房间的方向
	if (exitNum == 4 || exitNum == 1)
		randable = true;
	else
	{
		for (int i = DOWN; i < LEFT; i++)
		{
			if (i != DOWN && !isDirAvailable(scene, this->place, i))
			{
				if (unDir_1)
					unDir_2 = i;
				else
					unDir_1 = i;
			}
		}
		if (unDir_1)
		{
			int j = 0;
			for (int i = DOWN; i < LEFT; i++)
			{
				if (exitNum == 2)
				{
					if (i != DOWN && i != unDir_1 && i != unDir_2)
						break;
				}
				else
					if (i == unDir_1)
						break;
				if (i != DOWN)
					j++;
			}
			return exitDownMaps[3 * (exitNum - 1) + j];
		}
		else
			randable = true;
	}
	if (randable)
	{
		int max = (3 * exitNum) - 1;
		if (exitDownMaps.size() - 1 >= max)
		{
			int target = random(3 * (exitNum - 1), max);
			return exitDownMaps[target];
		}
	}
	break;
	}
	case(LEFT):
	{
		bool randable = false;
		int unDir_1 = 0, unDir_2 = 0;//不能有新房间的方向
		if (exitNum == 4 || exitNum == 1)
			randable = true;
		else
		{
			for (int i = DOWN; i < LEFT; i++)
			{
				if (i != RIGHT && !isDirAvailable(scene, this->place, i))
				{
					if (unDir_1)
						unDir_2 = i;
					else
						unDir_1 = i;
				}
			}
			if (unDir_1)
			{
				int j = 0;
				for (int i = DOWN; i < LEFT; i++)
				{
					if (exitNum == 2)
					{
						if (i != RIGHT && i != unDir_1 && i != unDir_2)
							break;
					}
					else
						if (i == unDir_1)
							break;
					if (i != RIGHT)
						j++;
				}
				return exitRightMaps[3 * (exitNum - 1) + j];
			}
			else
				randable = true;
		}
		if (randable)
		{
			int max = (3 * exitNum) - 1;
			if (exitRightMaps.size() - 1 >= max)
			{
				int target = random(3 * (exitNum - 1), max);
				return exitRightMaps[target];
			}
		}
		break;
	}
	default:
		return "0";
	}
	return "0";
}