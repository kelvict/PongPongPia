//
//  PongPongPiaData.cpp
//  PongPongPiaData
//
//  Created by HuFan on 13-9-15.
//
//

#include "PongPongPiaData.h"
#include "StaticData.h"

USING_NS_CC;

static PongPongPiaData* _sharedPongPongPiaData = NULL;

PongPongPiaData* PongPongPiaData::sharedPongPongPiaData()
{
	if(_sharedPongPongPiaData==NULL){
		_sharedPongPongPiaData = new PongPongPiaData();
		_sharedPongPongPiaData->init();
	}
	return _sharedPongPongPiaData;
}
void PongPongPiaData::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedPongPongPiaData);
}
PongPongPiaData::PongPongPiaData()
{

}
PongPongPiaData::~PongPongPiaData()
{
	this->flush();
}
bool PongPongPiaData::init()
{
	_isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner",true);
	if(_isBeginner == true){
		this->reset();
		this->flush();
		this->setIsBeginner(false);
	}else{
		_isBeginner = CCUserDefault::sharedUserDefault()->getBoolForKey("beginner");
		_soundVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("sound");
		_musicVolume = CCUserDefault::sharedUserDefault()->getFloatForKey("music");
		//_gold = CCUserDefault::sharedUserDefault()->getIntegerForKey("gold");
		CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
	}
	return true;
}
void PongPongPiaData::reset()
{
	//int gold = STATIC_DATA_INT("default_gold");
	//this->setGold(gold);
	this->setIsBeginner(true);
	this->setMusicVolume(1);
	this->setSoundVolume(1);
	this->flush();
}

void PongPongPiaData::flush()
{
	CCUserDefault::sharedUserDefault()->setFloatForKey("sound", this->getSoundVolume());
	CCUserDefault::sharedUserDefault()->setBoolForKey("beginner", this->getIsBeginner());
	// CCUserDefault::sharedUserDefault()->setIntegerForKey("gold", this->getGold());
	CCUserDefault::sharedUserDefault()->setFloatForKey("music", this->getMusicVolume());
	CCUserDefault::sharedUserDefault()->flush();
	CCUserDefault::sharedUserDefault()->purgeSharedUserDefault();
}
