#pragma once
#include <cocos2d.h>
#include"Equipment.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"
#include "GameScene.h"
#include"ChallengeUserLayer.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class ChallengeScene :
	public cocos2d::CCScene
{
public:
	static ChallengeScene* create();
	bool init();
	void CreatTipLayer();

	CC_SYNTHESIZE(CCArray*,players,Players);
	CC_SYNTHESIZE(CCArray*,challengeUserLayers,ChallengeUserLayers);
	CC_SYNTHESIZE(bool,hasShowTip,HasShowTip);
	CC_SYNTHESIZE(TipsLayer*,tipLayer,TipLayer);

	void removeFromParentCallback(CCObject* pSender);
	static std::string intToString(int n);

protected:
	void drawBackground();//������
	void drawBackHome();//
	void drawWindow();//
	void drawHeadSculpture();//��ͷ��
	void drawUserName();//д����
	void drawLevel();//д�ȼ�
	void drawHonor();//д����ֵ
	void drawUpdatePlayers();//����һ��

	void drawPlayers();

	void getRandomPlayers(int playersNumber,int minLevel,int maxLevel);//��һ��
	void clickHeadSculpture(CCObject* pSender);//���ͷ��
	void clickLevel(CCObject* pSender);//����ȼ�����
	void clickUpdatePlayers(CCObject* pSender);//�����һ������


public:
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	void displayOn();
};

