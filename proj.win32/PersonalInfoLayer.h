
#pragma once
#include <cocos2d.h>
#include "cocos2d.h"
#include"Equipment.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"
#include "GameScene.h"
#include"TipsLayer.h"
#include"ChallengeScene.h"
#include"ViewDataLayer.h";
#include"ViewEquipmentLayer.h"
#include"ViewProperyLayer.h"

typedef enum{
	view_data,
	view_equipment,
	view_property
}CurrentWindowType;

class PersonalInfoLayer :
	public cocos2d::CCLayer
{
public:
	static PersonalInfoLayer* create(CurrentWindowType type = view_data);
	bool init(CurrentWindowType type);

	static PersonalInfoLayer* createOtherInfor(Role* role);
	bool init(Role* role);

	bool isUseData;//true表示是自己查看自己的。
	int roleType;
	Equipment equipment;

	CC_SYNTHESIZE(CurrentWindowType,currentWindow,CurrentWindow);
	//0表示当前显示窗口为查看资料
	//1表示当前显示窗口为查看装备
	//2表示当前显示窗口为查看道具
	CC_SYNTHESIZE(ViewDataLayer*,viewDataWindow,ViewDataWindow);
	CC_SYNTHESIZE(ViewEquipmentLayer*,viewEquipmentWindow,ViewEquipmentWindow);
	CC_SYNTHESIZE(ViewProperyLayer*,viewProperyindow,ViewProperyWindow);

protected:
	void getdata();
	void CreatViewDataWindow();//建立查看资料窗口
	void CreatViewDataWindow(Role* role);
	void CreatViewEquipmentWindow();//建立查看装备窗口
	void CreatViewProperyWindow();//建立查看道具窗口

	void DrawBackground();//画背景
	void DrawBackTo();//画左上角的返回按钮
	void DrawRole();//画人物
	void DrawWindow();//画窗口
	void DrawViewData();//画查看资料
	void DrawViewEquipment();//画查看装备
	void DrawViewProperty();//画查看道具

	void DrawViewWindow();//画查看资料窗口

	void ClickBackTo(CCObject* pSender);//点击返回按钮
	void ClickViewData(CCObject* pSender);//点击查看资料
	void ClickViewEquipment(CCObject* pSender);//点击查看装备
	void ClickViewProperty(CCObject* pSender);//点击查看道具

public:
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	void displayOn(cocos2d::CCNode* node);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void registerWithTouchDispatcher();
	void ReDrawRole();
};

