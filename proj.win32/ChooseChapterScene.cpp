#include "ChooseChapterScene.h"
#include "cocos2d.h"
#include "StaticData.h"
#include "StartScene.h"
#include "ChooseRoundScene.h"
#include "UserData.h"
USING_NS_CC;
ChooseChapterScene* ChooseChapterScene::create()
{
	ChooseChapterScene* scene = new ChooseChapterScene();
	scene->init();
	scene->autorelease();
	return scene;
}

bool ChooseChapterScene::init()
{
	currentChapter = 0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* backgroundSprite = CCSprite::create(STATIC_DATA_STRING("choose_chapter_background"));

	backgroundSprite->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
	this->addChild(backgroundSprite,0);
	CCMenuItemImage * returnHomeItem = CCMenuItemImage::create(STATIC_DATA_STRING("choose_chapter_home_normal"),STATIC_DATA_STRING("choose_chapter_home_selected"),this,menu_selector(ChooseChapterScene::returnMainMenuCallback));
	returnHomeItem->setPosition(ccp(returnHomeItem->getContentSize().width/2,winSize.height-returnHomeItem->getContentSize().height/2));

	CCMenuItemImage * lastItem = CCMenuItemImage::create(STATIC_DATA_STRING("choose_chapter_last_button_normal"),STATIC_DATA_STRING("choose_chapter_last_button_selected"),this,menu_selector(ChooseChapterScene::showLastChapterCallback));
	lastItem->setPosition(ccp(lastItem->getContentSize().width,winSize.height/2));
	CCMenuItemImage* nextItem = CCMenuItemImage::create(STATIC_DATA_STRING("choose_chapter_next_button_normal"),STATIC_DATA_STRING("choose_chapter_next_button_selected"),this,menu_selector(ChooseChapterScene::showNextChapterCallback));
	nextItem->setPosition(ccp(winSize.width-nextItem->getContentSize().width,winSize.height/2));
	CCDictionary* staticData = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* gamesceneDict =dynamic_cast<CCDictionary*>( staticData->objectForKey("gamescene"));
	totalChapterNumber = gamesceneDict->valueForKey("total_chapter_number")->intValue();
	openChapterNumber = gamesceneDict->valueForKey("open_chapter_number")->intValue();

	CCDictionary* chapterDict = dynamic_cast<CCDictionary*>(gamesceneDict->objectForKey(CCString::createWithFormat("chapter_%d",this->currentChapter)->getCString()));
	introductionImage = CCMenuItemImage::create(chapterDict->valueForKey("introduction_image")->getCString(),chapterDict->valueForKey("introduction_image")->getCString(),this,menu_selector(ChooseChapterScene::chooseChapterCallback));
	introductionImage->setPosition(winSize.width/2,winSize.height/2);
	introductionImage->setTag(INTRODUCTIONIMAGE);
	CCMenu* menu = CCMenu::create(returnHomeItem,lastItem,nextItem,introductionImage,NULL);	

	menu->setTag(MENU);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	return true;
}
CCDictionary* ChooseChapterScene::getGamesceneDict(){
	CCDictionary* staticData = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* gamesceneDict =dynamic_cast<CCDictionary*>( staticData->objectForKey("gamescene"));
	return gamesceneDict;
}
CCDictionary* ChooseChapterScene::getCurrentChapterDict(){
	CCDictionary* chapterDict = dynamic_cast<CCDictionary*>(this->getGamesceneDict()->objectForKey(CCString::createWithFormat("chapter_%d",this->currentChapter)->getCString()));
	return chapterDict;
}
void ChooseChapterScene::showNextChapterCallback( CCObject *pSender )
{
	if(this->currentChapter+1<this->totalChapterNumber){
		this->currentChapter++;
		this->resetIntroductionImage();
	}
}

void ChooseChapterScene::resetIntroductionImage(){
	CCMenu* menu = (CCMenu*)this->getChildByTag(MENU);
		menu->removeChildByTag(INTRODUCTIONIMAGE,true);
	if(this->currentChapter < this->openChapterNumber){
		if(USER->openRounds[this->currentChapter]>0){
			this->introductionImage = CCMenuItemImage::create(this->getCurrentChapterDict()->valueForKey("introduction_image")->getCString(),this->getCurrentChapterDict()->valueForKey("introduction_image")->getCString(),this,menu_selector(ChooseChapterScene::chooseChapterCallback));
		}
		else{
			this->introductionImage = CCMenuItemImage::create(this->getCurrentChapterDict()->valueForKey("locked_introduction_image")->getCString(),this->getCurrentChapterDict()->valueForKey("locked_introduction_image")->getCString(),this,menu_selector(ChooseChapterScene::chooseChapterCallback));
		}

	}
	else{
		this->introductionImage=CCMenuItemImage::create(this->getGamesceneDict()->valueForKey("under_construction_image")->getCString(),this->getGamesceneDict()->valueForKey("under_construction_image")->getCString(),this,menu_selector(ChooseChapterScene::chooseChapterCallback));
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->introductionImage->setPosition(winSize.width/2,winSize.height/2);
	this->introductionImage->setTag(INTRODUCTIONIMAGE);
	menu->addChild(this->introductionImage);
}

void ChooseChapterScene::showLastChapterCallback( CCObject *pSender )
{
	if(this->currentChapter>0){
		this->currentChapter--;
		this->resetIntroductionImage();
	}
	
}

void ChooseChapterScene::chooseChapterCallback( CCObject *pSender )
{
	if(this->currentChapter<this->openChapterNumber){
		if(USER->openRounds[this->currentChapter]>0){
			CCTransitionShrinkGrow* transitionToChooseRoundScene = CCTransitionShrinkGrow::create(0.30f,ChooseRoundScene::create(this->currentChapter));	
			CCDirector::sharedDirector()->replaceScene(transitionToChooseRoundScene);
		}
	}
}

void ChooseChapterScene::returnMainMenuCallback( CCObject *pSender )
{
	CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
	CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
}
