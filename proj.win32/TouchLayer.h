//
//  TouchLayer.h
//  PongPongPia
//
//  Created by HuFan on 13-9-12.
//
//

#ifndef __PongPongPia__TouchLayer__
#define __PongPongPia__TouchLayer__
#include "cocos2d.h"
#include "SneakyJoystick.h"
#include "SneakyJoystickSkinnedBase.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"

class GameScene;

class TouchLayer:  public cocos2d::CCLayer
{
public:
	CREATE_FUNC(TouchLayer);
	bool init();
	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	void setTouchEnabled(bool flag);

	CC_SYNTHESIZE(cocos2d::CCPoint, direction, Direction);
	CC_SYNTHESIZE(bool, isTouched, IsTouched);
private:
	SneakyJoystick* joystick;
	SneakyJoystickSkinnedBase *joystickSkin;

	GameScene* getGameScene();
	void createJoystick();
	cocos2d::CCPoint locationFromTouch(cocos2d::CCTouch *touch);

};

#endif /* defined(__FishingJoy__TouchLayer__) */
