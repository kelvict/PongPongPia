#include "LoseLayer.h"
#include "StaticData.h"
#include "GameScene.h"
#include "ChallengeScene.h"
#include"CurlUtils.h"
#include"Utils.h"
#include "JsonBox.h"
#include "ChooseRoundScene.h"
USING_NS_CC;

void LoseLayer::registerWithTouchDispatcher(){
	// 这里的触摸优先级设置为 -128 这保证了，屏蔽下方的触摸
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool LoseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	//
	CCLog("LoseLayer touch");
	return true;
}

bool LoseLayer::init()
{
	//
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		this->setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void LoseLayer::playAgain(CCObject *pSender)
{
	GameScene* curGamescene = (GameScene*)this->getParent();
	GameScene* gamescene ;
	if(curGamescene->getGameType()==k_Normal_Game){
		gamescene = GameScene::createWithGameNumber(GameScene::curChapterNum,GameScene::curRoundNum);
		this->removeFromParentAndCleanup(true);
		CCTransitionShrinkGrow* transitionScene = CCTransitionShrinkGrow::create(0.30f,gamescene);
		CCDirector::sharedDirector()->replaceScene(transitionScene);	
	}
	else{
		curGamescene->getOtherRoles()->retain();
		curGamescene->getRewards()->retain();
		this->removeFromParentAndCleanup(true);
		ChallengeScene* challengeScene = ChallengeScene::create();
		CCTransitionShrinkGrow* transitionToChanllengeScene = CCTransitionShrinkGrow::create(0.30f,challengeScene);
		CCDirector::sharedDirector()->replaceScene(transitionToChanllengeScene);
	}

	CCLog("Play Again");
}

void LoseLayer::onEnter()
{
	CCLayer::onEnter();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* background = CCSprite::create(STATIC_DATA_STRING("lose_background"));
	//CC_BREAK_IF(!background);
	this->addChild(background);
	background->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));

	CCSprite* loseFont = CCSprite::create(STATIC_DATA_STRING("result_lose"));
//	CC_BREAK_IF(!loseFont);
	this->addChild(loseFont);
	loseFont->setPosition(ccp(winSize.width*0.5, winSize.height*0.8));

	CCMenuItemImage *retry = CCMenuItemImage::create(
		STATIC_DATA_STRING("retry_normal"),
		STATIC_DATA_STRING("retry_click"),
		this,
		menu_selector(LoseLayer::playAgain));
	CCMenuItemImage *giveupButton = CCMenuItemImage::create(
		STATIC_DATA_STRING("giveup_normal"),
		STATIC_DATA_STRING("giveup_click"),
		this,
		menu_selector(LoseLayer::giveupCallback));
	retry->setPosition(-4.0/7*retry->getContentSize().width,0);
	giveupButton->setPosition(4.0/7*giveupButton->getContentSize().width,0);
	//retry->setPosition(ccp(winSize.width*0.5, winSize.height*0.15));
	CCMenu* menu = CCMenu::create(retry,giveupButton, NULL);
	//this->addChild(retry);
	this->addChild(menu);
	menu->setPosition(ccp(winSize.width*0.5, winSize.height*0.15));
	
	GameScene* gamescene = (GameScene*)this->getParent();
	if(gamescene->getGameType()==k_Chanllenge_Game){
		Role* challengee = (Role*)gamescene->getOtherRoles()->objectAtIndex(0);
		map<string,string> post;
		post["api"] = "set_battle_record";
		post["username"] = USER->getUsername().getCString();
		post["password"] = USER->getPassword().getCString();
		post["enemy_name"] = challengee->getUsername().getCString();
		post["has_won"] = "false";

		std::string jsonStr = POST(post);

		JsonBox::Value data;
		CCLOG(jsonStr.c_str());
		data.loadFromString(jsonStr);
		USER->setPlayOnlineGamesNumber(USER->getPlayOnlineGamesNumber()+1);
		USER->uploadToCloud();
	}

}

void LoseLayer::giveupCallback(CCObject* pSender){
	GameScene* gamescene = (GameScene*) this->getParent();
	if(gamescene->getGameType()==k_Chanllenge_Game){
		CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
		CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
	}
	else if(gamescene->getGameType()==k_Normal_Game){
		CCTransitionShrinkGrow* transitionToChooseRoundScene = CCTransitionShrinkGrow::create(0.30f,ChooseRoundScene::create(GameScene::curChapterNum));	
		CCDirector::sharedDirector()->replaceScene(transitionToChooseRoundScene);	
	}
}

void LoseLayer::onExit()
{
	CCLog("Exit");
	CCLayer::onExit();
}