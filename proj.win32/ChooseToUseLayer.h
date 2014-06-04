#pragma once
#include <cocos2d.h>
#include "cocos2d.h"
#include"Prop.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"
#include "GameScene.h"
#include"TipsLayer.h"
#include"ChallengeScene.h"
/*
#include"ViewEquipmentLayer.h"
#include"ViewProperyLayer.h"*/
#include"Reward.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class ChooseToUseLayer :
	public cocos2d::CCLayer
{
public:
	static ChooseToUseLayer* create(RewardType type,int itemType,int poptype = 0);
	//poptype =1 ��ʾ����װ��
	//poptype =2 ��ʾ����
	//protype = 3��ʾ����
	bool init(RewardType type,int itemType,int poptype);

	CC_SYNTHESIZE(CCDictionary*,thisDicti,ThisDicti);
	RewardType thisType;
	int thisItemType;
	int poptype;

protected:
	void DrawWindow();//
	void DrawName();//
	void DrawCloseThis();//
	void DrawWindowShow();//
	void DrawZhiHeng();//
	void DrawSTRIncrement();//��
	void DrawAGIIncrement();//�ٶ�
	void DrawDEFIncrement();//����
	void DrawSUXING();//�����ٶȣ�����
	void DrawAditionEffect();
	void DrawDescription();
	void DrawUseThis();

	void ClickCloseThis(CCObject* pSender);
	void ClickUseThis(CCObject* pSender);


public:
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	void displayOn(cocos2d::CCNode* node);
};

