#pragma once
#include <cocos2d.h>
#include"Person.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class Boat :
	public cocos2d::CCNode
{
private:
	RiverAdr riverAdr;//在河流的左边或右边
public:
	static Person* create();
	bool init(); 

	virtual void AcrossRiver(); //过河

	RiverAdr GetRiverAdr();
};