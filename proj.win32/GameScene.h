//
//  GameScene.h
//  PongPongPia
//
//  Created by HuFan on 13-9-12.
//
//
#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

//#include "TouchLayer.h"
#include "MenuLayer.h"
#include "PanelLayer.h"
#include "BackgroundLayer.h"
#include "RoleLayer.h"
#include "ResultLayer.h"
#include "AccelerationLayer.h"
#include "HRocker.h"
#include "Swamp.h"
#include "Wind.h"

#define TAG_SPRITE_1 9991
#define TAG_SPRITE_2 9992
#define TAG_SPRITE_3 9993
#define TAG_SPRITE_GO 9994
#define TAG_SPRITE_CIRCLE 9995



typedef enum{
	k_Operate_Pause = 0,
	k_Operate_Resume
}OperateFlag;

typedef enum{
	k_Normal_Game=0,
	k_Chanllenge_Game
}GameType;

class GameScene : public cocos2d::CCScene
{
public:
	CREATE_FUNC(GameScene);
	static GameScene* create(Role* player,CCArray* otherRoles,CCArray* rewards=CCArray::create(),GameBackgroundType type = GameBackgroundType(0),GameType gameType = k_Normal_Game);
	static GameScene* createWithGameNumber(int chapterNumber,int roundNumber);
	virtual bool init(GameBackgroundType type=GameBackgroundType(0));
	bool init(Role* player,CCArray* otherRoles,CCArray* rewards,GameBackgroundType type = GameBackgroundType(0),GameType gameType = k_Normal_Game);
	void onEnterTransitionDidFinish();
	~GameScene();

	static int curChapterNum;
	static int curRoundNum;
	//菜单有关
	void start();
	void pause();
	void resume();
	void sound();
	void music();
	void reset();
	void transToMainMenu();

	CC_SYNTHESIZE(CCSet,actionSet,ActionSet);
	CC_SYNTHESIZE(bool, fullOfEnergy, isFullOfEnergy);
	//CCSet* getPActionSet();
	//void setPActionSet(CCSet* pActionSet);
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	//游戏逻辑有关
	void movePlay(cocos2d::CCPoint destination);
	void showResult(bool hasWon);
	void placeProp(Prop* prop);
	void increaceEnetgy();
	void fullEnergy();
	RoleLayer* getRoleLayer();
	void addBarriersLayer();
public:
	CC_SYNTHESIZE(CCArray*,rewards,Rewards);

protected:
	BackgroundLayer* _backgroundLayer;
	MenuLayer* _menuLayer;
	PanelLayer* _panelLayer;
	RoleLayer* _roleLayer;
	WinLayer* _resultLayer;
	AccelerationLayer* accelerationLayer;

	HRocker* joystick;

	CC_SYNTHESIZE(bool, isTouched, IsTouched);
	CC_SYNTHESIZE(Role*,player,Player);
	CC_SYNTHESIZE(Role*,computer,Computer);
	CC_SYNTHESIZE(CCArray*,otherRoles,OtherRoles);

	CC_SYNTHESIZE(GameType, gameType,GameType);
	CC_SYNTHESIZE(GameBackgroundType,backgroundType,BackgroundType);

	void update(float delta);
	void createJoystick();
	void saveRewardsToUserData();

	bool initWithGameNumber(int chapterNumber,int roundNumber);
	CCDictionary* getGamesceneDictionary();
	CCDictionary* getChapterDictionary(int chapterNumber);
	CCDictionary* getRoundDictionay(int chapterNum,int roundNum);
	CCDictionary* getPlayerDictionay(int chapterNum,int roundNum);
	CCDictionary* getComputerDict(int chapterNum,int roundNum,int computerNum);
	CCDictionary* getRewardDict(int chapterNum,int roundNum,int rewardNum);
	void resumeCallback(float delay);
	void showWinResultCallback(float delay);
	void showLoseResultCallback(float delay);
	void startCallback(float delay);
	void pauseCallback(float delay);
	void prestartCallback(float delay);
	void startAnimation();
};
