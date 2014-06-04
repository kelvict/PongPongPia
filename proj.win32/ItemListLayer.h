//
//  ItemListLayer.h
//  PongPongPia
//
//  Created by HuFan on 13-11-7.
//
//

#ifndef __PongPongPia__ItemListLayer__
#define __PongPongPia__ItemListLayer__

#include "cocos2d.h"
#include "Reward.h"
#include "GameScene.h"
#include "string.h"

/**
	物品列表
	enum rewardType{}
	enum rewardType{} 
	int itemType;             
*/
class ItemListLayer : public cocos2d::CCLayer
{
public:
	//static ItemListLayer* create(RewardType rewardType, int itemType, int quantity);
	static ItemListLayer* create(CCArray* rewards = NULL);
	void removeFromParentCallback(CCObject* pSender);
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	
protected:
	void showWindows();
	void createSureAndButtons();
	virtual void removeFromParentAndCleanup();
	bool initNewRewardWindows(CCArray* rewards);
	void showGetReward(Reward* reward, int number);
	static std::string makeEquipmentPropertiesStringFromRewardDict(CCDictionary* rewardDict);
	void confirmCallback( CCObject* pSender );
	void returnToChooseRoundCallback(CCObject* pSender);
	void showShareWindow(CCNode* that, int PositionX=CCDirector::sharedDirector()->getWinSize().width/2,int PositonY=CCDirector::sharedDirector()->getWinSize().height/2);
	void shareCallback(CCObject* pSender);
};


#endif