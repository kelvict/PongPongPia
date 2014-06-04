#pragma once
#include"cocos2d.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;

class ChooseRoundScene :
	public cocos2d::CCScene
{
public:
	static ChooseRoundScene* create(int ChapterNumber);
	bool init(int ChapterNumber);

	CC_SYNTHESIZE(int,currentChapterNumber,CurrentChapterNumber);
	CC_SYNTHESIZE(int,totalRoundNumber,TotalRoundNumber);
	CC_SYNTHESIZE(int,openRoundNumber,OpenRoundNumber);


	void returnMainMenuCallback(CCObject *pSender);
	void getBackCallback(CCObject *pSender);
	void chooseRoundCallback(CCObject *pSender);

	CCDictionary* getGamesceneDict();
	CCDictionary* getCurrentChapterDict();
	void resetIntroductionImage();
	int getNumberItemTag(int itemNumber);
	int getChooseNumber(int chooseNumber);
	void chooseLockedRound(CCObject* pSender);
};

