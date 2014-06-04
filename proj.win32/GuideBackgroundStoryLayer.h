#pragma once
#include <cocos2d.h>
#include "GameScene.h"
#include"Equipment.h"
#include "Role.h"
#include "UserData.h"
#include "StoryboardLayer.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class GuideBackgroundStoryLayer:public cocos2d::CCLayer
{
private:
	int order;
public:
	static GuideBackgroundStoryLayer* create();
	bool init();

	void DrawPage();
	void DrawThenOrKnow();
	void DrawJump();

	void ClickThenOrKnow(CCObject* pSender);
	void ClickJump(CCObject* pSender);

	void displayOn(cocos2d::CCNode* node);
	
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);//¥•∆¡œÏ”¶
};