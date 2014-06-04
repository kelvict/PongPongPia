#include "GameScene.h"
#include "StaticData.h"
#include "PongPongPiaData.h"
#include "PersonalAudioEngine.h"
#include "StartScene.h"
#include "HRocker.h"
#include "AccelerationLayer.h"
#include "UserData.h"
#include "Reward.h"
#include "WinLayer.h"
#include "LoseLayer.h"
using namespace cocos2d;

int GameScene::curChapterNum = 1;
int GameScene::curRoundNum = 1;


GameScene* GameScene::createWithGameNumber(int chapterNumber,int roundNumber){
	GameScene* scene = new GameScene();
	scene->initWithGameNumber(chapterNumber,roundNumber);
	scene->autorelease();
	return scene;
}

bool GameScene::initWithGameNumber(int chapterNumber,int roundNumber){
	this->curChapterNum = chapterNumber;
	this->curRoundNum = roundNumber;
	CCDictionary* roundDict = this->getRoundDictionay(chapterNumber,roundNumber);
	CCDictionary* chapterDict = this->getChapterDictionary(chapterNumber);
	
	GameBackgroundType type = (GameBackgroundType)chapterDict->valueForKey("game_background_type")->intValue();
	std::string test= chapterDict->valueForKey("game_background_type")->getCString();
	Equipment temp = USER->getEquipment();
	Role* player = Role::create(USER->getRoleType(),Player,&temp);	
	CCArray* otherRoles=CCArray::create();
	CCArray* rewards=CCArray::create();
	player->setSTR(USER->getSTR());
	player->setDEF(USER->getDEF());
	player->setAGI(USER->getAGI());
	player->retain();
	otherRoles->retain();
	rewards->retain();


	for(int i=0;i<roundDict->valueForKey("number_of_computers")->intValue();i++){
		CCDictionary* computerDict = this->getComputerDict(chapterNumber,roundNumber,i);
		Role* computer = Role::create((RoleType)computerDict->valueForKey("role")->intValue(),(Status)computerDict->valueForKey("status")->intValue(),Equipment::create((Weapon)computerDict->valueForKey("weapon")->intValue(),(Base)computerDict->valueForKey("base")->intValue(),(Plate)computerDict->valueForKey("plate")->intValue()));
		otherRoles->addObject(computer);
	}
	for(int i=0;i<roundDict->valueForKey("number_of_computers")->intValue();i++){
		CCDictionary* rewardDict = this->getRewardDict(chapterNumber,roundNumber,i);
		Reward* reward = Reward::create((RewardType)rewardDict->valueForKey("reward_type")->intValue(),rewardDict->valueForKey("item_type")->intValue(),rewardDict->valueForKey("quantity")->intValue());
		rewards->addObject(reward);
	}
	this->init(player,otherRoles,rewards,type);
	return true;
}

CCDictionary* GameScene::getGamesceneDictionary(){
	CCDictionary* staticData = StaticData::sharedStaticData()->getStaticDataDictionary();
	CCDictionary* gamesceneDict =dynamic_cast<CCDictionary*>( staticData->objectForKey("gamescene"));
	gamesceneDict->retain();
	return gamesceneDict;
}

CCDictionary* GameScene::getChapterDictionary(int chapterNumber){
	CCDictionary* chapterDict = dynamic_cast<CCDictionary*>(this->getGamesceneDictionary()->objectForKey(CCString::createWithFormat("chapter_%d",chapterNumber)->getCString()));
	chapterDict->retain();
	return chapterDict;
}

CCDictionary* GameScene::getRoundDictionay(int chapterNum,int roundNum){
	CCDictionary* chapterDict = this->getChapterDictionary(chapterNum);
	CCDictionary* roundDict   = dynamic_cast<CCDictionary*>(chapterDict->objectForKey(CCString::createWithFormat("round_%d",roundNum)->getCString()));
	roundDict->retain();
	return roundDict;
}

CCDictionary* GameScene::getPlayerDictionay(int chapterNum,int roundNum){
	CCDictionary* roundDict = this->getRoundDictionay(chapterNum,roundNum);
	CCDictionary* playerDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey("player"));
	playerDict->retain();
	return playerDict;
}

CCDictionary* GameScene::getComputerDict(int chapterNum,int roundNum,int computerNum){
	CCDictionary* roundDict = this->getRoundDictionay(chapterNum,roundNum);
	CCDictionary* computerDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey(CCString::createWithFormat("computer_%d",computerNum)->getCString()));
	computerDict->retain();
	return computerDict;
}

CCDictionary* GameScene::getRewardDict(int chapterNum,int roundNum,int rewardNum){
	CCDictionary* roundDict = this->getRoundDictionay(chapterNum,roundNum);
	CCDictionary* rewardDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey(CCString::createWithFormat("reward_%d",rewardNum)->getCString()));
	rewardDict->retain();
	return rewardDict;
}

GameScene* GameScene::create(Role* player,CCArray* otherRoles,CCArray* rewards,GameBackgroundType type,GameType gameType){
	GameScene* scene = new GameScene();
	scene->init(player,otherRoles,rewards,type,gameType);
	scene->autorelease();
	return scene;
}

bool GameScene::init(Role* player,CCArray* otherRoles,CCArray* rewards,GameBackgroundType backgroundType,GameType gameType){
	this->init(backgroundType);
	this->player=player;
	this->otherRoles=otherRoles;
	this->otherRoles->retain();
	this->rewards = rewards;
	this->rewards->retain();
	this->setGameType( gameType);
	this->setBackgroundType(backgroundType);
	return true;
}

void GameScene::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();

	this->startAnimation();

	this->scheduleOnce(schedule_selector(GameScene::startCallback),2);
}

void GameScene::startAnimation(){
	CCSize winSize  = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(winSize.width/2,winSize.height/2);
	float timeScaler = 0.5;
	CCFiniteTimeAction* rotateAndFadeIn = CCSpawn::actions(CCFadeIn::actionWithDuration(0.75*timeScaler),NULL);
	CCFiniteTimeAction* rotateAndFadeOut = CCSpawn::actions(CCFadeOut::actionWithDuration(0.25*timeScaler),NULL);
	CCAction* inAndOutAction = CCSequence::actions(rotateAndFadeIn,rotateAndFadeOut,NULL);
	CCSprite* sprite =CCSprite::create("123Go/1.png");
	sprite->setPosition(center);
	this->addChild(sprite,0,TAG_SPRITE_1);
	sprite->runAction(inAndOutAction);

	CCSprite* sprite2 = CCSprite::create("123Go/2.png");
	CCAction* inAndOutAction2 = CCSequence::actions(CCHide::create(),CCDelayTime::actionWithDuration(1*timeScaler),CCShow::create(),inAndOutAction,NULL);
	sprite2->setPosition(center);
	this->addChild(sprite2,0,TAG_SPRITE_2);
	sprite2->runAction(inAndOutAction2);

	CCSprite* sprite3 = CCSprite::create("123Go/3.png");
	CCAction* inAndOutAction3 = CCSequence::actions(CCHide::create(),CCDelayTime::actionWithDuration(2*timeScaler),CCShow::create(),inAndOutAction,NULL);
	sprite3->setPosition(center);
	this->addChild(sprite3,0,TAG_SPRITE_3);
	sprite3->runAction(inAndOutAction3);

	CCSprite* spriteCircle = CCSprite::create("123Go/spin.png");
	CCAction* spinAndHide = CCSequence::actions(CCRotateBy::actionWithDuration(3*timeScaler,3*360),CCHide::create(),NULL);
	spriteCircle->setPosition(center);
	this->addChild(spriteCircle,0,TAG_SPRITE_CIRCLE);
	spriteCircle->runAction(spinAndHide);

	CCSprite* spriteGo = CCSprite::create("123Go/go.png");
	CCFiniteTimeAction* scaleAndFadeOut = CCSpawn::actions(CCScaleBy::actionWithDuration(1*timeScaler,5),CCFadeOut::actionWithDuration(1*timeScaler),NULL);
	CCAction* goAction  = CCSequence::actions(CCHide::create(),CCDelayTime::actionWithDuration(3*timeScaler),CCShow::create(),scaleAndFadeOut,NULL);
	spriteGo->setPosition(center);
	this->addChild(spriteGo,0,TAG_SPRITE_GO);
	spriteGo->runAction(goAction);

}

void GameScene::resumeCallback(float delay){
	this->operateAllSchedulerAndActions(this,k_Operate_Resume);
	CCLOG("resume!");
}

void GameScene::pauseCallback(float delay){
	this->operateAllSchedulerAndActions(this,k_Operate_Pause);
	CCLOG("pause!");
}

void GameScene::startCallback(float delay){

	this->removeChildByTag(TAG_SPRITE_1,true);
	this->removeChildByTag(TAG_SPRITE_2,true);
	this->removeChildByTag(TAG_SPRITE_3,true);
	this->removeChildByTag(TAG_SPRITE_CIRCLE,true);
	this->removeChildByTag(TAG_SPRITE_GO,true);

	this->createJoystick();

	do {
		accelerationLayer = AccelerationLayer::create();
		CC_SAFE_RETAIN(accelerationLayer);
		this->addChild(accelerationLayer);

		_menuLayer = MenuLayer::create();
		CC_SAFE_RETAIN(_menuLayer);

		_panelLayer = PanelLayer::create();
		this->addChild(_panelLayer);

		_roleLayer = RoleLayer::create();
		CC_BREAK_IF(!_roleLayer);
		this->addChild(_roleLayer);
		_roleLayer->setPlayer(this->player);
		//	_roleLayer->setComputer(this->computer);
		CCObject* iter;
		CCARRAY_FOREACH(this->otherRoles,iter){
			Role* role = (Role*)iter;
			_roleLayer->addOtherRole(role);
		}
		this->addBarriersLayer();
		this->start();


		_menuLayer->setSoundAndMusicVolume(PongPongPiaData::sharedPongPongPiaData()->getSoundVolume(), PongPongPiaData::sharedPongPongPiaData()->getMusicVolume());
		PersonalAudioEngine::sharedEngine()->playBackgroundMusic(STATIC_DATA_STRING("gamescene_background_music"),true);
	} while (0);
	this->scheduleUpdate();
}

void GameScene::prestartCallback(float delay){
	this->operateAllSchedulerAndActions(this,k_Operate_Pause);
}


bool GameScene::init(GameBackgroundType type)
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(! CCScene::init());

		_backgroundLayer = BackgroundLayer::create(type);
		CC_BREAK_IF(! _backgroundLayer);
		this->addChild(_backgroundLayer);
		fullOfEnergy=false;
		return true;
	} while(0);

	return bRet;
}

void GameScene::start(){


	//_roleLayer->addOtherRole(Role::create(BiaBo,Player,Equipment::create(weapon_none,base_none,plate_none),left));
	_roleLayer->startAllNormalSpin_repeatForever();
};

void GameScene::pause()
{
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	//this->operateAllSchedulerAndActions(this->_roleLayer,k_Operate_Pause);
	//_touchLayer->setTouchEnabled(false);
	this->addChild(_menuLayer);
	this->joystick->Inactive();
	//this->setActionSet(*CCDirector::sharedDirector()->getActionManager()->pauseAllRunningActions());

	//this->operateAllSchedulerAndActions(this->_roleLayer,k_Operate_Pause);
}

void GameScene::resume()
{
	this->operateAllSchedulerAndActions(this, k_Operate_Resume);
	//this->operateAllSchedulerAndActions(this->_roleLayer,k_Operate_Resume);
	PersonalAudioEngine::sharedEngine()->resumeBackgroundMusic();
	this->removeChild(_menuLayer, false);
	//_touchLayer->setTouchEnabled(true);
	this->joystick->Active();
	_panelLayer->getChildByTag(MENUTAG)->setVisible(true);

	//CCDirector::sharedDirector()->getActionManager()->resumeTargets(this->getPActionSet());
	//this->operateAllSchedulerAndActions(this->_roleLayer,k_Operate_Resume);
}


void GameScene::operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag)
{
	if(node->isRunning()){
		switch (flag) {
		case k_Operate_Pause:
			node->pauseSchedulerAndActions();
			break;
		case k_Operate_Resume:
			node->resumeSchedulerAndActions();
			break;
		default:
			break;
		}
		CCArray* array = node->getChildren();
		if(array != NULL && array->count()>0){
			CCLOG("Hello");
			CCObject* iterator;
			CCARRAY_FOREACH(array, iterator){
				CCNode* child = (CCNode*)iterator;
				this->operateAllSchedulerAndActions(child, flag);
			}
		}
	}
}

void GameScene::sound()
{
	bool flag = PongPongPiaData::sharedPongPongPiaData()->getSoundVolume()>0;
	PersonalAudioEngine::sharedEngine()->setEffectsVolume(!flag);
}
void GameScene::music()
{
	bool flag = PongPongPiaData::sharedPongPongPiaData()->getMusicVolume()>0;
	PersonalAudioEngine::sharedEngine()->setBackgroundMusicVolume(!flag);
}
void GameScene::reset()
{

}
void GameScene::transToMainMenu()
{
	CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
	CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
	//CCDirector::sharedDirector()->replaceScene(StartLayer::scene());
}

void GameScene::update(float delta)
{
	_roleLayer->update(delta);
	CCPoint scaledV = ccpMult(joystick->getDirection(), -1); 
	//
	if(true == USER->getIsAcceleratorOn())
	{
	    CCPoint* dir = accelerationLayer->GetDirection();
		scaledV = ccpMult(*dir,1.5);
	}
	//
	this->movePlay(scaledV);
}

void GameScene::movePlay( cocos2d::CCPoint destination )
{
	_roleLayer->movePlayer(destination);
}

void GameScene::showResult(bool hasWon){

	if(hasWon==true){
		this->scheduleOnce(schedule_selector(GameScene::showWinResultCallback),0.1);
	}
	else{
		this->scheduleOnce(schedule_selector(GameScene::showLoseResultCallback),0.1);
	}
	//PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("failed_music"),true);
}

void GameScene::showWinResultCallback(float delay){
	//PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	//ResultLayer* _resultLayer = ResultLayer::create(hasWon);
	WinLayer* layer = WinLayer::create();
	this->addChild(layer);
}
void GameScene::showLoseResultCallback(float delay){
	//PersonalAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	PersonalAudioEngine::sharedEngine()->pauseBackgroundMusic();
	//PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("sound_button"));
	this->operateAllSchedulerAndActions(this, k_Operate_Pause);
	//ResultLayer* _resultLayer = ResultLayer::create(hasWon);
	LoseLayer* layer = LoseLayer::create();
	this->addChild(layer);
}
void GameScene::placeProp(Prop* prop)
{
	this->_panelLayer->placeProp(prop);

}
void GameScene::increaceEnetgy()
{
	this->_panelLayer->increaceEnetgy();
}

void GameScene::fullEnergy()
{
	fullOfEnergy = true;
	this->_panelLayer->fullEnergy();
}
GameScene::~GameScene()
{
//	CC_SAFE_RELEASE(_menuLayer);
}

void GameScene::createJoystick()
{
	CCSprite *spRocker = CCSprite::create(STATIC_DATA_STRING("control_point"));//摇杆
	spRocker->setScale(0.5);
	spRocker->setColor(ccc3(100, 100, 100));
	CCSprite *spRockerBG = CCSprite::create(STATIC_DATA_STRING("control_base"));//摇杆背景
	joystick = HRocker::HRockerWithCenter(ccp(0.0f, 0.0f), 50.0f, spRocker, spRockerBG, true);//创建摇杆
	this->addChild(joystick);//摇杆添加到layer中

	if (USER->getIsControlStickOn() == false) {
		joystick->Inactive();
	}
}

RoleLayer* GameScene::getRoleLayer()
{
	return this->_roleLayer;
}

void GameScene::saveRewardsToUserData(){
	CCObject* iter;
	CCARRAY_FOREACH(rewards,iter){
		Reward* reward = (Reward*)iter;
		reward->saveRewardToUserData();
	}
	USER->flush();
}

void GameScene::addBarriersLayer()
{
	if(this->getGameType()==k_Chanllenge_Game){//////////////////////////////////123456
		return;
	}
	CCDictionary* roundDict = this->getRoundDictionay(curChapterNum,curRoundNum);
	CCDictionary* barriersDict = dynamic_cast<CCDictionary*>(roundDict->objectForKey("barriers"));

	if (barriersDict == NULL)
		return;

	CCDictElement* pElement; 
	CCDICT_FOREACH(barriersDict, pElement)
	{
		const char*key = pElement->getStrKey();
		CCDictionary* barrierEach = dynamic_cast<CCDictionary*>(pElement->getObject());

		if (strcmp(key, "wind") == 0) {
			// ·çµÄ·½Ïò
			const CCString* str = barrierEach->valueForKey("direction");
			int direction = str->intValue();
			// ·çµÄÎ»ÖÃ
			const CCString* posStr = barrierEach->valueForKey("position");
			float posX,posY;
			sscanf(posStr->getCString(), "(%f,%f)", &posX, &posY);
			// ·çËÙ
			const CCString* speedStr = barrierEach->valueForKey("speed");
			float speedX, speedY;
			sscanf(speedStr->getCString(), "(%f,%f)", &speedX, &speedY);

			Wind* wind = Wind::create(ccp(posX,posY), ccp(speedX, speedY), WindDirection(direction));

			_roleLayer->setWind(wind);

		} else if (strcmp(key, "swamp") == 0) {
			// ÕÓÔóµÄÀàÐÍ,ÔÝÊ±Î´ÓÃ
			const CCString* str = barrierEach->valueForKey("direction");
			int type = str->intValue();
			// ÕÓÔóµÄÎ»ÖÃ
			const CCString* posStr = barrierEach->valueForKey("position");
			float posX, posY;
			sscanf(posStr->getCString(), "(%f,%f)", &posX, &posY);
			// ÕÓÔó¼õËÙÐ§¹û
			const CCString* speedStr = barrierEach->valueForKey("slowdown_speed");
			float slowDown = speedStr->floatValue();

			Swamp* swamp = Swamp::create(ccp(posX, posY), slowDown);

			_roleLayer->setSwamp(swamp);
		}
		// ÆäËûÕÏ°­Îï
	}
}