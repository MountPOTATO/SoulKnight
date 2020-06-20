
#ifndef __WINSCENE_H__
#define __WINSCENE_H__


#include "cocos2d.h"

class WinScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();


	void menuStartCallBack(cocos2d::Ref* pSender);
	void menuEndCallBack(cocos2d::Ref* pSender);



	CREATE_FUNC(WinScene);

};


#endif