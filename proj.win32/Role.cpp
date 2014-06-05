#include "Role.h"
#include<StaticData.h>

#include "Reward.h"

Role* Role::create(RoleType roleType ,Status status,Equipment* pEquipment,FacingDirection direction){
	Role* role = new Role();
	role->init(roleType,status,pEquipment,direction);
	role->autorelease();
	return role;
}
bool Role::init(RoleType roleType,Status status,Equipment* pEquipment,FacingDirection direction){

	this->setUsername(*CCString::create("Undefined"));

	this->setRoleType(roleType);
	this->setStatus(status);
	this->setPEquipment(pEquipment);
	this->setDirection(direction);

	this->setIsReverse(false);

	this->setRoleActionState(NONE_ACTION);
	this->setState(state_normal);
	this->setSP(0);
	CCString* rolePropertyIndex=CCString::createWithFormat(STATIC_DATA_STRING("role_property"),roleType);
	CCDictionary* rolePropertyDictionary = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* roleProperty= dynamic_cast<CCDictionary*>(rolePropertyDictionary->objectForKey(rolePropertyIndex->getCString()));
	
	//change
	CCDictionary* staticDataDict = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* weaponDict =(CCDictionary*) staticDataDict->objectForKey(CCString::createWithFormat(STATIC_DATA_STRING("reward_info_format"),(int)k_Reward_Weapon,(int)this->getPEquipment()->getWeapon())->getCString());
	CCDictionary* baseDict =(CCDictionary*) staticDataDict->objectForKey(CCString::createWithFormat(STATIC_DATA_STRING("reward_info_format"),(int)k_Reward_Base,(int)this->getPEquipment()->getBase())->getCString());
	CCDictionary* plateDict =(CCDictionary*) staticDataDict->objectForKey(CCString::createWithFormat(STATIC_DATA_STRING("reward_info_format"),(int)k_Reward_Plate,(int)this->getPEquipment()->getPlate())->getCString());


	this->setHonor(0);
	
	this->getPEquipment()->getWeapon();

	this->setSTR(roleProperty->valueForKey("STR")->intValue()+weaponDict->valueForKey("STR_increment")->intValue()+baseDict->valueForKey("STR_increment")->intValue()+plateDict->valueForKey("STR_increment")->intValue());
	this->setAGI(roleProperty->valueForKey("AGI")->intValue()+weaponDict->valueForKey("AGI_increment")->intValue()+baseDict->valueForKey("AGI_increment")->intValue()+plateDict->valueForKey("AGI_increment")->intValue());
	this->setDEF(roleProperty->valueForKey("DEF")->intValue()+weaponDict->valueForKey("DEF_increment")->intValue()+baseDict->valueForKey("DEF_increment")->intValue()+plateDict->valueForKey("DEF_increment")->intValue());
	this->setAlive(true);
	this->setInSwamp(false);
	this->setSpinAnimationCache();

	this->body = CCSprite::create();
	this->initMotionStreak();
	this->addChild(this->body);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setPositionScaleAndZOrder(ccp(size.width/2,size.height/2));
//	this->setLastPosition(size.width/2,size.height/2);
	this->scheduleUpdate();

	return true;
}

bool Role::initMotionStreak(){
	strike = CCMotionStreak::streakWithFade(1.0f,20.0f,40.0f,ccc3(255,255,0),"following_shader/feedback_following.png");
	strike->setFastMode(true);
	strike->tintWithColor(ccc3(255,0,0));
	strike->setVisible(false);
	this->addChild(strike);
	strike->setPosition(ccp((this->getCollisionRectangle().getMaxX()+this->getCollisionRectangle().getMinX())/2,(this->getCollisionRectangle().getMaxY()+this->getCollisionRectangle().getMinY())/2-25));

	return true;
}

void Role::update(float delay){

	strike->setPosition(ccp((this->getCollisionRectangle().getMaxX()+this->getCollisionRectangle().getMinX())/2,(this->getCollisionRectangle().getMaxY()+this->getCollisionRectangle().getMinY())/2-25));
	if(!strike->isVisible()){
		strike->setVisible(true);
	}
}

void Role::setSpinAnimationCache(){
	int spinAnimationFrameCount = STATIC_DATA_INT("role_spin_animation_frame_count");

	CCArray* normalSpinSpriteFrames = CCArray::createWithCapacity(spinAnimationFrameCount);
	CCArray* ultimateSpinSpriteFrames = CCArray::createWithCapacity(spinAnimationFrameCount);


	for(int i = 0;i<spinAnimationFrameCount;i++){
		//////////////////////////////////////////////////////////////////////////
//normalSpinSpriteFrames
		CCString* filename = this->getSpriteFrameNameWithFormat("role_spin_animation_frame_format",i);
		CCSpriteFrame* normalSpinSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(filename->getCString());
		normalSpinSpriteFrames->addObject(normalSpinSpriteFrame);
//////////////////////////////////////////////////////////////////////////
//ultimateSpinSpriteFrames
		if(this->roleType != BadEgg&&this->roleType != EvilBadEgg&&this->roleType != BadEggBlue&&this->roleType != EvilBadEggBlue&&this->roleType != EvilBadEggGreen&&this->roleType != EvilBadEggRed){
			CCString* ultimateSpinFrameFilename = CCString::createWithFormat(STATIC_DATA_STRING("role_spin_animation_frame_format"),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),state_ultimate,i);
			CCSpriteFrame* ultimateSpinSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ultimateSpinFrameFilename->getCString());
			ultimateSpinSpriteFrames->addObject(ultimateSpinSpriteFrame);		
		}
	}
//////////////////////////////////////////////////////////////////////////
//normalSpinSpriteFrames
	CCAnimation* normalSpinAnimation = CCAnimation::createWithSpriteFrames(normalSpinSpriteFrames);
	normalSpinAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("role_spin_animation_delay"));
	CCString* normalSpinAnimationName = this->getAnimationNameWithFormat("role_spin_animation_format");
	CCAnimationCache::sharedAnimationCache()->addAnimation(normalSpinAnimation,normalSpinAnimationName->getCString());

//////////////////////////////////////////////////////////////////////////
//ultimateSpinSpriteFrames
	if(this->roleType != BadEgg&&this->roleType != EvilBadEgg&&this->roleType != BadEggBlue&&this->roleType != EvilBadEggBlue&&this->roleType != EvilBadEggGreen&&this->roleType != EvilBadEggRed){
		CCAnimation* ultimateSpinAnimation = CCAnimation::createWithSpriteFrames(ultimateSpinSpriteFrames);
		ultimateSpinAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("role_spin_animation_delay"));
		CCString* ultimateSpinAnimationName = CCString::createWithFormat(STATIC_DATA_STRING("role_spin_animation_format"),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),state_ultimate);//to be Modified
		CCAnimationCache::sharedAnimationCache()->addAnimation(ultimateSpinAnimation,ultimateSpinAnimationName->getCString());
	}

//////////////////////////////////////////////////////////////////////////
//petrifiedSpriteFrames

	CCArray* petrifiedSpriteFrames = CCArray::createWithCapacity(1);

	CCString* petrifiedFrameFilename = CCString::createWithFormat(STATIC_DATA_STRING("role_spin_animation_frame_format"),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),state_petrified,0);
	CCSpriteFrame* petrifiedSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(petrifiedFrameFilename->getCString());
	petrifiedSpriteFrames->addObject(petrifiedSpriteFrame);

	CCAnimation* petrifiedAnimation = CCAnimation::createWithSpriteFrames(petrifiedSpriteFrames);
	petrifiedAnimation->setDelayPerUnit(STATIC_DATA_FLOAT("role_spin_animation_delay"));
	CCString* petrifiedAnimationName = CCString::createWithFormat(STATIC_DATA_STRING("role_spin_animation_format"),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),state_petrified);//to be Modified
	CCAnimationCache::sharedAnimationCache()->addAnimation(petrifiedAnimation,petrifiedAnimationName->getCString());



	//CC_SAFE_RELEASE(normalSpinSpriteFrames);
	//CC_SAFE_RELEASE(ultimateSpinSpriteFrames);
	//CC_SAFE_RELEASE(petrifiedSpriteFrames);
}

void Role::setPositionScaleAndZOrder(CCPoint position){
	this->body->setPosition(position);
	this->setScaleAndZOrder();
}

bool Role::startNormalSpin_repeatForever(void){
	this->setState(state_normal);
	if(this->getState()==state_normal){
		this->body->stopAllActions();
		CCAnimation* normalSpinAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(this->getAnimationNameWithFormat("role_spin_animation_format")->getCString());
		CCAnimate* normalSpinAnimate = CCAnimate::create(normalSpinAnimation);
		normalSpinAnimate->setTag(normal_spinning);
		body->runAction(CCRepeatForever::create(normalSpinAnimate));
		return true;
	}
	else{
		return false;
	}
}
void Role::stopNormalSpin_repeatForever(void){
	body->stopActionByTag(normal_spinning);
}

CCString* Role::getAnimationNameWithFormat(std::string key){
	return CCString::createWithFormat(STATIC_DATA_STRING(key),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),this->getState());
}

CCString* Role::getSpriteFrameNameWithFormat(std::string key,int frameNumber){
	return CCString::createWithFormat(STATIC_DATA_STRING(key),this->getRoleType(),this->getPEquipment()->getWeapon(),this->getPEquipment()->getBase(),this->getPEquipment()->getPlate(),this->getState(),frameNumber);
}

float Role::getSpeed(){
	return 1.6+1.2*STATIC_DATA_FLOAT("speed/AGI")*AGI*(0.9+0.1*this->getScaleRatio());
}

CCPoint Role::getVelocity(void){
	return CCPointZero;
}

void Role::setScaleAndZOrder(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	body->setScale(0.9 + this->getScaleRatio() * 0.1);

	if(this->getParent()!=NULL){
		this->getParent()->reorderChild(this,100000*this->getScaleRatio());
	}

}

void Role::moveBy(CCPoint velocity){
	//todo 移动也要根据比例来移动
	//this->stopActionByTag(moveBy);
	if(this->getAlive()==false){return;}
	CCPoint pos = body->getPosition();
	this->setScaleAndZOrder();
	pos.x += velocity.x * this->getSpeed();
	pos.y += velocity.y * this->getSpeed();
	this->setPositionScaleAndZOrder(pos);
}

void Role::automaticalBumping(Role* role){
	if(this->getAlive()==false)return;
	if(this->state==state_normal){
		CCPoint roleBodyPosition = role->body->getPosition();
		CCPoint thisBodyPosition = this->body->getPosition();
		if(!roleBodyPosition.equals(thisBodyPosition)){
		CCPoint velocityNormalize =ccpNormalize(ccpSub(roleBodyPosition,thisBodyPosition));
		CCPoint velocity=ccp(1*this->getSpeed()*velocityNormalize.x,1*this->getSpeed()*velocityNormalize.y);
		this->moveBy(velocity);
		}
	}

}


// 坏蛋自动撞向人 
// 撞击方向的精准度
// 撞击的频率
void Role::intelligentBumping(Role* role) {
	// CCRANDOM_0_1() >= 0.8
	if(this->getAlive() == false ) return;
	if(this->state == state_normal) {
		CCPoint roleBodyPosition = role->body->getPosition();
		CCPoint thisBodyPosition = this->body->getPosition();
		// 距离
		float dis = ccpDistance(roleBodyPosition, thisBodyPosition);
		CCPoint velocityNormalize = ccpNormalize(ccpSub(roleBodyPosition,thisBodyPosition));
		CCPoint velocity = ccpMult(velocityNormalize, this->getSpeed());

		// 获得坏蛋的AGI
		// AGI 越大，停的时间越短，快冲概率增大
		// Stay时间 = 1 - float(agi)/100
		// 快冲概率的AGI/100 *2 
		//
		int agi = this->getAGI();
		float delay = 3 * (1 - float(agi) / 100); // 延时时间
		float pp = 0.8 * agi / 100;		// 快冲概率
		// 当距离大于200的时候，以5倍的速度移到人物旁边
		// 当距离在200以内的时候，有一定的概率朝人物方向移动
		//
		if (dis >= 150.0) {
			//this->moveBy(ccpMult(velocity, 5));
			if(this->getRoleActionState() == NONE_ACTION){
				int r = CCRANDOM_0_1() * 10;
				if (r < pp ) {
					this->setRoleActionState(FAST_ACTION);
				}
				else if ( r < pp + 0.3) {
					// stop
					this->setRoleActionState(STOP_ACTION);
					this->scheduleOnce(schedule_selector(Role::setRoleActionStateToRunCallBack), delay);
				}
				else {
					this->setRoleActionState(SLOW_ACTION);
				}

			}
			if(this->getRoleActionState() == STOP_ACTION) {
				float x = CCRANDOM_0_1() - 0.5;
				float y = CCRANDOM_0_1() - 0.5;
				CCPoint v = ccpNormalize(ccp(x, y));
				this->moveBy(ccpMult(v, this->getSpeed()));
			}
			else if(this->getRoleActionState() == SLOW_ACTION) {
				if (CCRANDOM_0_1() > 0.5) {
					CCPoint p = ccp(velocityNormalize.y, -velocityNormalize.y);
					p = ccpMult(ccpNormalize(p), 0.5);
					velocity = ccpAdd(velocityNormalize, p);
				}
				this->moveBy(ccpMult(velocity, 0.5));

			}
			else if(this->getRoleActionState() == FAST_ACTION) {
				this->moveBy(ccpMult(velocity, 2));
			}

			return;
		}
		else {
			// 在200以内，在攻击范围内
			// 概率大于0.8朝人物攻击，其他则随机一个方向
			if(this->getRoleActionState()!=NONE_ACTION){
				this->setRoleActionState(NONE_ACTION);
			}
			if (CCRANDOM_0_1() > 0.2) {
				this->moveBy(velocity);
				/*float x = CCRANDOM_0_1() - 0.5;
				float y = CCRANDOM_0_1() - 0.5;
				CCPoint v = ccpNormalize(ccp(x, y));
				this->moveBy(ccpMult(v, this->getSpeed()));*/
			}
			else {
				float x = CCRANDOM_0_1() - 0.5;
				float y = CCRANDOM_0_1() - 0.5;
				CCPoint v = ccpNormalize(ccp(x, y));
				this->moveBy(ccpMult(v, this->getSpeed()));
			}
		}
	}
}

CCRect Role::getCollisionRectangle(){
	CCRect collisionRect = CCRectMake(this->body->getPositionX()-(0.9+0.1*this->getScaleRatio())*86/2,
		this->body->getPositionY()-(0.9+0.1*this->getScaleRatio())*56,
		(0.9+0.1*this->getScaleRatio())*86,
		(0.9+0.1*this->getScaleRatio())*56);
	return collisionRect;
}

void Role::getBump(Role* role){
	int str = role->getSTR();
	int def = this->getDEF();
	int impactForceCoefficient=(30+str-def);
	if(impactForceCoefficient<5){
		impactForceCoefficient = 5;
	}
	CCPoint velocity = ccpMult(ccpNormalize(ccpSub(this->body->getPosition(),role->body->getPosition())),impactForceCoefficient);
	this->bumpBy(velocity);
	if(this->getState()==state_normal){
		this->setSP(this->getSP()+5);
	}
}

float Role::getScaleRatio(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float rate = 1 - body->getPosition().y/size.height;
//	if(this->getStatus()==Player){
//		rate*=2;
//	}
	return rate;
}

Equipment* Role::getPEquipment(){
	return &this->equipment;
}

void Role::setPEquipment(Equipment* equipment){
	this->equipment = *equipment;
}

bool Role::startUltimateSpin_ForeverTimeAction(){
	this->setState(state_ultimate);
	if(this->getState() == state_ultimate){
		this->body->stopAllActions();
		CCAnimation* ultimateSpinAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(this->getAnimationNameWithFormat("role_spin_animation_format")->getCString());
		CCAnimate* ultimateSpinAnimate = CCAnimate::create(ultimateSpinAnimation);
		ultimateSpinAnimate->setTag(ultimate_spinning);
		body->runAction(CCRepeatForever::create(ultimateSpinAnimate));
		return true;
	}
	else{
		return false;
	}
}

void Role::startUltimateSpin_FiniteTimeAction(){
	this->startUltimateSpin_ForeverTimeAction();
	this->scheduleOnce(schedule_selector(Role::resumeNormalSpinning),STATIC_DATA_FLOAT("ultimate_spin_time"));
}

void Role::stopUltimateSpin_ForeverTimeAction(){
	body->stopActionByTag(ultimate_spinning);
}

void Role::resumeNormalSpinning(float delay){
	this->startNormalSpin_repeatForever();
}

bool Role::startPetrifiedStanding_ForeverTimeAction(){
	this->setState(state_petrified);
	if(this->getState() == state_petrified){
		this->body->stopAllActions();
		CCAnimation* petrifiedStandingAnimation = CCAnimationCache::sharedAnimationCache()->animationByName(this->getAnimationNameWithFormat("role_spin_animation_format")->getCString());
		CCAnimate* petrifiedStandingAnimate = CCAnimate::create(petrifiedStandingAnimation);
		petrifiedStandingAnimate->setTag(petrified_standing);
		body->runAction(CCRepeatForever::create(petrifiedStandingAnimate));
		return true;
	}
	else{
		return false;
	}
}

void Role::stopPetrifiedStanding_ForeverTimeAction(){
	body->stopActionByTag(petrified_standing);
}

void Role::startPetrifiedStanding_FiniteTimeAction(){
	this->startPetrifiedStanding_ForeverTimeAction();
	this->scheduleOnce(schedule_selector(Role::resumeNormalSpinningFromPetrifiedStanding),STATIC_DATA_FLOAT("petrified_standing_time"));
}

void Role::resumeNormalSpinningFromPetrifiedStanding(float delay){
	this->startNormalSpin_repeatForever();
}

void Role::bumpBy( CCPoint& velocity )
{
	if(this->getAlive()==false)return;
	CCPoint pos = body->getPosition();
	this->setScaleAndZOrder();
	pos.x += velocity.x ;
	pos.y += velocity.y ;
	this->setPositionScaleAndZOrder(pos);
}

void Role::killed(){
	if(this->getAlive()==true){
		this->setAlive(false);
		this->getBody()->setVisible(false);
		this->body->stopAllActions();
		this->body->pauseSchedulerAndActions();
		this->stopAllActions();
		this->pauseSchedulerAndActions();

		CCParticleExplosion *explosion = CCParticleExplosion::create();
		explosion->setPosition(this->body->getPositionX(),this->body->getPositionY());
		explosion->setTextureWithRect(CCTextureCache::sharedTextureCache()->addImage("Particle/snow.png"),CCRectMake(0,0,32,32));
		this->addChild(explosion);

	}
}

void Role::setRoleActionStateToRunCallBack(CCObject* psend)
{
	if(CCRANDOM_0_1()>0.5){
		this->setRoleActionState(SLOW_ACTION);
	}
	else{
		this->setRoleActionState(FAST_ACTION);
	}
}
