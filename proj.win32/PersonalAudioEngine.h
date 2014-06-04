//
//  PersonalAudioEngine.h
//  PongPongPia
//
//  Created by HuFan on 13-9-15.
//
//

#ifndef __PongPongPia__PersonalAudioEngine__
#define __PongPongPia__PersonalAudioEngine__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class PersonalAudioEngine : public CocosDenshion::SimpleAudioEngine
{
public:
	void setBackgroundMusicVolume(float volume);
	void setEffectsVolume(float volume);

	static PersonalAudioEngine* sharedEngine();

	void purge();
	bool init();
protected:
	PersonalAudioEngine();
	~PersonalAudioEngine();
};

#endif /* defined(__PongPongPia__PersonalAudioEngine__) */
