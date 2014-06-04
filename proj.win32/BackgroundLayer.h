//
//  BackgroundLayer.h
//  PongPongPia
//
//  Created by HuFan on 13-9-17.
//
//

#ifndef __PongPongPia__BackgroundLayer__
#define __PongPongPia__BackgroundLayer__
#include "cocos2d.h"

typedef enum{
	Sky_Background,
	Grasslands_Background,
	Challenge_Background,
	Cape_Background,
	OuterSpace_Background
}GameBackgroundType;

class BackgroundLayer : public cocos2d::CCLayer
{
public:
	static BackgroundLayer* create(GameBackgroundType type = GameBackgroundType(0));
	bool init(GameBackgroundType type = GameBackgroundType(0) );

	CC_SYNTHESIZE(cocos2d::CCArray*, fencePnts, FencePnts);
	//cocos2d::CCPoint[] getPoint();
	~BackgroundLayer();
};

#endif /* defined(__FishingJoy__BackgroundLayer__) */
