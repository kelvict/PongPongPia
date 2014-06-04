#pragma once
#include <cocos2d.h>
#include "GameScene.h"
#include"Equipment.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"

#include"TipsLayer.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class ChallengeUserLayer :
	public cocos2d::CCLayer
{
public:
	static ChallengeUserLayer* create(Role* role,CCPoint position);
	bool init(Role* role,CCPoint position);

	void CreatTipLayer();

	CC_SYNTHESIZE(CCString,username,Username);
	CC_SYNTHESIZE(int,level,Level);
	CC_SYNTHESIZE(int,honor,Honor);
	CC_SYNTHESIZE(CCPoint,position,ThisPosition);
	CC_SYNTHESIZE(bool,showTip,ShowTip);
	CC_SYNTHESIZE(TipsLayer*,tipLayer,TipLayer);
	CC_SYNTHESIZE(Role*,role,Role);

	void removeFromParentCallback(CCObject* pSender);

protected:
	void drawBackground();//画背景
	void DrawHeadSculpture();//画头像
	void DrawUserName();//写名字
	void DrawLevel();//写等级
	void DrawHonor();//写荣誉值
	void DrawPK();//画PK

	void ClickBackground(CCObject* pSender);//点击背景函数
	void ClickHeadSculpture(CCObject* pSender);//点击头像
	void ClickLevel(CCObject* pSender);//点击等级函数
	void ClickPK(CCObject* pSender);//点击PK函数

	std::string intToString(int n);
public:
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	void displayOn(cocos2d::CCNode* node);
};

