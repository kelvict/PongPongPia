#include "PopWindowsLayer.h"
#include "StaticData.h"



USING_NS_CC;

PopWindowsLayer* PopWindowsLayer::createNewEquipmentRewardWindows(PopWindowsType windowsType,int type,cocos2d::SEL_MenuHandler sureButtonHandler)
{
	PopWindowsLayer* popWindowsLayer = new PopWindowsLayer();
	popWindowsLayer->initNewEquipmentRewardWindows(windowsType,type);
	popWindowsLayer->autorelease();
	return popWindowsLayer;
}

bool PopWindowsLayer::initNewEquipmentRewardWindows(PopWindowsType windowsType,int type)
{
	if(!windowsType>2)
		return false;
	this->showWindows();
//	this->showGetEquiment(GetEquipment);
	return true;
}

 PopWindowsLayer* PopWindowsLayer::createEvolutionRewardWindows(RoleType type,cocos2d::SEL_MenuHandler sureButtonHandler)
 {
	PopWindowsLayer* popWindowsLayer = new PopWindowsLayer();
//	popWindowsLayer->init();
	popWindowsLayer->autorelease();
	return popWindowsLayer;
 }

 bool PopWindowsLayer::initEvolutionRewardWindows(RoleType type)
{
	this->showWindows();
	this->showEvolve();
	return true;
}

  PopWindowsLayer* PopWindowsLayer::createUpgradeRewardWindows(int level,cocos2d::SEL_MenuHandler sureButtonHandler)
 {
	PopWindowsLayer* popWindowsLayer = new PopWindowsLayer();
	popWindowsLayer->initUpgradeRewardWindows(level);
	popWindowsLayer->autorelease();
	return popWindowsLayer;
 }

 bool PopWindowsLayer::initUpgradeRewardWindows(int level)
{
	if(level <1)
		return false;
	this->showWindows();
	//std::cout<<level<<std::endl;
	this->showUpGrade(level);
	return true;
}

 void PopWindowsLayer::showWindows()
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("pop_window_window"));
	 pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	 this->addChild(pBg);
 }

 void PopWindowsLayer::showGetEquiment(Equipment* GetEquipment )
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pBg1 = CCSprite::create(STATIC_DATA_STRING("pop_window_equipment"));
	 pBg1->setPosition(CCPointMake(winSize.width/2,winSize.height*3/4));
	 this->addChild(pBg1);

	 int equipment = 0;
	 if(GetEquipment->getWeapon())
		 equipment = 1;
	 if(GetEquipment->getBase())
		 equipment = 2;
	 if(GetEquipment->getPlate())
		 equipment = 3;
	 std::string name1 = "pop_window_equipment_property_";
	 char e = (char) (equipment+48);
	 name1.append(&e);
	 CCSprite* pBg2 = CCSprite::create(STATIC_DATA_STRING(name1));
	 pBg2->setPosition(CCPointMake(winSize.width*2/5,winSize.height/2));
	 this->addChild(pBg2);

	 std::string name2 = "pop_window_equipment_graph_";
	 name2.append(&e);
	 CCSprite* pBg3 = CCSprite::create(STATIC_DATA_STRING(name2));
	 pBg3->setPosition(CCPointMake(winSize.width*2/3,winSize.height/2));
	 this->addChild(pBg3);

	 CCSprite* pBg4 = CCSprite::create(STATIC_DATA_STRING("pop_window_banner"));
	 pBg4->setPosition(CCPointMake(winSize.width*2/3,winSize.height/4));
	 this->addChild(pBg4);
 }

 void PopWindowsLayer::showEvolve()
 {
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pBg1 = CCSprite::create(STATIC_DATA_STRING("pop_window_evolve"));
	 pBg1->setPosition(CCPointMake(winSize.width/2,winSize.height*3/4));
	 this->addChild(pBg1);

	 CCSprite* pBg2 = CCSprite::create(STATIC_DATA_STRING("pop_window_evolve_property"));
	 pBg2->setPosition(CCPointMake(winSize.width*2/5,winSize.height/2));
	 this->addChild(pBg2);

	 CCSprite* pBg3 = CCSprite::create(STATIC_DATA_STRING("pop_window_evolve_graph"));
	 pBg3->setPosition(CCPointMake(winSize.width*2/3,winSize.height/2));
	 this->addChild(pBg3);
 }

void PopWindowsLayer::showUpGrade(int level)
{
	 CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	 CCSprite* pBg1 = CCSprite::create(STATIC_DATA_STRING("pop_window_upgrade"));
	 pBg1->setPosition(CCPointMake(winSize.width/2,winSize.height*3/4));
	 this->addChild(pBg1);

	 std::string name = "pop_window_upgrade_property_";
	 char* e = new char[4];
	 int size = 0;
	 while(level >0)
	 {
		 e[size] = 48 + level%10;
		 level = level/10;
		 size++;
	 }
	 e[size] = 0;
	 size --;
	 while(size>=0)
	 {
		 name.append(e+size);
		 e[size]=0;
		 size--;
	 }
	 //std::cout<<e<<std::endl;
	// std::cout<<name<<std::endl;
	 CCSprite* pBg2 = CCSprite::create(STATIC_DATA_STRING(name));
	 pBg2->setPosition(CCPointMake(winSize.width*2/5,winSize.height/2));
	 this->addChild(pBg2);

	 CCSprite* pBg3 = CCSprite::create(STATIC_DATA_STRING("pop_window_upgrade_graph"));
	 pBg3->setPosition(CCPointMake(winSize.width*2/3,winSize.height/2));
	 this->addChild(pBg3);
}


void PopWindowsLayer::sureButton(CCObject* pSender)
{
	exit(0);
}
void PopWindowsLayer::createSureAndButtons()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("pop_window_button_normal"),
			STATIC_DATA_STRING("pop_window_button_click"),
			this,
			menu_selector(PopWindowsLayer::removeFromParentCallback)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	menu->setPosition(CCPointMake(winSize.width/2,winSize.height/7));	
	this->addChild(menu);
}


bool PopWindowsLayer::init( cocos2d::SEL_MenuHandler sureButtonHandler )
{
//	this->setSureButtonHandler(sureButtonHandler);
	this->showWindows();
	this->createSureAndButtons();
	return true;
}

bool PopWindowsLayer::init( PopWindowsType windowsType,int itemType,cocos2d::SEL_MenuHandler confirmButtonHandler )
{
	this->setWindowsType(windowsType);
	this->setItemType(itemType);
	this->setConfirmButtonHandler(confirmButtonHandler);
	this->menu=CCMenu::create();
	return true;
}

PopWindowsLayer* PopWindowsLayer::create( PopWindowsType windowsType,int itemType,cocos2d::SEL_MenuHandler sureButtonHandler )
{
	PopWindowsLayer* popWindowsLayer = new PopWindowsLayer();
	popWindowsLayer->init( windowsType,itemType,sureButtonHandler );
	popWindowsLayer->autorelease();
	return popWindowsLayer;
}

void PopWindowsLayer::drawBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("pop_window_window"));
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);
}

void PopWindowsLayer::drawTitle()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(CCString::createWithFormat(STATIC_DATA_STRING("pop_window_title_image_format"),(int)this->windowsType)->getCString());
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height*3/4));
	this->addChild(pBg);
}

void PopWindowsLayer::drawImage()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(CCString::createWithFormat(STATIC_DATA_STRING("pop_window_image_image_format"),(int)this->windowsType,(int)this->itemType)->getCString());
	 pBg->setPosition(CCPointMake(winSize.width*2/3,winSize.height/2));
	this->addChild(pBg);
}

void PopWindowsLayer::drawDescriptoin()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(CCString::createWithFormat(STATIC_DATA_STRING("pop_window_description_image_format"),(int)this->windowsType,(int)this->itemType)->getCString());
	pBg->setPosition(CCPointMake(winSize.width*2/5,winSize.height/2));
	this->addChild(pBg);	
}

void PopWindowsLayer::drawConfirmButton()
{
	CCMenuItemImage* item = CCMenuItemImage::create(
		STATIC_DATA_STRING("pop_window_button_normal"),
		STATIC_DATA_STRING("pop_window_button_click"),
		this,
		this->confirmButtonHandler
		);
	
	item->setPosition(CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height/7));
	this->menu->addChild(item);
}

void PopWindowsLayer::displayOn(cocos2d::CCNode* node)
{
	this->drawBackground();
	this->drawTitle();
	this->drawDescriptoin();
	this->drawImage();
	this->drawItemBackground();
	this->drawConfirmButton();
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	this->operateAllSchedulerAndActions(node,k_Operate_Pause);
	this->setPosition(CCPointZero);
	this->_setZOrder(99999999);
	node->addChild(this);
	//node->reorderChild(this,99999999);
}

void PopWindowsLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
	//this->removeFromParentAndCleanup();
}

void PopWindowsLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
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
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void PopWindowsLayer::removeFromParentCallback( CCObject* pSender )
{
	this->removeFromParentAndCleanup();
}

bool PopWindowsLayer::initInformationBox(CCString ccStr,CCNode* node,cocos2d::SEL_MenuHandler sureButtonHandler)
{
	this->setConfirmButtonHandler(sureButtonHandler);
	this->menu=CCMenu::create();
	this->displayInformationBox(ccStr,node);
	return true;
}

PopWindowsLayer* PopWindowsLayer::createInfomationBox( CCString ccStr,CCNode* node,cocos2d::SEL_MenuHandler sureButtonHandler)
{
	PopWindowsLayer* popWindowsLayer = new PopWindowsLayer();
	popWindowsLayer->initInformationBox(ccStr,node);
	popWindowsLayer->autorelease();
	return popWindowsLayer;
}

void PopWindowsLayer::drawInformation( CCString ccStr )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();	
	CCLabelTTF* pLabel = CCLabelTTF::create(ccStr.getCString(),"свт╡",48,CCSizeMake(550, 200), kCCTextAlignmentLeft);
	pLabel->setPosition(ccp(size.width/2,size.height/2));
	pLabel->setColor(ccc3(0,0,0));

	this->addChild(pLabel);
}

void PopWindowsLayer::displayInformationBox( CCString ccStr,cocos2d::CCNode* parentNodePtr )
{
	this->drawBackground();
	//this->drawItemBackground();
	this->drawInformation(ccStr);
	this->drawConfirmButton();
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	this->operateAllSchedulerAndActions(parentNodePtr,k_Operate_Pause);
	this->setPosition(CCPointZero);
	this->_setZOrder(99999999);
	parentNodePtr->addChild(this);	
}

void PopWindowsLayer::drawItemBackground()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING("pop_window_item_background"));
	pBg->setPosition(CCPointMake(float(winSize.width)/1.47-16,float(winSize.height)/2.2+16));	 
	this->addChild(pBg);
}

