#pragma once
#ifndef __SPACE_H__
#define __SPACE_H__
#include "Constant.h"
//#include"StartExplore.h"
#include <sstream>


class Space :public cocos2d::Node {
public:
	//Space() {};
	static Space* create(Space* pre=nullptr,const int mType=0,const int mDir=0);
	virtual Space* append(cocos2d::Node* scene,const int dir);
	cocos2d::CCTMXTiledMap* getMap() { return map; }
	cocos2d::Point getExitPointPos(int dir);
	std::vector<int>exitInfo;
	std::string mapID;
	void resetAnchor(cocos2d::Vec2 psntAnchor);
private:
	virtual bool init(Space* pre = nullptr, const int mType = 0, const int mDir = 0);
	std::string getExitPointStr(const int dir);
	std::string getExitObjectStr(const int dir);
	cocos2d::Point getAnchorPointWithDir(const int dir);
	std::string getRandomIDWithDir(const int dir);
	static cocos2d::CCTMXTiledMap* createMapWithID(std::string str);
	cocos2d::CCTMXTiledMap* map;
	int type;
	int count;
};


#endif