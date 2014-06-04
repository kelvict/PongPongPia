#include "HRocker.h"

void HRocker::updatePos(float dt){
    jsSprite->setPosition(
            ccpAdd(
                jsSprite->getPosition(), 
                ccpMult(
                        ccpSub(currentPoint, jsSprite->getPosition()), 0.5
                    )
            )
        );
}

//启动摇杆
void HRocker::Active()
{
    if (!active) {
        active = true;
        this->schedule(schedule_selector(HRocker::updatePos));//添加刷新函数
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);//添加触摸委托
    }else {
        //
    }
}

//解除摇杆
void   HRocker::Inactive()
{
    if (active) {
        active = false;
        this->unschedule(schedule_selector(HRocker::updatePos));//删除刷新
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);//删除委托
    }else {
        //
    }
}

//摇杆方位
CCPoint HRocker::getDirection()
{
	if (getVelocity() < 0.5)
		return ccp(0, 0);
	return ccpNormalize(ccpSub(centerPoint, currentPoint));
}

//摇杆力度
float HRocker::getVelocity()
{
    return ccpDistance(centerPoint, currentPoint);
}


/* 使用方法
 *    第一个参数aPoint：摇杆中心点的坐标
 *    第二个参数aRadius: 摇杆的半径
 *    第三个参数：aJsSprite :摇杆的图片资源精灵
 *    第四个参数：aJsBg: 摇杆背景图片资源精灵
 *    第五个参数：isFollowRole：是否让摇杆永远跟随用户触屏点（Himi新添加的功能）
 */
HRocker* HRocker:: HRockerWithCenter(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole)
{
    HRocker *jstick = HRocker::create();
    jstick->initWithCenter(aPoint, aRadius, aJsSprite, aJsBg, _isFollowRole);
    return jstick;
}

bool HRocker::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    if (!active)
    {
        return false;
    }
    this->setVisible(true);
    CCPoint touchPoint = touch->locationInView();
    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
    if(!isFollowRole){
        if (ccpDistance(touchPoint, centerPoint) > radius){
            return false;
        }
    }
    currentPoint = touchPoint;
    if(isFollowRole){
        centerPoint = currentPoint;
        jsSprite->setPosition(currentPoint);
        this->getChildByTag(88)->setPosition(currentPoint);
    }
    return true;
}

void  HRocker::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->locationInView();
    touchPoint = CCDirector:: sharedDirector()->convertToGL(touchPoint);
    if (ccpDistance(touchPoint, centerPoint) > radius)
    {
        currentPoint = ccpAdd(centerPoint, ccpMult(ccpNormalize(ccpSub(touchPoint, centerPoint)), radius));
    }else {
        currentPoint = touchPoint;
    }
}
void  HRocker::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    currentPoint = centerPoint;
    if(isFollowRole){
        this->setVisible(false);
    }
}


/* 初始化方法
 *    第一个参数aPoint：摇杆中心点的坐标
 *    第二个参数aRadius: 摇杆的半径
 *    第三个参数：aJsSprite :摇杆的图片资源精灵
 *    第四个参数：aJsBg: 摇杆背景图片资源精灵
 *    第五个参数：isFollowRole：是否让摇杆永远跟随用户触屏点（Himi新添加的功能）
 */
HRocker* HRocker::initWithCenter(CCPoint aPoint, float aRadius, CCSprite* aJsSprite, CCSprite* aJsBg, bool _isFollowRole)
{
    isFollowRole =_isFollowRole;
    active = false;
    radius = aRadius;
    if(!_isFollowRole){
        centerPoint = aPoint;
    }else{
        centerPoint = ccp(0,0);
    }

    currentPoint = centerPoint;
    jsSprite = aJsSprite;
    jsSprite->setPosition(centerPoint);
    aJsBg->setPosition(centerPoint);
    aJsBg->setTag(88);
    this->addChild(aJsBg);
    this->addChild(jsSprite);
    if(isFollowRole){
        this->setVisible(false);
    }
    this->Active();//激活摇杆
    return this;
}