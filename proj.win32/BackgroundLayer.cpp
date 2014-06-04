//
//  BackgroundLayer.cpp
//  PongPongPia
//
//  Created by HuFan on 13-9-17.
//
//



#include "BackgroundLayer.h"
#include "StaticData.h"
USING_NS_CC;
bool BackgroundLayer::init(GameBackgroundType type)
{
	if(CCLayer::init()){
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCString* str = CCString::createWithFormat(STATIC_DATA_STRING("game_background_format"),(int)type);
		CCSprite* background = CCSprite::create(str->getCString());
		background->setPosition(CCPointMake(winSize.width*0.5,winSize.height*0.5));
		this->addChild(background);

		//设置背景的相关点位置：
		int capacity = 6;
		fencePnts = CCArray::createWithCapacity(capacity);
		CC_SAFE_RETAIN(fencePnts);
		
		CCPoint point = CCPointMake(100, 100);
		fencePnts->addObject(&point);

		point = CCPointMake(100, 150);
		fencePnts->addObject(&point);

		point = CCPointMake(100, 150);
		fencePnts->addObject(&point);

		point = CCPointMake(100, 200);
		fencePnts->addObject(&point);

		point = CCPointMake(150, 200);
		fencePnts->addObject(&point);

		point = CCPointMake(200, 200);
		fencePnts->addObject(&point);

		return true;
	}
	return false;
}

BackgroundLayer::~BackgroundLayer()
{
	 CC_SAFE_RELEASE(fencePnts);
}

BackgroundLayer* BackgroundLayer::create( GameBackgroundType type /*= 0*/ )
{
	BackgroundLayer* backgroundLayer = new BackgroundLayer();
	backgroundLayer->init(type);
	backgroundLayer->autorelease();
	return backgroundLayer;
}
