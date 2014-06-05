#pragma once
#include <cocos2d.h>
#include "cocos2d.h"
#include <StartScene.h>

class ResultLayer :
	public cocos2d::CCLayer
{
public:
	static ResultLayer* create(bool hasWon);
	bool init(bool hasWon);
	
	CC_SYNTHESIZE(bool,hasWon,HasWon);
	
	void returnMainMenu(CCObject* pSender);
	void retry(CCObject* pSender);
	void playNext(CCObject* pSender);
	void showReward();
	
	void createBackgroundAndButtons();
};

