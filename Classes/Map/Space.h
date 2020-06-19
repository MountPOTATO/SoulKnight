
#ifndef __SPACE_H__
#define __SPACE_H__
#include "Const/ConstInfo.h"

#include <sstream>

class HelloWorld;

class Space :public cocos2d::Node {
public:
	//Space() {};
	static Space* create(HelloWorld* scene,Space* pre=nullptr,const int mType=0,const int mDir=0);
	virtual Space* append(HelloWorld* scene, const int dir);
	cocos2d::CCTMXTiledMap* getMap() { return map; }
	cocos2d::Point getExitPointPos(int dir);
	std::vector<int>exitInfo;
	std::string mapID;
	void resetAnchor(cocos2d::Vec2 psntAnchor);
	bool isInBound(cocos2d::Point pos);
	bool isExitExist(const std::string str,const char* target);
	int count;
	cocos2d::Vec2 place;
	bool setPlace(HelloWorld* scene, Space* pre,const int dir);
private:
	virtual bool init(HelloWorld* scene,Space* pre = nullptr, const int mType = 0, const int mDir = 0);
	cocos2d::Point getAnchorPointWithDir(const int dir);
	std::string getRandomIDWithDir(HelloWorld* scene,const int dir,const int exitNum);
	static cocos2d::CCTMXTiledMap* createMapWithID(std::string str);
	cocos2d::CCTMXTiledMap* map;
	int type;
	bool isDirAvailable(HelloWorld*scene,cocos2d::Vec2 plc,int dir);
	int parentDir;
};


#endif