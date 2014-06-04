#pragma once
#include <cocos2d.h>
#include "cocos2d.h"

using namespace cocos2d;

class AccelerationLayer : public CCLayer
{
private:
	CCPoint direction;
	bool IsSET;
	CCPoint initDirection;
	float minchange ;
public:
	~AccelerationLayer();
	static AccelerationLayer* create();
	bool init();
	void setInitDirection();
	virtual void didAccelerate(CCAcceleration* pAccelerationValue);
	CCPoint* GetDirection();

	
};