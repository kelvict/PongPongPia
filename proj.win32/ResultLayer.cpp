#include "ResultLayer.h"
#include "StaticData.h"
#include "PersonalAudioEngine.h"
#include <cocos2d.h>

USING_NS_CC;

enum{
	result_background_tag
}child_tag;

ResultLayer* ResultLayer::create(bool hasWon){
	ResultLayer* resultLayer = new ResultLayer();
	resultLayer->init(hasWon);
	resultLayer->autorelease();
	return resultLayer;
}

bool ResultLayer::init(bool hasWon){
	if(CCLayer::init()){
		this->setHasWon(hasWon);
		this->createBackgroundAndButtons();
		return true;
	}
	return false;
}

void ResultLayer::createBackgroundAndButtons(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	if(this->getHasWon()==true){
		CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("win_background"));
		
		pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
		this->addChild(pBg,0,result_background_tag);
		
		CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("win_confirm_normal"),
			STATIC_DATA_STRING("win_confirm_selected"),
			this,
			menu_selector(ResultLayer::returnMainMenu)
			);
		CCMenu* menu = CCMenu::create(pBackItem,NULL);
		menu->setPosition(CCPointMake(winSize.width/2,winSize.height/7));	
		pBg->addChild(menu);
		//PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("victory_music"),true);
	}
	else{
		CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("lose_background"));

		pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
		this->addChild(pBg,0,result_background_tag);

		CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("lose_confirm_normal"),
			STATIC_DATA_STRING("lose_confirm_selected"),
			this,
			menu_selector(ResultLayer::returnMainMenu)
			);
		CCMenu* menu = CCMenu::create(pBackItem,NULL);
		menu->setPosition(CCPointMake(winSize.width/2,winSize.height/7));
		pBg->addChild(menu);
		//PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("failed_music"),true);
	}
}
void ResultLayer::returnMainMenu(CCObject* pSender){
	//PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());
	CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
}

void ResultLayer::retry(CCObject* pSender){
	//todo
}

void ResultLayer::playNext(CCObject* pSender){
	//todo
};

void ResultLayer::showReward(){
	//todo
};

