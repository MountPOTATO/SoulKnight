#include "StartExplore.h"

USING_NS_CC;

std::vector<std::string> exitRightMaps;
std::vector<std::string>exitLeftMaps;
std::vector<std::string> exitUpMaps;
std::vector<std::string>exitDownMaps;
std::vector<std::string>corridors;

Scene* ExploreScene::createScene()
{
	return ExploreScene::create();
}

bool ExploreScene::init()
{
	if (!Scene::init())
		return false;
	appliedSpace = *(new std::vector<Space*>);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	initMaps();
	auto actor= Sprite::create("Knight.png");
	if (actor != nullptr)
	{
		actor->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*2 / 3 + origin.y));
		//actor->setAnchorPoint(Vec2::ZERO);
		//actor->setPosition(87,7);
		this->addChild(actor, 1);
		knight = actor;
		
	}
	this->scheduleUpdate();
	return true;
}


void ExploreScene::update(float dt)
{
	updateMap();
}

void ExploreScene::updateMap()
{
	for (int j=0;j<appliedSpace.size();j++)
	{
		for (int i = 1; i<=4; i++)
		{
			if (i > appliedSpace[j]->exitInfo.size())
			{
				log("exitInfo out of range.");
			}
			else
			{
				if (appliedSpace[j]->exitInfo[i] == E_UNAPPENDED)//存在出口未延伸
				{
					Point exitPos = appliedSpace[j]->getExitPointPos(i);//上下型为y，左右型为x
					auto visibleSize = Director::getInstance()->getVisibleSize();
					Vec2 origin = Director::getInstance()->getVisibleOrigin();
					if (i % 2 && exitPos.y >= origin.y && exitPos.y <= origin.y + visibleSize.height)//上下断口在画面内
					{
						Space* temp = appliedSpace[j]->append(this, i);
						if (temp != nullptr)
						{
							this->appliedSpace.push_back(temp);
							appliedSpace[j]->exitInfo[i] = E_APPENDED;
							int otherExit = i > 2 ? i - 2 : i + 2;
							appliedSpace[appliedSpace.size() - 1]->exitInfo[otherExit] = E_APPENDED;
						}
					}
					else if (!(i % 2) && exitPos.x >= origin.x && exitPos.x <= origin.x + visibleSize.width)//左右断口在画面内
					{
						Space* temp = appliedSpace[j]->append(this, i);
						if (temp != nullptr)
						{
							this->appliedSpace.push_back(temp);
							appliedSpace[j]->exitInfo[i] = E_APPENDED;
							int otherExit = i > 2 ? i - 2 : i + 2;
							appliedSpace[appliedSpace.size()-1]->exitInfo[otherExit] = E_APPENDED;
						}
					}
				}
			}
		}
	}
	for (int j = 0; j < appliedSpace.size(); j++)
	{
		auto map = appliedSpace[j]->getMap();
		map->setPosition(map->getPosition()+Vec2(0,1));
	}
}

bool ExploreScene::initMaps()
{
	std::string squareRoom = "SquareRoom.tmx";
	std::string verticalCorridor="VerticalCorridor.tmx";
	std::string horizontalCorridor="HorizontalCorridor.tmx";
	std::string monsterRoom4Exits = "MonsterRoom4Exits.tmx";
	exitDownMaps = { squareRoom,monsterRoom4Exits };
	exitRightMaps = { squareRoom,monsterRoom4Exits };
	exitUpMaps = { monsterRoom4Exits };
	exitLeftMaps = { monsterRoom4Exits };
	corridors = { verticalCorridor,horizontalCorridor };
	auto firstRoom = Space::create();
	if(firstRoom!=nullptr)
	{
		auto firstMap = firstRoom->getMap();
		//auto firstMap = CCTMXTiledMap::create(squareRoom);
		if (firstMap != nullptr)
		{
			this->addChild(firstMap, 0);
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			firstMap->setAnchorPoint(Vec2(0.5, 0.5));
			firstMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height*2 / 3 + origin.y));
			//firstMap->setPosition(Vec2(origin.x+20, visibleSize.height/2+ origin.y));
			auto curAnc = firstMap->getAnchorPoint();
			auto curPos = firstMap->getPosition();
			firstRoom->resetAnchor(Vec2(0.5,0.5));
			this->curMap = firstMap;
			this->appliedSpace.push_back(firstRoom);
			return true;
		}
		log("Map access failed!");
		return false;
	}
	log("Room building failed!");
	return false;
}

