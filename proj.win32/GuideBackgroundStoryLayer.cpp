#include "GuideBackgroundStoryLayer.h"

GuideBackgroundStoryLayer* GuideBackgroundStoryLayer::create()
{
	GuideBackgroundStoryLayer* guideBackgroundStoryLayer = new GuideBackgroundStoryLayer();
	guideBackgroundStoryLayer->init();
	guideBackgroundStoryLayer->autorelease();
	return guideBackgroundStoryLayer;
}

bool GuideBackgroundStoryLayer::init()
{
	if(!CCLayer::init())
	 {
		 return false;
	 }
	this->order = 1;
	this->setTouchEnabled(true);
	return true;
}

void GuideBackgroundStoryLayer::DrawPage()
{
	if(this->order > 4 || this->order <1)
		return ;
	CCString* a = CCString::createWithFormat(STATIC_DATA_STRING("GuideBackgroundStoryLayer_page"),this->order);
	CCSprite* pBg = CCSprite::create(a->getCString());
	pBg->setPosition(CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height/2));
	pBg->setTag(110);
	this->addChild(pBg);
}

void GuideBackgroundStoryLayer::DrawThenOrKnow()
{
	if(this->order <1 &&this->order > 4)
		return ;
	CCMenuItemImage* pBackItem = NULL;
	if(this->order>0&&this->order<4)
	{
	    pBackItem = CCMenuItemImage::create(
			        STATIC_DATA_STRING("GuideBackgroundStoryLayer_then_normal"),
			        STATIC_DATA_STRING("GuideBackgroundStoryLayer_then_click"),
			        this,
			        menu_selector(GuideBackgroundStoryLayer::ClickThenOrKnow)
			        );
	}
	if(this->order == 4)
	{
	    pBackItem = CCMenuItemImage::create(
			        STATIC_DATA_STRING("GuideBackgroundStoryLayer_know_normal"),
			        STATIC_DATA_STRING("GuideBackgroundStoryLayer_know_click"),
			        this,
			        menu_selector(GuideBackgroundStoryLayer::ClickThenOrKnow)
			        );
	}
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height*80/622);
	menu->setPosition(pos);
	menu->setTag(111);
	this->addChild(menu);
}

void GuideBackgroundStoryLayer::DrawJump()
{
	if(this->order <1 &&this->order > 3)
		return ;
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("GuideBackgroundStoryLayer_jump_normal"),
		STATIC_DATA_STRING("GuideBackgroundStoryLayer_jump_click"),
		this,
		menu_selector(GuideBackgroundStoryLayer::ClickJump)
		);

	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*996/1100,WIN_SIZE.height*65/622);
	menu->setPosition(pos);
	menu->setTag(112);
	this->addChild(menu);
}

void GuideBackgroundStoryLayer::ClickThenOrKnow(CCObject* pSender)
{	
	this->order++;

	if(this->order <1 || this->order > 4)
	{
		removeFromParentAndCleanup();
		return ;
	}

	this->removeChildByTag(110,true);
	this->DrawPage();

	if(this->order == 4)
	{
		this->removeChildByTag(111,true);
		this->removeChildByTag(112,true);
		this->DrawThenOrKnow();
	}
	
}
void GuideBackgroundStoryLayer::ClickJump(CCObject* pSender)
{
	removeFromParentAndCleanup();
}

void GuideBackgroundStoryLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void GuideBackgroundStoryLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
	
}

void GuideBackgroundStoryLayer::displayOn(cocos2d::CCNode* node)
{
	this->DrawPage();
	this->DrawThenOrKnow();
	this->DrawJump();

	node->addChild(this,20);
}

void GuideBackgroundStoryLayer::registerWithTouchDispatcher(){
	// 这里的触摸优先级设置为 -128 这保证了，屏蔽下方的触摸
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool GuideBackgroundStoryLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	//
	CCLog("LoseLayer touch");
	return true;
}
