//
//  PanelLayer.h
//  PongPongPia
//
//  Created by HuFan on 13-9-16.
//
//


#ifndef __PongPongPia__PanelLayer__
#define __PongPongPia__PanelLayer__

#define MENUTAG 8888
#include"ProgressBar.h"
#include "cocos2d.h"
#include "Prop.h"
class PanelLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(PanelLayer);
	bool init();
	CC_SYNTHESIZE(cocos2d::CCMenuItemImage*, propLeft, PropLeft);
	CC_SYNTHESIZE(cocos2d::CCMenuItemImage*, propRight, PropRight);
	CC_SYNTHESIZE(Prop*,leftProp,LeftProp);
	CC_SYNTHESIZE(Prop*,rightProp,RightProp);
	void placeProp(Prop* prop); // interface to set the prop

	CC_SYNTHESIZE(cocos2d::CCMenuItem*, eneygyButtonNormal,       EneygyButtonNormal);
	CC_SYNTHESIZE(cocos2d::CCMenuItemImage*, eneygyButtonFull,      EneygyButtonFull);
	ProgressBar *energyBar;
	void increaceEnetgy();
	void fullEnergy();

protected:
	CCMenu* menuProp;
	CCMenu* menuUltimate;
	void pause(cocos2d::CCObject* pSender);
	void setting(cocos2d::CCObject* pSender);
	void useLeftPro(cocos2d::CCObject* pSender);
	void useRightPro(cocos2d::CCObject* pSender);
	void removeAndPlace(int tag, const char* propName);
	void useUltimate(cocos2d::CCObject* pSender);
	bool leftPlaced;
	bool rightPlaced;
	cocos2d::CCLabelTTF* _scheduleLabel;
};

#endif /* defined(__PongPongPia__PanelLayer__) */
