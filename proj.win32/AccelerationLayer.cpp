#include "AccelerationLayer.h"
#include <iostream>
#include "UserData.h"

using namespace std;

AccelerationLayer* AccelerationLayer::create()
{
	AccelerationLayer* accelerationLayer = new AccelerationLayer();
	accelerationLayer->init();
	accelerationLayer->autorelease();
	return accelerationLayer;
}

bool AccelerationLayer::init()
{
	bool bRet = false;
	do{
		CC_BREAK_IF(!CCLayer::init());

		if (true == USER->getIsAcceleratorOn()) {
			this->setAccelerometerEnabled(true);
			IsSET = false;
			minchange = 1.2;
			direction.x = 0;
			direction.y = 0;
		}
		else
		{
			this->setAccelerometerEnabled(false);
			IsSET = false;
			minchange = 1.2;
			direction.x = 0;
			direction.y = 0;
		}
		
		bRet = true;
	}while(0);
	return bRet;
}


void AccelerationLayer::didAccelerate(CCAcceleration* pAccelerationValue)
{
	direction.x = 0;
	direction.y = 0;
	float x = pAccelerationValue->x*15;
	float y = pAccelerationValue->y*15;
	if(!IsSET)
	{
		initDirection.x  = x;
		initDirection.y = y;
std::cout<<initDirection.x<<"    "<<initDirection.y<<std::endl;
		IsSET = true;
		return ;
	}
	x-=initDirection.x;
	y-=initDirection.y;


	float all = x*x + y*y;

	//
	if(all >minchange)
	{
		direction.x = x;
		direction.y = y;
		direction = ccpNormalize(direction);
		//		cout<<"x:"<<direction.x<<"    y:"<<direction.y<<endl;
	}

}

CCPoint* AccelerationLayer::GetDirection()
{
	return &direction;
}

AccelerationLayer::~AccelerationLayer()
{
	this->setAccelerometerEnabled(false);
}


