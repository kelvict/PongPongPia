//
//  PongPongPiaData.h
//  PongPongPiaData
//
//  Created by HuFan on 13-9-15.
//
//

#ifndef __PongPongPia__PongPongPiaData__
#define __PongPongPia__PongPongPiaData__
#include "cocos2d.h"
class PongPongPiaData : public cocos2d::CCObject
{
public:
    static PongPongPiaData* sharedPongPongPiaData();
    //CC_SYNTHESIZE(int , _gold, Gold);
    CC_SYNTHESIZE(bool, _isBeginner, IsBeginner);
    CC_SYNTHESIZE(float, _soundVolume, SoundVolume);
    CC_SYNTHESIZE(float, _musicVolume, MusicVolume);
    
    /**
     *	@brief	 内存不足时调用
     */
    void purge();
    
    /**
     *	@brief	 将数据从内存保存到外部文件中
     */
    void flush();
    
    /**
     *	@brief	 对Gold的操作
     *
     *	@param 	delta 	正负值均可
     */
    void alterGold(int delta);
    /**
     *	@brief	 重置游戏数据为默认数值
     */
    void reset();
protected:
    PongPongPiaData();
    ~PongPongPiaData();
    bool init();
};

#endif /* defined(__PongPongPia__PongPongPiaData__) */
