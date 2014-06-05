#include "ProgressBar.h"
#include "GameScene.h"
#include "StaticData.h"

USING_NS_CC;

bool ProgressBar::init()
{
	bool bRet = false;
	do 
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCProgressTimer::initWithSprite(CCSprite::create(STATIC_DATA_STRING("energyBar")));

		this->setType(kCCProgressTimerTypeBar);
		//    Setup for a bar starting from the left since the midpoint is 0 for the x
		this->setMidpoint(ccp(1,0));
		//    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
		this->setBarChangeRate(ccp(1, 0));
		this->setSpeed(16.0f);
		//ÓÃÀ´ÉèÖÃ½ø¶ÈÌõµÄ½ø¶È
		this->setPercentage(0);
		this->setPosition(CCPointZero);
		this->setBackground(CCSprite::create(STATIC_DATA_STRING("energyBarBG")));
		bRet = true;
	} while (0);

	return bRet;
}

void ProgressBar::setBackground(CCNode* bg)
{
	this->removeChild(_background,true);
	_background = bg;
	CCSize size = this->getSprite()->getContentSize();
	_background->setPosition(CCPointMake(size.width*0.5, size.height*0.5));
	this->addChild(_background, -1);
}

CCNode* ProgressBar::getBackground()
{
	return _background;
}

void ProgressBar::setForeground(CCNode* fg)
{
	this->removeChild(_foreground, true);
	_foreground = fg;
	CCSize size = this->getSprite()->getContentSize();
	_foreground->setPosition(CCPointMake(size.width*0.5, size.height*0.5));
	this->addChild(_foreground, 1);
}
CCNode* ProgressBar::getForeground()
{
	return _foreground;
}

void ProgressBar::increaceEnetgy()
{
	if (this->getPercentage() + _speed >= 65) {
		// set the flag that is full of energy
		GameScene* gamescene =  (GameScene*)this->getParent()->getParent();
		gamescene->fullEnergy();
		this->setPercentage(0.0f);
		return;
	}
	this->setPercentage(this->getPercentage() + _speed);
}