//
//  LoseLayer.h
//  PongPongPia
//
//  Created by HuFan on 13-11-7.
//
//

#ifndef __PongPongPia__LoseLayer__
#define __PongPongPia__LoseLayer__

#include "cocos2d.h"

class LoseLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(LoseLayer);
	virtual bool init();
	virtual void registerWithTouchDispatcher(void);
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void onEnter();
	virtual void onExit();

	void showLoseLayer();
	void playWinMusic();
	void playAgain(CCObject *pSender);
	void giveupCallback(CCObject* pSender);
	//void play
	//protected:

};

#endif
