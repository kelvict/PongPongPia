#include "StaticData.h";
#include"ChooseToUseLayer.h"
#include"ViewEquipmentLayer.h"
#include"ViewProperyLayer.h"

ChooseToUseLayer* ChooseToUseLayer::create(RewardType type,int itemType,int poptype)
{
	ChooseToUseLayer* chooseToUseLayer = new ChooseToUseLayer();
	chooseToUseLayer->init(type,itemType,poptype);
	chooseToUseLayer->autorelease();
	return chooseToUseLayer;
}

bool ChooseToUseLayer::init(RewardType type,int itemType,int poptype)
{
	if(!CCLayer::init())
	{
		return false;
	}
	thisType = type;
	thisItemType = itemType;
	this->poptype = poptype;
	thisDicti= Reward::getRewardInfoDictionary(type,itemType);
	thisDicti->retain();
	return true;
}

void ChooseToUseLayer::DrawWindow()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"choose_to_use_window"));
	CCPoint pos = CCPointMake(WIN_SIZE.width*189/1100,WIN_SIZE.height*306/622);
	pBg->setPosition(pos);
	this->addChild(pBg);	
}

void ChooseToUseLayer::DrawName()
{
	std::string show;
	if(poptype == 1)
	{
		show.append(STATIC_DATA_STRING("choose_to_get"));
	}

	show.append(
		((CCString*)(thisDicti->objectForKey("name")))->m_sString
		);
	if(poptype == 2)
	{
		show.append(STATIC_DATA_STRING("choose_to_use_level"),
			UserData::sharedUserData()->getLevel());
	}
	const char* s = show.data();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(s, "Thonburi", 34);
	pBg1->setColor(ccc3(0,0,255));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*525/622));
	this->addChild(pBg1);
}

void ChooseToUseLayer::DrawCloseThis()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("choose_to_use_close_this_normal"),
		STATIC_DATA_STRING("choose_to_use_close_this_click"),
		this,
		menu_selector(ChooseToUseLayer::ClickCloseThis)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	menu->setPosition(
		CCPointMake(WIN_SIZE.width*328/1100,WIN_SIZE.height*533/622));
	this->addChild(menu);
}

void ChooseToUseLayer::DrawWindowShow()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"choose_to_use_window_show"));
	CCPoint pos = CCPointMake(WIN_SIZE.width*189/1100,WIN_SIZE.height*390/622);
	pBg->setPosition(pos);
	this->addChild(pBg);
}

void ChooseToUseLayer::DrawZhiHeng()
{
	std::string a;
	if(poptype == 0||poptype == 1)
	{
		a = "choose_to_use_"; 
		if(thisType == k_Reward_Weapon)
			a.append("weapon",6);
		if(thisType == k_Reward_Base)
			a.append("base",4);
		if(thisType == k_Reward_Plate)
			a.append("plate",5);
		if(thisType == k_Reward_Prop)
			a.append("propery",7);
	}
	else
	{
		if(poptype == 2)
			a = "ma_shang_sheng_ji";
		if(poptype == 3)
			a = "ma_shang_jing_hua";
	}

	const char* s = (CCString::createWithFormat(
		STATIC_DATA_STRING(a),thisItemType))->getCString();

	CCSprite* pBg = CCSprite::create(s);
	CCPoint pos = CCPointMake(WIN_SIZE.width*189/1100,WIN_SIZE.height*390/622);
	pBg->setPosition(pos);
	if(poptype == 2||poptype == 3)
		pBg->setScale(0.69);
	this->addChild(pBg);
}
void ChooseToUseLayer::DrawSTRIncrement()
{
	std::string s = ((CCString*)thisDicti->objectForKey("STR_increment"))->m_sString;
	if(s == "0")
		return ;
	std::string a = STATIC_DATA_STRING("choose_to_use_liliang");
	a.append(s);

	const char* result = a.data();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(result, "Thonburi", 28);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*279/622));
	this->addChild(pBg1);
}

void ChooseToUseLayer::DrawAGIIncrement()
{
	std::string s = ((CCString*)thisDicti->objectForKey("AGI_increment"))->m_sString;
	if(s == "0")
		return ;
	std::string a = STATIC_DATA_STRING("choose_to_use_sudu");
	a.append(s);

	const char* result = a.data();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(result, "Thonburi", 28);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*279/622));
	this->addChild(pBg1);
}


void ChooseToUseLayer::DrawDEFIncrement()
{
	std::string s = ((CCString*)thisDicti->objectForKey("DEF_increment"))->m_sString;
	if(s == "0")
		return ;
	std::string a = STATIC_DATA_STRING("choose_to_use_fangyu");
	a.append(s);

	const char* result = a.data();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(result, "Thonburi", 28);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*279/622));
	this->addChild(pBg1);
}

void ChooseToUseLayer::DrawSUXING()
{
	std::string liliangzhi = ((CCString*)thisDicti->objectForKey("STR_increment"))->m_sString;
	std::string liliang;
	if(liliangzhi != "0")
	{
		liliang= STATIC_DATA_STRING("choose_to_use_liliang");
		liliang.append(liliangzhi);
		liliang.append("  ",2);
	}

	std::string suduzhi = ((CCString*)thisDicti->objectForKey("AGI_increment"))->m_sString;
	std::string sudu;
	if(suduzhi != "0")
	{
		sudu = STATIC_DATA_STRING("choose_to_use_sudu");
		sudu.append(suduzhi);
		sudu.append("  ",2);
	}

	std::string fangyuzhi = ((CCString*)thisDicti->objectForKey("DEF_increment"))->m_sString;
	std::string fangyu;
	if(fangyuzhi != "0")
	{
		fangyu= STATIC_DATA_STRING("choose_to_use_fangyu");
		fangyu.append(fangyuzhi);
	}

	std::string s;
	s.append(liliang);
	s.append(sudu);
	s.append(fangyu);

	const char* result = s.data();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(result, "Thonburi", 28);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*279/622));
	this->addChild(pBg1);
}


void ChooseToUseLayer::DrawAditionEffect()
{
	const char* s = ((CCString*)thisDicti->objectForKey("addition_effect"))->getCString();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(s, "Thonburi", 24);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*240/622));
	this->addChild(pBg1);
}

void ChooseToUseLayer::DrawDescription()
{
	const char* s = ((CCString*)thisDicti->objectForKey("description"))->getCString();
	CCLabelTTF* pBg1 =
		CCLabelTTF::labelWithString(s, "Thonburi", 20);
	pBg1->setColor(ccc3(0,0,0));
	pBg1->setPosition(CCPointMake(WIN_SIZE.width*190/1100,WIN_SIZE.height*204/622));
	this->addChild(pBg1);
}


void ChooseToUseLayer::DrawUseThis()
{
	std::string normalButton = "";
	std::string clickButton = "";
	if(this->poptype==2||this->poptype==3){
		normalButton = "choose_to_use_confirm_normal";
		clickButton = "choose_to_use_confirm_normal";
	}
	else{
		normalButton = "choose_to_use_use_it_normal";
		clickButton = "choose_to_use_use_it_click";
	}


	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING(normalButton.c_str()),
		STATIC_DATA_STRING(clickButton.c_str()),
		this,
		menu_selector(ChooseToUseLayer::ClickUseThis)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	menu->setPosition(
		CCPointMake(WIN_SIZE.width*187/1100,WIN_SIZE.height*104/622));
	this->addChild(menu);
}

void ChooseToUseLayer::ClickCloseThis(CCObject* pSender)
{
	if(poptype!=0)
	{
		removeFromParentAndCleanup();
		return ;
	}
	int a = (int)thisType;
	if(a<3)
	{
		ViewEquipmentLayer* viewEq = (ViewEquipmentLayer*)this->getParent();
		viewEq->ClickExit();
	}
	if(a == 3)
	{
		ViewProperyLayer* viewPr = (ViewProperyLayer*)this->getParent();
		viewPr->ClickExit();
	}
	removeFromParentAndCleanup();
}

void ChooseToUseLayer::ClickUseThis(CCObject* pSender)
{
	if(poptype!=0)
	{
		removeFromParentAndCleanup();
		return ;
	}
	int a = (int)thisType;
	if(a<3)
	{
		ViewEquipmentLayer* viewEq = (ViewEquipmentLayer*)this->getParent();
		viewEq->ClickSure();
	}
	if(a == 3)
	{
		ViewProperyLayer* viewPr = (ViewProperyLayer*)this->getParent();
		viewPr->ClickSure();
	}
	removeFromParentAndCleanup();
}

void ChooseToUseLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
	OperateFlag flag)
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

void ChooseToUseLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);

}

void ChooseToUseLayer::displayOn(cocos2d::CCNode* node)
{
	DrawWindow();
	DrawName();
	DrawCloseThis();
	DrawWindowShow();
	DrawZhiHeng();
	//	DrawSTRIncrement();
	//	DrawAGIIncrement();
	//	DrawDEFIncrement();
	this->DrawSUXING();
	DrawAditionEffect();
	DrawDescription();
	DrawUseThis();

	node->addChild(this,30);
}
