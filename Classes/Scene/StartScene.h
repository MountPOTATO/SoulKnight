
#ifndef __STARTSCENE_H__
#define __STARTSCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	
	void menuStartCallBack(cocos2d::Ref* pSender);
	void menuEndCallBack(cocos2d::Ref* pSender);
	void menuMusicCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(StartScene);

};

#endif