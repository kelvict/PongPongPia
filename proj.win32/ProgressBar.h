//
//  ProgressBar.h
//  PongPongPia
//
//  Created by HuFan on 13-10-06.
//
//

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "cocos2d.h"

class ProgressBar : public cocos2d::CCProgressTimer
{
public:
	CREATE_FUNC(ProgressBar);
	bool init();
    void progressBy(float delta);
  
    void progressTo(float destination);

	void increaceEnetgy();
    /**
     *	@brief	     ÉèÖÃ½ø¶ÈÌõÇ°½øµÄËÙÂÊ
     *
     *	@param 	Speed 	ËÙÂÊ
     *
     *	@return
     */
    CC_SYNTHESIZE(float, _speed, Speed);
   // CC_SYNTHESIZE(ProgressDelegate*, _target, Target);
    
    /**
     *	@brief	    Îª½ø¶ÈÌõÌí¼ÓÇ°¾°»ò±³¾°
     *
     *	@param 	Foreground 	Ç°¾°£¬ÀýÈç½ø¶ÈÌõµÄµ±Ç°µÄ°Ù·Ö±ÈÖµ
     *	@param 	Background 	±³¾°
     *
     *	@return
     */
    CC_PROPERTY(cocos2d::CCNode*, _background, Background);
    CC_PROPERTY(cocos2d::CCNode*, _foreground, Foreground);
protected:
    void updatePercentage();
};
#endif