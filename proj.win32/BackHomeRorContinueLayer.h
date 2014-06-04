#pragma once
#include <cocos2d.h>
#include "GameScene.h"
#include"Equipment.h"
#include "Role.h"
#include "UserData.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class BackHomeRorContinueLayer:public cocos2d::CCLayer
{
public:
	static BackHomeRorContinueLayer* create();
	bool init();

	void DrawEndBackground();
	void DrawBackHome();
	void DrawContinue();

	void ClickBackHome(CCObject* pSender);
	void ClickContinue(CCObject* pSender);

void displayOn(cocos2d::CCNode* node);
	
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);//¥•∆¡œÏ”¶
};