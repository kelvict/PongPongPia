#include "StartScene.h"
#include "GameScene.h"
#include "StaticData.h"
#include "PongPongPiaData.h"
#include "PersonalAudioEngine.h"
#include "ChooseChapterScene.h"

USING_NS_CC;

CCScene* StartLayer::scene()
{
	CCScene* scene = CCScene::create();
	StartLayer* layer = StartLayer::create();
	scene->addChild(layer);
	return scene;
}

bool StartLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCLayer::init());

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *pBg = CCSprite::create(STATIC_DATA_STRING("startscene_background"));
		CC_BREAK_IF(! pBg);
		pBg->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		this->addChild(pBg, 0);

		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("play_btn_normal"),
			STATIC_DATA_STRING("play_btn_selected"),
			this,
			menu_selector(StartLayer::startGame));
		CC_BREAK_IF(! pStartItem);

		pStartItem->setPosition(ccp(winSize.width - pStartItem->getContentSize().width / 2, pStartItem->getContentSize().height / 2));

		CCMenuItemImage *pQuitItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("quit_btn_normal"),
			STATIC_DATA_STRING("quit_btn_selected"),
			this,
			menu_selector(StartLayer::quitGame));
		CC_BREAK_IF(! pQuitItem);

		this->cacheInit();

		pQuitItem->setPosition(ccp(pStartItem->getContentSize().width / 2, pStartItem->getContentSize().height / 2));
		
		// Create a menu with the "ok", "quit" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pStartItem, pQuitItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		bRet = true;

	} while (0);

	return bRet;
}

void StartLayer::audioAndUserDataInit()
{
	PongPongPiaData::sharedPongPongPiaData();
	PersonalAudioEngine::sharedEngine();
}

void StartLayer::startGame(CCObject *pSender)
{
	PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("click_button"));
	ChooseChapterScene* chooseChapterScene = ChooseChapterScene::create();
	CCTransitionShrinkGrow* transitionToChooseChapterScene = CCTransitionShrinkGrow::create(1.2f,chooseChapterScene);
	CCDirector::sharedDirector()->replaceScene(transitionToChooseChapterScene);
}

void StartLayer::quitGame(CCObject* pSender)
{
	// "quit" menu item clicked
	PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("click_button"));

	CCDirector::sharedDirector()->end();
}

void StartLayer::cacheInit(){
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("gamescene.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("prop_resource.plist");
}

