
#ifndef __LOSESCENE_H__
#define __LOSESCENE_H__

#include "cocos2d.h"

class LoseScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	void menuStartCallBack(cocos2d::Ref* pSender);
	void menuEndCallBack(cocos2d::Ref* pSender);



	CREATE_FUNC(LoseScene);

};

#endif