#ifndef __ROLE_H__
#define __ROLE_H__


#include<cocos2d.h>
#include<Equipment.h>
#include "Swamp.h"
#include "Wind.h"
#include "misc_nodes\CCMotionStreak.h"
USING_NS_CC;

typedef enum{
	BiaBo=0,
	BiaHo,
	BiaKo,
	BiaMo,
	BadEgg=4,
	BadEggBlue,
	EvilBadEgg,
	EvilBadEggBlue,
	EvilBadEggGreen,
	EvilBadEggRed
}RoleType;

typedef enum{
	LEFT_FACING_DIRECTION=0,
	RIGHT_FACING_DIRECTION
}FacingDirection;

typedef enum{
	Player=0,
	Teamate,
	Enemy
}Status;

typedef enum{
	state_normal=0,
	state_ultimate,
	state_frozen,
	state_petrified,
	state_reverse
}State;

typedef enum{
	normal_standing=0,
	normal_spinning,
	ultimate_spinning,
	frozen_standing,
	petrified_standing
}BodyActionTag;

typedef enum{
	moveBy,
	stay
}RoleActionTag;

typedef enum {
	NONE_ACTION,
	STOP_ACTION,
	SLOW_ACTION,
	FAST_ACTION

}RoleActionState;


class Role :
	public cocos2d::CCNode
{
public:
	static Role* create(RoleType roleType ,Status status,Equipment* pEquipment,FacingDirection direction=LEFT_FACING_DIRECTION);
	bool init(RoleType roleType,Status status,Equipment* pEquipment,FacingDirection direction=LEFT_FACING_DIRECTION);

	CC_SYNTHESIZE(RoleActionState,roleActionState, RoleActionState);

	CC_SYNTHESIZE(RoleType,roleType,RoleType);//个人角色
	CC_SYNTHESIZE(Status,status,Status);//个人身份	
	CC_SYNTHESIZE(State,state,State);//个人状态
	CC_SYNTHESIZE(int,level,Level);

	CC_SYNTHESIZE(float,SP,SP);//能量柱大小

	CC_SYNTHESIZE(CCString,username,Username);

	CC_SYNTHESIZE(Equipment,equipment,Equipment);//装备
	CC_SYNTHESIZE(int,AGI,AGI);//敏捷力or速度
	CC_SYNTHESIZE(int,STR,STR);//力量or冲击力
	CC_SYNTHESIZE(int,DEF,DEF);//防御力or防冲击
	CC_SYNTHESIZE(int,EXP,EXP);//经验值
	CC_SYNTHESIZE(int,honor,Honor);//荣誉值
	CC_SYNTHESIZE(bool,alive,Alive);
	CC_SYNTHESIZE(bool,isReverse,IsReverse);
	CC_SYNTHESIZE(FacingDirection,direction,Direction);
	CC_SYNTHESIZE_READONLY(cocos2d::CCSprite*,body,Body);

	CC_SYNTHESIZE(CCPoint,lastPosition,LastPosition);

	CC_SYNTHESIZE(int,tempAGI,TempAGI);

	CC_SYNTHESIZE(CCString, roleName ,RoleName);

	CC_SYNTHESIZE(bool,inSwamp, InSwamp);
	float getSpeed();
	float getScaleRatio();

	Equipment* getPEquipment();
	void setPEquipment(Equipment* equipment);

	bool getUltimateState(void);
	bool getNormal(void);



	bool startNormalSpin_repeatForever(void);
	void stopNormalSpin_repeatForever(void);

	bool startUltimateSpin_ForeverTimeAction();
	void stopUltimateSpin_ForeverTimeAction(void);

	void startUltimateSpin_FiniteTimeAction();

	void frozen(Role& role);
	void petrified(Role& role);

	void startFrozenStanding(void);
	void stopFrozenStanding(void);

	bool startPetrifiedStanding_ForeverTimeAction(void);
	void stopPetrifiedStanding_ForeverTimeAction(void);
	void startPetrifiedStanding_FiniteTimeAction();
	void startReverseSpinning(void);
	void stopReverseSpinning(void);

	CCPoint getVelocity(void);
	void setScaleAndZOrder(void);

	void moveBy(CCPoint velocity);
	void bumpBy(CCPoint& velocity);

	void reverseMoveBy(CCPoint& reverseVelocity);

	void getFrozen(void);
	void getPetrified(void);

	void getBump(Role* role);
	void stand(void);

	CCRect getCollisionRectangle(void);

	void resumeNormalSpinning(float delay);
	void resumeNormalSpinningFromPetrifiedStanding(float delay);

	void setPositionScaleAndZOrder(CCPoint position);

	//AutomaticalBumping
	void automaticalBumping(Role* role);
	void stopAutomaticalBumping(void);

	void intelligentBumping(Role* role);
	void outOfBounds();
	void killed();
	virtual void update(float delta);

	void setRoleActionStateToRunCallBack(CCObject* psend);
protected:
	void setSpinAnimationCache();
	CCString* getAnimationNameWithFormat(std::string key);
	CCString* getSpriteFrameNameWithFormat(std::string key,int frameNumber);
	bool initMotionStreak();
	CCMotionStreak * strike;

};

#endif