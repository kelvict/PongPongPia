//
//  PanelLayer.cpp
//  PongPongPia
//
//  Created by HuFan on 13-9-16.
//
//

#include "PanelLayer.h"
#include "GameScene.h"
#include "StaticData.h"
#include "PersonalAudioEngine.h"

USING_NS_CC;

#define LEFT 0
#define RIGHT 1

bool PanelLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		
		// Settting and pause (Right Top)
		CCMenuItemImage* setting = CCMenuItemImage::create(
			STATIC_DATA_STRING("setting_normal"),
			STATIC_DATA_STRING("setting_selected"),
			this,
			menu_selector(PanelLayer::setting));
		CC_BREAK_IF( !setting );
		
		CCMenuItemImage* pause = CCMenuItemImage::create(
			STATIC_DATA_STRING("pause_normal"),
			STATIC_DATA_STRING("pause_selected"),
			this,
			menu_selector(PanelLayer::pause));
		CC_BREAK_IF( !pause );

		CCSize settingSize = setting->getContentSize();
		CCSize pauseSize = pause->getContentSize();

		CCMenu* menu = CCMenu::create(setting, pause, NULL);
		CC_BREAK_IF( !menu );
		this->addChild(menu, 1, MENUTAG);

		menu->setPosition(CCPointMake(winSize.width-pauseSize.width * 3 / 2, winSize.height-pauseSize.height * 3 /4));
		menu->alignItemsHorizontallyWithPadding(pauseSize.width / 3);

		// energy bar (Left Top)
		energyBar = ProgressBar::create();
		CC_BREAK_IF( !energyBar );
		CCSize barSize = energyBar->getContentSize();
		energyBar->setPosition(ccp(barSize.width*0.52, winSize.height-barSize.height*0.58));
		this->addChild(energyBar);

		// energy button(Left Top)
		eneygyButtonNormal = CCMenuItemImage::create(
			STATIC_DATA_STRING("ultimateButton_normal"),
			STATIC_DATA_STRING("ultimateButton_normal"),
			this,
			menu_selector(PanelLayer::useUltimate));
		eneygyButtonFull = CCMenuItemImage::create(
			STATIC_DATA_STRING("ultimateButton_selected"),
			STATIC_DATA_STRING("ultimateButton_selected"),
			this,
			menu_selector(PanelLayer::useUltimate));
		menuUltimate = CCMenu::create(eneygyButtonNormal, eneygyButtonFull, NULL);
		eneygyButtonFull->setVisible(false);
		this->addChild(menuUltimate);
		CCSize ultiSize = eneygyButtonNormal->getContentSize();
		menuUltimate->setPosition(ccp(ultiSize.width*0.6, winSize.height-ultiSize.height*0.58));


		// Pro
		propLeft = CCMenuItemImage::create(
			STATIC_DATA_STRING("prop_nothing"),
			STATIC_DATA_STRING("prop_nothing"),
			this,
			menu_selector(PanelLayer::useLeftPro));
		propLeft->setTag(LEFT);
		Prop* prop = Prop::create(No_Prop);
		this->setLeftProp(prop);

		propRight = CCMenuItemImage::create(
			STATIC_DATA_STRING("prop_nothing"),
			STATIC_DATA_STRING("prop_nothing"),
			this,
			menu_selector(PanelLayer::useRightPro));
		propRight->setTag(RIGHT);

		Prop* prop2 = Prop::create(No_Prop);
		this->setRightProp(prop2);


		menuProp = CCMenu::create(propLeft, propRight, NULL);
		this->addChild(menuProp);
		CCSize proSize = propLeft->getContentSize();
		menuProp->setPosition(CCPointMake(proSize.width * 3 / 2, proSize.height * 0.618));
		menuProp->alignItemsHorizontallyWithPadding(proSize.width / 3);
		leftPlaced = rightPlaced = false;
		bRet = true;
	} while (0);

	return bRet;
}

void PanelLayer::pause(cocos2d::CCObject* pSender)
{
	PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("click_button"));
	this->getChildByTag(MENUTAG)->setVisible(false);
	GameScene* gameScene = (GameScene*)this->getParent();
	gameScene->pause();
}

void PanelLayer::setting(cocos2d::CCObject* pSender)
{
	// TO-DO
}

void PanelLayer::placeProp(Prop* prop)
{	
	CCString* spriteName = CCString::createWithFormat(STATIC_DATA_STRING("prop_format"),prop->getPropType());

	if (!leftPlaced) {
		this->setLeftProp(prop);
		removeAndPlace(LEFT, spriteName->getCString());
		leftPlaced = true;
	}
	else if (!rightPlaced) {
		this->setRightProp(prop);
		removeAndPlace(RIGHT, spriteName->getCString());
		rightPlaced = true;
	}
	return;
}

void PanelLayer::useLeftPro(cocos2d::CCObject* pSender)
{

	this->getLeftProp()->playEffect();
	removeAndPlace(LEFT, STATIC_DATA_STRING("prop_nothing"));
	Prop* prop = Prop::create(No_Prop);
	this->setLeftProp(prop);
	leftPlaced = false;
	// TO-DO
	// Example: add the ap and so on

}
void PanelLayer::useRightPro(cocos2d::CCObject* pSender)
{
	this->getRightProp()->playEffect();
	removeAndPlace(RIGHT, STATIC_DATA_STRING("prop_nothing"));
	Prop* prop = Prop::create(No_Prop);
	this->setRightProp(prop);
	rightPlaced = false; 
	// TO-DO
	// Example:
}
void PanelLayer::useUltimate(cocos2d::CCObject* pSender)
{
	// To-Do use the ultimate
	// get the energy if not full return
	//else
	GameScene* gamescene =  (GameScene*)this->getParent();
	if (!gamescene->getisFullOfEnergy())
		return;
	//
	// 
		gamescene->getRoleLayer()->getPlayer()->startUltimateSpin_FiniteTimeAction();
	//
	eneygyButtonFull->setVisible(false);
	eneygyButtonNormal->setVisible(true);
	gamescene->setisFullOfEnergy(false);
}


void PanelLayer::removeAndPlace(int tag, const char* propName)
{
	menuProp->removeChildByTag(tag, true);
	if (tag == LEFT) {
		propLeft = CCMenuItemImage::create(
			propName,
			 STATIC_DATA_STRING("prop_nothing"),
			this,
			menu_selector(PanelLayer::useLeftPro));
		propLeft->setTag(tag);
		menuProp->addChild(propLeft);
		leftPlaced = false;
	}
	else {
		propRight = CCMenuItemImage::create(
			propName,
			STATIC_DATA_STRING("prop_nothing"),
			this,
			menu_selector(PanelLayer::useRightPro));
		propRight->setTag(tag);
		menuProp->addChild(propRight);
		rightPlaced = false;
	}

	CCSize proSize = propLeft->getContentSize();
	menuProp->setPosition(CCPointMake(proSize.width * 3 / 2, proSize.height * 0.618));
	menuProp->alignItemsHorizontallyWithPadding(proSize.width / 3);
}

void PanelLayer::increaceEnetgy()
{
	this->energyBar->increaceEnetgy();
}

void PanelLayer::fullEnergy()
{
	eneygyButtonFull->setVisible(true);
	eneygyButtonNormal->setVisible(false);
}