#include "BackHomeRorContinueLayer.h"

BackHomeRorContinueLayer* BackHomeRorContinueLayer::create()
{
	BackHomeRorContinueLayer* backHomeRorContinueLayer = new BackHomeRorContinueLayer();
	backHomeRorContinueLayer->init();
	backHomeRorContinueLayer->autorelease();
	return backHomeRorContinueLayer;
}

bool BackHomeRorContinueLayer::init()
{
	if(!CCLayer::init())
	 {
		 return false;
	 }
	this->setTouchEnabled(true);
	return true;
}

void BackHomeRorContinueLayer::DrawEndBackground()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"StoryEndLayer_background"));
	 CCPoint pos = CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height/2);
	 pBg->setPosition(pos);
	 this->addChild(pBg);
}

void BackHomeRorContinueLayer::DrawBackHome()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("StoryEndLayer_backHome_normal"),
			STATIC_DATA_STRING("StoryEndLayer_backHome_click"),
			this,
			menu_selector(BackHomeRorContinueLayer::ClickBackHome)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*409/1100,WIN_SIZE.height*123/622);
	menu->setPosition(pos);
	this->addChild(menu);
}

void BackHomeRorContinueLayer::DrawContinue()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("StoryEndLayer_continue_normal"),
			STATIC_DATA_STRING("StoryEndLayer_continue_click"),
			this,
			menu_selector(BackHomeRorContinueLayer::ClickBackHome)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*692/1100,WIN_SIZE.height*123/622);
	menu->setPosition(pos);
	this->addChild(menu);
}

void BackHomeRorContinueLayer::ClickBackHome(CCObject* pSender)
{
	//回主页，话说，主页在哪儿呢
	this->removeFromParentAndCleanup();
}

void BackHomeRorContinueLayer::ClickContinue(CCObject* pSender)
{
	//继续，这个继续咋个走哇
	this->removeFromParentAndCleanup();
}

void BackHomeRorContinueLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void BackHomeRorContinueLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
	
}

bool BackHomeRorContinueLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	return true;
}

void BackHomeRorContinueLayer::registerWithTouchDispatcher(){
	// 这里的触摸优先级设置为 -128 这保证了，屏蔽下方的触摸
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

void BackHomeRorContinueLayer::displayOn(cocos2d::CCNode* node)
{
	this->DrawEndBackground();
	this->DrawBackHome();
	this->DrawContinue();

	node->addChild(this,20);
}