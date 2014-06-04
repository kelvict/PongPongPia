#include "ItemListLayer.h"
#include "Language.h"
#include "ChooseChapterScene.h"
#include "ChooseRoundScene.h"
#include "GameScene.h"
#include "ChallengeScene.h"
#include "StartScene.h"
#include "PopWindowsLayer.h"
#include "UserData.h"
#include "Language.h"
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../proj.android/jni/hellocpp/SocialShare.h"
#endif

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "SocialShare.h"
#endif

USING_NS_CC;

ItemListLayer* ItemListLayer::create(CCArray* rewards)
{
	ItemListLayer* itemListLayer = new ItemListLayer();
	itemListLayer->initNewRewardWindows(rewards);
	itemListLayer->autorelease();
	return itemListLayer;
}

bool ItemListLayer::initNewRewardWindows(CCArray* rewards)
{
	this->showWindows();
	this->createSureAndButtons();
	this->showShareWindow(this,cocos2d::CCDirector::sharedDirector()->getWinSize().width*6/7);
	if(rewards == NULL)
		return false;
	//	show rewards
	for (int i = 0; i < rewards->count(); i++) {
		//this->showGetReward(rewards.)
		Reward* reward = (Reward*)rewards->objectAtIndex(i);
		this->showGetReward(reward, i);
	}
	USER->handleUpgrade(this);
	return true;
}

void ItemListLayer::showWindows()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("reward_window"));
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);
}

void ItemListLayer::showShareWindow(CCNode* that, int PositionX,int PositonY){
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("reward_share_window"));
	pBg->setPosition(ccp(PositionX,PositonY));
	CCMenuItemImage* shareButton = CCMenuItemImage::create(
		STATIC_DATA_STRING("reward_share_button_normal"),
		STATIC_DATA_STRING("reward_share_button_click"),
		that,
		menu_selector(ItemListLayer::shareCallback)
		);
	shareButton->setPosition(0,-shareButton->getContentSize().height);
	CCMenu* menu = CCMenu::create(shareButton,NULL);
	menu->setPosition(pBg->getPositionX(),pBg->getPositionY());
	that->addChild(pBg);
	that->addChild(menu);

}

void ItemListLayer::shareCallback(CCObject* pSender) {
	INFORMATION_BOX("Sharing is under construction!",this);
	// ·ÖÏíÎ¢²© share weibo
	SocialShare::WeiboShare((USER->getUsername().m_sString + CN("weibo_sharing")).c_str());
}

// Í¼Æ¬ºÍÎÄ×ÖÎ»ÖÃÐÅÏ¢µÈ´ýÍ¼Æ¬
void ItemListLayer::showGetReward(Reward* reward, int number)
{
	CCDictionary* rewardDict = (CCDictionary*)StaticData::sharedStaticData()->getStaticDataDictionary()->objectForKey("reward_"+Utils::int2str((int)reward->getType())+"_"+Utils::int2str((int)reward->getItemType())+"_info");
	std::string title = rewardDict->valueForKey("name")->getCString();
	std::string properties="";

	switch(reward->getType()){
		case k_Reward_Money:
			properties = title+"+"+Utils::int2str(reward->getQuantity());
			title = "";
			break;
		case k_Reward_Honor:
			properties = title+"+"+Utils::int2str(reward->getQuantity());
			title = "";
			break;
		case k_Reward_Exp:
			properties = title+"+"+Utils::int2str(reward->getQuantity());
			title = "";
			break;
		case k_Reward_Weapon:
			properties = ItemListLayer::makeEquipmentPropertiesStringFromRewardDict(rewardDict);
			break;
		case k_Reward_Base:
			properties = ItemListLayer::makeEquipmentPropertiesStringFromRewardDict(rewardDict);
			break;
		case k_Reward_Plate:
			properties = ItemListLayer::makeEquipmentPropertiesStringFromRewardDict(rewardDict);
			break;
		case k_Reward_Prop:
			properties = rewardDict->valueForKey("addition_effect")->getCString();
			break;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCString* imgPath = CCString::createWithFormat(STATIC_DATA_STRING("reward_image_format"),(int)reward->getType(),reward->getItemType());
	CCSprite* img = CCSprite::create(imgPath->getCString());
	img->setScale(Reward::scaleRatio[(int)k_Reward_itemlist_item]);
	this->addChild(img);
	img->setPosition(ccp(winSize.width * 0.33, winSize.height * (0.78 - number * 0.22)));
	
	CCString* title2 = CCString::createWithFormat(title.c_str(), 100);
	std::string result = title2->m_sString.append("\n");

	CCString* propertiesStr = CCString::createWithFormat(properties.c_str(), 18);
	result += propertiesStr->m_sString;

	CCLabelTTF* pLabel=CCLabelTTF::labelWithString(
		//rewardString.c_str(),
		result.c_str(),
		CCSizeMake(150,0),
		cocos2d::kCCTextAlignmentRight,
		//	"Arial",
		STATIC_DATA_STRING("word_font"),
		//"Ó×Ô²",
		//"American Typewriter",
		24);

	//pLabel->setAnchorPoint(ccp(0, 0));
	pLabel->setPosition(ccp(winSize.width * 0.63, winSize.height * (0.78 - number * 0.22)));
	pLabel->setColor(ccc3(0, 0, 0));
	this->addChild(pLabel);
}

void ItemListLayer::createSureAndButtons()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("reward_ok_button_normal"),
		STATIC_DATA_STRING("reward_ok_button_click"),
		this,
		menu_selector(ItemListLayer::confirmCallback)
		);

	pBackItem->setPosition(-pBackItem->getContentSize().width*6/10,0);
	CCMenuItemImage* pChooseRoundItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("reward_choose_round_button_normal"),
		STATIC_DATA_STRING("reward_choose_round_button_click"),
		this,
		menu_selector(ItemListLayer::returnToChooseRoundCallback)
		);
	pChooseRoundItem->setPosition(pChooseRoundItem->getContentSize().width*6/10,0);
	CCMenu* menu = CCMenu::create(pBackItem,pChooseRoundItem,NULL);
	menu->setPosition(CCPointMake(winSize.width/2,winSize.height/7));	
	this->addChild(menu);
}

void ItemListLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
	//this->removeFromParentAndCleanup();
}

void ItemListLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if(node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if(array != NULL && array->count()>0){
			CCLOG("Hello");
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void ItemListLayer::removeFromParentCallback( CCObject* pSender )
{
	this->removeFromParentAndCleanup();
}

void ItemListLayer::confirmCallback( CCObject* pSender )
{
	GameScene* curGamescene = (GameScene*)this->getParent();
	if(curGamescene->getGameType()==k_Normal_Game){
		int chapterNum=-1,roundNum=-1;
		if(curGamescene->curRoundNum<5){
			if(curGamescene->curRoundNum<USER->openRounds[curGamescene->curChapterNum]){
				chapterNum=curGamescene->curChapterNum;
				roundNum = curGamescene->curRoundNum+1;
			}
			else{
				chapterNum=-1;
				roundNum=-1;
			}
			roundNum = curGamescene->curRoundNum+1;
		}
		else if(curGamescene->curRoundNum==5){
			if(USER->openRounds[curGamescene->curChapterNum+1]>0){
				chapterNum=curGamescene->curChapterNum+1;
				roundNum=0;
			}
		}
		if(roundNum!=-1&&chapterNum!=-1){
			GameScene* gamescene = GameScene::createWithGameNumber(chapterNum,roundNum);
			CCTransitionShrinkGrow* transitionToGameScene= CCTransitionShrinkGrow::create(0.30f,gamescene);
			CCDirector::sharedDirector()->replaceScene(transitionToGameScene);	
		}
		else{
			ChooseChapterScene* chooseChapterScene = ChooseChapterScene::create();
			CCTransitionShrinkGrow* transitionToChooseChapterScene = CCTransitionShrinkGrow::create(0.30f,chooseChapterScene);
			CCDirector::sharedDirector()->replaceScene(transitionToChooseChapterScene);		
		}
	}
	else if(curGamescene->getGameType() == k_Chanllenge_Game){
		ChallengeScene* challengeScene = ChallengeScene::create();
		CCTransitionShrinkGrow* transitionToChallengeScene = CCTransitionShrinkGrow::create(0.30f,challengeScene);
		CCDirector::sharedDirector()->replaceScene(transitionToChallengeScene);				
	}
}

std::string ItemListLayer::makeEquipmentPropertiesStringFromRewardDict( CCDictionary* rewardDict )
{
	std::string properties="";
	if(rewardDict->valueForKey("STR_increment")->intValue()!=0){
		properties += "  "+CN("STR")+"+"+Utils::int2str(rewardDict->valueForKey("STR_increment")->intValue());
	}
	if(rewardDict->valueForKey("AGI_increment")->intValue()!=0){
		properties += "  "+CN("AGI")+"+"+Utils::int2str(rewardDict->valueForKey("AGI_increment")->intValue());
	}
	if(rewardDict->valueForKey("DEF_increment")->intValue()!=0){
		properties += "  "+CN("DEF")+"+"+Utils::int2str(rewardDict->valueForKey("DEF_increment")->intValue());
	}
	return properties;
}

void ItemListLayer::returnToChooseRoundCallback( CCObject* pSender )
{
	GameScene* gamescene = (GameScene*)this->getParent();
	if(gamescene->getGameType()==k_Normal_Game){
		CCTransitionShrinkGrow* transitionToChooseRoundScene = CCTransitionShrinkGrow::create(0.30f,ChooseRoundScene::create(GameScene::curChapterNum));	
		CCDirector::sharedDirector()->replaceScene(transitionToChooseRoundScene);	
	}
	else{
		CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
		CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
	}

}
