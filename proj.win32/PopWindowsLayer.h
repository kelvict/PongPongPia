#pragma once
#include <cocos2d.h>
#include "cocos2d.h"
#include"Equipment.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"
#include "GameScene.h"
typedef enum{
	k_PW_Weapon,
	k_PW_Base,
	k_PW_Plate,
	k_PW_Upgrade,
	k_PW_Evolution,
	k_PW_Alert,
	k_PW_SignIn,
	k_PW_SignUp,
	k_PW_Infomation

}PopWindowsType;

USING_NS_CC;

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()
#define INFORMATION_BOX(info,node) PopWindowsLayer::createInfomationBox(info,node)

class PopWindowsLayer :
	public cocos2d::CCLayer
{
public:
	static PopWindowsLayer* createNewEquipmentRewardWindows(PopWindowsType windowsType,int type,cocos2d::SEL_MenuHandler sureButtonHandler);//获得装备
	static PopWindowsLayer* createInfomationBox(CCString ccStr,CCNode* node,cocos2d::SEL_MenuHandler sureButtonHandler=menu_selector(PopWindowsLayer::removeFromParentCallback));
	bool initNewEquipmentRewardWindows(PopWindowsType windowsType,int type);
	CC_SYNTHESIZE(cocos2d::SEL_MenuHandler,confirmButtonHandler,ConfirmButtonHandler);
	CC_SYNTHESIZE(PopWindowsType,windowsType,WindowsType);
	CC_SYNTHESIZE(int,itemType,ItemType);
	CC_SYNTHESIZE(CCMenu*,menu,Menu);

	static PopWindowsLayer* createEvolutionRewardWindows(RoleType type,cocos2d::SEL_MenuHandler sureButtonHandler);//进化
	bool initEvolutionRewardWindows(RoleType type);

	static PopWindowsLayer* createUpgradeRewardWindows(int level,cocos2d::SEL_MenuHandler sureButtonHandler);//升级
	bool initUpgradeRewardWindows(int level);
	bool initInformationBox(CCString ccStr,CCNode* node,cocos2d::SEL_MenuHandler sureButtonHandler=menu_selector(PopWindowsLayer::removeFromParentCallback));
	bool init(cocos2d::SEL_MenuHandler sureButtonHandler);

	static PopWindowsLayer* create(PopWindowsType windowsType,int itemType,cocos2d::SEL_MenuHandler sureButtonHandler=menu_selector(PopWindowsLayer::removeFromParentCallback));
	bool init(PopWindowsType windowsType,int itemType,cocos2d::SEL_MenuHandler sureButtonHandler);

	void removeFromParentCallback(CCObject* pSender);

protected:
	void showWindows();
	void showGetEquiment(Equipment* GetEquipment );
	void showEvolve();

	void drawBackground();
	void drawTitle();
	void drawImage();
	void drawDescriptoin();
	void drawConfirmButton();
	void drawInformation(CCString ccStr);
	void drawItemBackground();

	void showUpGrade(int level);
	void sureButton(CCObject* pSender);
public:
	void createSureAndButtons();
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();

	void displayOn(cocos2d::CCNode* node);
	void displayInformationBox(CCString ccStr,cocos2d::CCNode* parentNodePtr);
};

				