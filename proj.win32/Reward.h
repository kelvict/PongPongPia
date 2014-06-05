#pragma once
#include <cocos2d.h>
#include "UserData.h"
#include "StaticData.h"
typedef enum{
	k_Reward_Weapon,//0
	k_Reward_Base,
	k_Reward_Plate,
	k_Reward_Prop,
	k_Reward_Evolution,
	k_Reward_Exp,//5
	k_Reward_Level,
	k_Reward_Honor,
	k_Reward_Money,
	k_Reward_AGI,//9
	k_Reward_STR,
	k_Reward_DEF
}RewardType;


typedef enum{
	k_Game_Props,
	k_Game_Button_Props,
	k_Personal_infomation_big_item,
	k_Personal_infomation_small_item,
	k_Personal_infomation_description_item,
	k_Reward_itemlist_item,
	k_PopWindow_item
}ItemImageType;


class Reward:public cocos2d::CCObject
{
public:
	static Reward* create(RewardType type,int itemType,int quantity);
	bool init(RewardType type,int itemType,int quantity);

	CC_SYNTHESIZE(RewardType,type,Type);
	CC_SYNTHESIZE(int,itemType,ItemType);
	CC_SYNTHESIZE(int,quantity,Quantity);

	static double scaleRatio[20];
	static CCDictionary* getRewardInfoDictionary(RewardType type,int itemType);
	static bool isSatisfiedRequirement(CCDictionary* requirement);
	static bool saveRewardsFromDictionary(CCDictionary* rewards);
	static CCArray* getRewardsArrayFromDictionary(CCDictionary* rewardDict);
	static bool saveRewardsFromRewardsArray(CCArray* rewards);
	void saveRewardToUserData();
	static CCArray* getRewardsArrayFromChapterAndRoundNumber(int chapterNum,int roundNum);
	
	~Reward(void);
};

