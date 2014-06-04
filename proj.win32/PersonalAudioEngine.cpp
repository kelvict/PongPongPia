//
//  PersonalAudioEngine.cpp
//  PongPongPia
//
//  Created by HuFan on 13-9-15.
//
//

#include "PersonalAudioEngine.h"
#include "PongPongPiaData.h"
#include "StaticData.h"
static PersonalAudioEngine* _sharedEngine = NULL;
using namespace CocosDenshion;
USING_NS_CC;
void PersonalAudioEngine::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);

	PongPongPiaData::sharedPongPongPiaData()->setMusicVolume(volume);
}
void PersonalAudioEngine::setEffectsVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
	PongPongPiaData::sharedPongPongPiaData()->setSoundVolume(volume);
}
PersonalAudioEngine* PersonalAudioEngine::sharedEngine()
{
	if(_sharedEngine==NULL){
		_sharedEngine = new PersonalAudioEngine();
		_sharedEngine->init();
	}
	return _sharedEngine;
}
bool PersonalAudioEngine::init()
{
	this->preloadBackgroundMusic(STATIC_DATA_STRING("gamescene_background_music"));
	this->preloadEffect(STATIC_DATA_STRING("click_button"));
	this->preloadEffect(STATIC_DATA_STRING("sound_shot"));
	this->preloadBackgroundMusic(STATIC_DATA_STRING("victory_music"));
	this->preloadBackgroundMusic(STATIC_DATA_STRING("failed_music"));
	//
	this->setBackgroundMusicVolume(PongPongPiaData::sharedPongPongPiaData()->getMusicVolume());
	this->setEffectsVolume(PongPongPiaData::sharedPongPongPiaData()->getSoundVolume());

	return true;
}
void PersonalAudioEngine::purge()
{

}
PersonalAudioEngine::PersonalAudioEngine()
{

}
PersonalAudioEngine::~PersonalAudioEngine()
{

}
