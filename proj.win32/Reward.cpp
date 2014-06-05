#include "Reward.h"

double Reward::scaleRatio[20]={
	1,
	1,
	0.3051771,
	0.2316076294,
	1,
	0.4051771,
	0.78474,
	1,1,1,1,1,1,1,1,1,1,1,1,1
};

Reward::~Reward(void)
{
}

Reward* Reward::create( RewardType type,int itemType,int quantity )
{
	Reward* reward = new Reward();
	reward->init(type,itemType,quantity);
	reward->autorelease();
	return reward;
}

bool Reward::init( RewardType type,int itemType,int quantity )
{
	this->setType(type);
	this->setItemType(itemType);
	this->setQuantity(quantity);
	return true;
}

void Reward::saveRewardToUserData()
{
	switch(this->getType())
	{
		case k_Reward_Weapon:
			USER->addWeapon(Weapon(this->itemType));
			break;
		case k_Reward_Base:
			USER->addBase(Base(this->itemType));
			break;
		case k_Reward_Plate:
			USER->addPlate(Plate(this->itemType));
			break;
		case k_Reward_Prop:
			USER->addProp(PropType(this->itemType));
			break;
		case k_Reward_Evolution:
			USER->setRoleType(RoleType(this->itemType));
			break;
		case k_Reward_Exp:
			USER->setExp(USER->getExp()+quantity);
			break;
		case k_Reward_Level:
			USER->setLevel(USER->getLevel()+quantity);
			break;
		case k_Reward_Honor:
			USER->setHonor(USER->getHonor()+quantity);
			break;
		case k_Reward_Money:
			USER->setMoney(USER->getMoney()+quantity);
			break;
		case k_Reward_AGI:
			USER->setBasicAGI(USER->getBasicAGI()+quantity);
			break;
		case k_Reward_STR:
			USER->setBasicSTR(USER->getBasicSTR()+quantity);
			break;
		case k_Reward_DEF:
			USER->setBasicDEF(USER->getBasicDEF()+quantity);
			break;
		default:
			break;
	}
	USER->flush();

}

CCDictionary* Reward::getRewardInfoDictionary( RewardType type,int itemType )
{
	 CCDictionary* dict = StaticData::sharedStaticData()->getStaticDataDictionary();
	 CCDictionary* rewardItemDict =  (CCDictionary*)dict->objectForKey(CCString::createWithFormat(dict->valueForKey("reward_info_format")->getCString(),(int)type,itemType)->getCString());
	 return rewardItemDict;
}

bool Reward::isSatisfiedRequirement( CCDictionary* dict )
{
	bool flag = true;
	CCArray* keyArray = dict->allKeys();
	
	CCObject* tempObj;
	CCARRAY_FOREACH(keyArray,tempObj){
		CCString* pKey = (CCString*)tempObj;
		int iKey = pKey->intValue();
		int iValue  = dict->valueForKey(iKey)->intValue();
		RewardType type = RewardType(iKey);
		switch (type)
		{
		case k_Reward_Weapon:
			flag = USER->hasWeapon((Weapon)iValue);
			break;
		case k_Reward_Base:
			flag = USER->hasBase((Base)iValue);
			break;
		case k_Reward_Plate:
			flag = USER->hasPlate((Plate)iValue);
			break;
		case k_Reward_Prop:
			flag = USER->hasProp((PropType)iValue);
			break;
		case k_Reward_Evolution:
			break;
		case k_Reward_Exp:
			flag = USER->getExp()>=iValue;
			break;
		case k_Reward_Level:
			flag = USER->getLevel()>=iValue;
			break;
		case k_Reward_Honor:
			flag = USER->getHonor()>= iValue;
			break;
		case k_Reward_Money:
			flag = USER->getMoney() >= iValue;
			break;
		case k_Reward_AGI:
			flag = USER->getBasicAGI() >= iValue;
			break;
		case k_Reward_DEF:
			flag = USER->getBasicDEF() >= iValue;
			break;
		case k_Reward_STR:
			flag = USER->getBasicSTR() >=iValue;
			break;
		default:
			break;
		}
		if(flag == false){
			break;
		}
	}
	return flag;
}

bool Reward::saveRewardsFromDictionary( CCDictionary* dict )
{
	CCArray* keyArray = dict->allKeys();
	keyArray->retain();
	CCObject* tempObj;

	CCARRAY_FOREACH(keyArray,tempObj){
		CCString* pKey = (CCString*)tempObj;
		int iKey = pKey->intValue();
		int iValue  = dict->valueForKey(iKey)->intValue();
		RewardType type = RewardType(iKey);
		switch (type)
		{
		case k_Reward_Weapon:
			USER->addWeapon((Weapon)iValue);
			break;
		case k_Reward_Base:
			USER->addBase((Base)iValue);
			break;
		case k_Reward_Plate:
			USER->addPlate((Plate)iValue);
			break;
		case k_Reward_Prop:
			USER->addProp((PropType)iValue);
			break;
		case k_Reward_Evolution:
			//todo
			
			break;
		case k_Reward_Exp:
			USER->setExp(USER->getExp()+iValue);
			break;
		case k_Reward_Level:
			USER->setLevel(USER->getLevel()+iValue);
			break;
		case k_Reward_Honor:
			USER->setHonor(USER->getHonor()+iValue);
			break;
		case k_Reward_Money:
			USER->setMoney(USER->getMoney()+iValue);
			break;
		case k_Reward_AGI:
			USER->setBasicAGI(USER->getBasicAGI()+iValue);
			break;
		case k_Reward_DEF:
			USER->setBasicDEF(USER->getBasicDEF()+iValue);
			break;
		case k_Reward_STR:
			USER->setBasicSTR(USER->getBasicSTR()+iValue);
			break;
		default:
			break;
		}
	}
	USER->flush();
	return true;
}

CCArray* Reward::getRewardsArrayFromDictionary( CCDictionary* dict )
{
	CCArray* keyArray = dict->allKeys();
	keyArray->retain();
	CCObject* tempObj;

	CCArray* rewards = CCArray::create();
	rewards->retain();

	CCARRAY_FOREACH(keyArray,tempObj){
		CCString* pKey = (CCString*)tempObj;
		int iKey = pKey->intValue();
		int iValue  = dict->valueForKey(iKey)->intValue();
		RewardType type = RewardType(iKey);
		rewards->addObject(Reward::create(RewardType(iKey),iValue,1));
	}
	return rewards;
}

bool Reward::saveRewardsFromRewardsArray( CCArray* rewards )
{
	 CCObject* tempObject;
	 CCARRAY_FOREACH(rewards,tempObject){
		 Reward* reward = (Reward*)tempObject;
		 reward->saveRewardToUserData();
	 }
	 return true;
}

CCArray* Reward::getRewardsArrayFromChapterAndRoundNumber( int chapterNum,int roundNum )
{
	CCDictionary* dict = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* gamesceneDict = (CCDictionary*)dict->objectForKey("gamescene");
	CCDictionary* chapterDict = (CCDictionary*)gamesceneDict->objectForKey("chapter_"+Utils::int2str(chapterNum));
	CCDictionary* roundDict = (CCDictionary*)chapterDict->objectForKey("round_"+Utils::int2str(roundNum));
	int rewardsNum = roundDict->valueForKey("number_of_rewards")->intValue();

	CCArray* rewards = CCArray::create();
	rewards->retain();
	for(int i=0;i<rewardsNum;i++){
		CCDictionary* rewardDict = (CCDictionary*)roundDict->objectForKey("reward_"+Utils::int2str(i));
		int rewardType = rewardDict->valueForKey("reward_type")->intValue();
		int itemType = rewardDict->valueForKey("item_type")->intValue();
		int quantity = rewardDict->valueForKey("quantity")->intValue();
		Reward* reward = Reward::create((RewardType)rewardType,itemType,quantity);
		rewards->addObject(reward);
	}
	return rewards;
}

