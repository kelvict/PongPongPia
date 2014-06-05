#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class StartLayer : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	CREATE_FUNC(StartLayer);
	virtual bool init();
	void startGame(CCObject *pSender);
	void quitGame(CCObject *pSender);
	void audioAndUserDataInit();
	void cacheInit();

protected:
	//void onEnterTransitionDidFinish();
	//void onExitTransitionDidStart();
};

#endif  // __Start_SCENE_H__