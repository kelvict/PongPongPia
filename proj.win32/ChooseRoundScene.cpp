#include "ChooseRoundScene.h"
#include "StaticData.h"
#include "StartScene.h"
#include"GameScene.h"
#include "cocos2d.h"
#include "UserData.h"
#include "ChooseChapterScene.h"
USING_NS_CC;

ChooseRoundScene* ChooseRoundScene::create( int chapterNumber )
{
	ChooseRoundScene* scene = new ChooseRoundScene();
	scene->init(chapterNumber);
	scene->autorelease();
	return scene;
}

bool ChooseRoundScene::init( int chapterNumber )
{
	this->setCurrentChapterNumber(chapterNumber);
	this->setTotalRoundNumber(this->getCurrentChapterDict()->valueForKey("total_round_number")->intValue());
	this->setOpenRoundNumber(UserData::sharedUserData()->openRounds[chapterNumber]);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* backgroundSprite = CCSprite::create(this->getCurrentChapterDict()->valueForKey("choose_round_background")->getCString());
	backgroundSprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(backgroundSprite);
	
	CCMenuItemImage* returnHomeItem = CCMenuItemImage::create(STATIC_DATA_STRING("choose_round_home_button_normal"),STATIC_DATA_STRING("choose_round_home_button_selected"),this,menu_selector(ChooseRoundScene::returnMainMenuCallback));
	returnHomeItem->setPosition(ccp(winSize.width-returnHomeItem->getContentSize().width/2,winSize.height-returnHomeItem->getContentSize().height/2));
	
	CCMenuItemImage* backItem = CCMenuItemImage::create(STATIC_DATA_STRING("choose_round_back_button_normal"),STATIC_DATA_STRING("choose_round_back_button_selected"),this,menu_selector(ChooseRoundScene::getBackCallback));
	backItem->setPosition(ccp(returnHomeItem->getContentSize().width/2,winSize.height-returnHomeItem->getContentSize().height/2));

	CCMenu* menu = CCMenu::create(returnHomeItem,backItem,NULL);
	for(int i = 1; i <= this->getTotalRoundNumber();i++){
		CCMenuItemImage* numberItem;
		if(i<=this->getOpenRoundNumber()){
			numberItem = CCMenuItemImage::create(CCString::createWithFormat(STATIC_DATA_STRING("choose_round_num_normal_format"),i)->getCString(),CCString::createWithFormat(STATIC_DATA_STRING("choose_round_num_selected_format"),i)->getCString(),this,menu_selector(ChooseRoundScene::chooseRoundCallback));

		}
		else{
			numberItem = CCMenuItemImage::create(CCString::createWithFormat(STATIC_DATA_STRING("choose_round_num_lock_format"),i)->getCString(),CCString::createWithFormat(STATIC_DATA_STRING("choose_round_num_lock_format"),i)->getCString(),this,menu_selector(ChooseRoundScene::chooseLockedRound));
		}

		numberItem->setTag(this->getNumberItemTag(i));		
		numberItem->setPosition(winSize.width/2+((i-1)%3-1)*1*numberItem->getContentSize().width,winSize.height/2+((i-1)/3-1)*1*numberItem->getContentSize().height);
		//numberItem->setPosition(winSize.width/2,winSize.height/2);
		menu->addChild(numberItem);
	}
	menu->setPosition(CCPointZero);
	this->addChild(menu);
	return true;
}

int ChooseRoundScene::getNumberItemTag(int itemNumber){
	return itemNumber+888;
}

int ChooseRoundScene::getChooseNumber(int chooseNumber){
	return chooseNumber-888;
}

void ChooseRoundScene::returnMainMenuCallback( CCObject *pSender )
{
	CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
	CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
}

void ChooseRoundScene::getBackCallback( CCObject *pSender )
{
	ChooseChapterScene* chooseChapterScene = ChooseChapterScene::create();
	CCTransitionShrinkGrow* transitionToChooseChapterScene = CCTransitionShrinkGrow::create(0.30f,chooseChapterScene);
	CCDirector::sharedDirector()->replaceScene(transitionToChooseChapterScene);
}

void ChooseRoundScene::chooseRoundCallback( CCObject *pSender )
{
	CCMenuItemImage* menuItem=(CCMenuItemImage*) pSender;
	int roundNum = this->getChooseNumber(menuItem->getTag());
	//CCDictionary* roundDict = dynamic_cast<CCDictionary*>(this->getCurrentChapterDict()->objectForKey(CCString::createWithFormat("round_%d",roundNum-1)->getCString()));
	//CCDictionary* playerDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey("player"));
	//UserData* user = USER;
	//Role* player = Role::create(USER->getRoleType(),Player,&(USER->getEquipment()),left);
	//int computersNumber = roundDict->valueForKey("number_of_computers")->intValue();
	//CCArray* otherRoles = CCArray::createWithCapacity(computersNumber);
	//otherRoles->retain();
	//for(int i=0;i<computersNumber;i++){
	//	playerDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey(CCString::createWithFormat("computer_%d",i)->getCString()));
	//	Role* computer = Role::create((RoleType)playerDict->valueForKey("role")->intValue(),(Status)playerDict->valueForKey("status")->intValue(),Equipment::create((Weapon)playerDict->valueForKey("weapon")->intValue(),(Base)playerDict->valueForKey("base")->intValue(),(Plate)playerDict->valueForKey("plate")->intValue()),left);	
	//	otherRoles->addObject(computer);
	//}

	GameScene* gamescene = GameScene::createWithGameNumber(this->getCurrentChapterNumber(),roundNum-1);
	CCTransitionShrinkGrow* transitionToGameScene= CCTransitionShrinkGrow::create(0.30f,gamescene);
	CCDirector::sharedDirector()->replaceScene(transitionToGameScene);	
	
}

void ChooseRoundScene::chooseLockedRound(CCObject* pSender){
	//todo
}

CCDictionary* ChooseRoundScene::getGamesceneDict()
{
	CCDictionary* staticData = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* gamesceneDict =dynamic_cast<CCDictionary*>( staticData->objectForKey("gamescene"));
	return gamesceneDict;
}

CCDictionary* ChooseRoundScene::getCurrentChapterDict()
{
	CCDictionary* chapterDict = dynamic_cast<CCDictionary*>(this->getGamesceneDict()->objectForKey(CCString::createWithFormat("chapter_%d",this->currentChapterNumber)->getCString()));
	return chapterDict;
}

