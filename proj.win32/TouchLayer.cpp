//
//  TouchLayer.cpp
//  PongPongPia
//
//  Created by HuFan on 13-9-12.
//
//

#include "TouchLayer.h"
#include "GameScene.h"
USING_NS_CC;
bool TouchLayer::init()
{
	this->createJoystick();
	this->setTouchEnabled(true);
	return true;
}

GameScene* TouchLayer::getGameScene()
{
	return (GameScene*)this->getParent();
}

bool TouchLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	joystickSkin->setPosition(this->locationFromTouch(touch));
	this->setIsTouched(true);
	return true;
}
void TouchLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	joystick->ccTouchBegan(touch, event);
	joystickSkin->setVisible(true);
	CCPoint scaledV = ccpMult(joystick->getVelocity(), 1); 
	this->setDirection(scaledV);
}

void TouchLayer::ccTouchEnded(CCTouch* touch, CCEvent* event)
{	
	joystickSkin->setVisible(false);
	this->setTouchEnabled(true);
	this->setIsTouched(false);
}

void TouchLayer::setTouchEnabled(bool flag)
{
	if (m_bIsTouchEnabled != flag){
		m_bIsTouchEnabled = flag;
		if(flag){
			CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		}else{
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		}
	}
}

CCPoint TouchLayer::locationFromTouch(CCTouch* touch)
{
	return CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
}

void TouchLayer::createJoystick()
{
	float joystickRadius=50;

	joystick=new SneakyJoystick();
	joystick->autorelease();
	joystick->initWithRect(CCRectZero);

	joystick->setAutoCenter(true);
	joystick->setHasDeadzone(true);
	joystick->setDeadRadius(10);

	joystickSkin=new SneakyJoystickSkinnedBase();
	joystickSkin->autorelease();
	joystickSkin->init();
	joystickSkin->setBackgroundSprite(CCSprite::create("button-disabled.png"));
	joystickSkin->setThumbSprite(CCSprite::create("button-disabled.png"));
	joystickSkin->getThumbSprite()->setScale(0.5f);
	joystickSkin->getThumbSprite()->setColor(ccc3(255, 0, 0));
	joystickSkin->setPosition(ccp(joystickRadius,joystickRadius));
	joystickSkin->setJoystick(joystick);

	this->addChild(joystickSkin);
	joystickSkin->setVisible(false);
}