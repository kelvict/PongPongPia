#pragma once
#include"cocos2d.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;
typedef enum{
	MENU=0,
	INTRODUCTIONIMAGE
}ChooseChapterSceneTag;
class ChooseChapterScene :
	public cocos2d::CCScene
{
public:
	static ChooseChapterScene* create();
	bool init();

	CC_SYNTHESIZE(int,currentChapter,CurrentChapter);
	CC_SYNTHESIZE(CCMenuItemImage*, introductionImage,IntroductionImage);
	CC_SYNTHESIZE(int, totalChapterNumber,TotalChapterNumber);
	CC_SYNTHESIZE(int,openChapterNumber,OpenChapterNumber);

	void showNextChapterCallback(CCObject *pSender);
	void showLastChapterCallback(CCObject *pSender);
	void chooseChapterCallback(CCObject *pSender);
	void returnMainMenuCallback(CCObject *pSender);
	CCDictionary* getGamesceneDict();
	CCDictionary* getCurrentChapterDict();
	void resetIntroductionImage();
};

