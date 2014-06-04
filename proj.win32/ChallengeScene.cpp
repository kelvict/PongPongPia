#include "ChallengeScene.h"
#include "StaticData.h"
#include "JsonBox.h"
#include"CurlUtils.h"
#include"PopWindowsLayer.h"
#include"Utils.h"
#include "PersonalInfoLayer.h"

ChallengeScene* ChallengeScene::create()
{
	ChallengeScene* challengeScene = new ChallengeScene();
	challengeScene->init();
	challengeScene->autorelease();
	return challengeScene;
}

bool ChallengeScene::init()
{
	if(!CCScene::init())
	{
		return false;
	}
	players= CCArray::create();
	challengeUserLayers=CCArray::create();

	players->retain();
	challengeUserLayers->retain();
	getRandomPlayers(3,USER->getLevel()-1,USER->getLevel()+1);
	CreatTipLayer();
	this->displayOn();
	return true;
}

void ChallengeScene::CreatTipLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos.x +=287;
	pos.y -=16;

	TipsLayer* tiplayer = TipsLayer::create((TipsType)2,(TipsDirType)1,pos);
	tiplayer->retain();
	this->setTipLayer(tiplayer);
	this->setHasShowTip(false);
}

void ChallengeScene::removeFromParentCallback(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void ChallengeScene::drawBackground()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"challenge_BG"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);	
}

void ChallengeScene::drawBackHome()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("challenge_home"),
		STATIC_DATA_STRING("challenge_home"),
		this,
		menu_selector(ChallengeScene::removeFromParentCallback)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width,winSize.height);
	pos.x = pos.x  /31;
	pos.y = pos.y *19/20;
	menu->setPosition(pos);
	this->addChild(menu);
}

void ChallengeScene::drawWindow()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"challenge_window"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);	
}

void ChallengeScene::drawHeadSculpture()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("challenge_headshot-user"),
		STATIC_DATA_STRING("challenge_headshot-user"),
		this,
		menu_selector(ChallengeScene::clickHeadSculpture)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	pos.x -=340;
	menu->setPosition(pos);
	this->addChild(menu);
}

void ChallengeScene::drawUserName()
{
	//const char *a = ;//需要改为当前用户的名字
	CCLabelTTF* pBg =
		CCLabelTTF::labelWithString(USER->getUsername().getCString(), "Thonburi", 34);
	pBg->setColor(ccc3(0,0,255));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos.x -=115;
	pos.y +=30;

	pBg->setPosition(pos);
	this->addChild(pBg);
}

void ChallengeScene::drawLevel()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("challenge_level-normal"),
		STATIC_DATA_STRING("challenge_level-click"),
		this,
		menu_selector(ChallengeScene::clickLevel)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos.x -=130;
	pos.y -= 30;
	menu->setPosition(pos);
	this->addChild(menu);

	std::string  a ;
	std::string st = (CCString::createWithFormat(STATIC_DATA_STRING("user_level"),USER->getLevel()/5))->m_sString;
	std::cout<<"userlevel:  "<<st<<std::endl;
	a.append(STATIC_DATA_STRING(st));//称号

	a.append(intToString(USER->getLevel()));//这里的3需要改为当前用户的等级
	a.append(")");
	const char *b = a.data();
	CCLabelTTF* pBg =
		CCLabelTTF::labelWithString(b, "Thonburi", 34);

	pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos.x -=135;
	pos.y -=35;

	pBg->setPosition(pos);
	this->addChild(pBg);
}
void ChallengeScene::drawHonor()
{
	CCSprite* pBg1 = CCSprite::create(STATIC_DATA_STRING(
		"challenge_rongyu-user"));

	std::string  a = intToString(USER->getHonor());//这里的27需要改为当前用户的荣誉值
	const char *b = a.data();
	CCLabelTTF* pBg2 =
		CCLabelTTF::labelWithString(b, "Thonburi", 34);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos1 = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos1.x +=75;
	pos1.y -=2;
	CCPoint pos2 = pos1;
	pos2.y -=18;
	pBg1->setPosition(pos1);
	pBg2->setPosition(pos2);
	this->addChild(pBg1);
	this->addChild(pBg2);
}

void ChallengeScene::drawUpdatePlayers()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("challenge_normal-next"),
		STATIC_DATA_STRING("challenge_click-next"),
		this,
		menu_selector(ChallengeScene::clickUpdatePlayers)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width/2,winSize.height*501/600);
	pos.x +=280;

	menu->setPosition(pos);
	this->addChild(menu);
}

void ChallengeScene::drawPlayers()
{
	if(players->count()>=1){
		Role* role1 = (Role*)players->objectAtIndex(0);
		ChallengeUserLayer* challengeUserLayer1 = ChallengeUserLayer::create(role1,
			CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height*31/50));

		challengeUserLayer1->retain();
		this->getChallengeUserLayers()->addObject(challengeUserLayer1);
		challengeUserLayer1->displayOn(this);

	}

	if(players->count()>=2){
		Role* role2 = (Role*)players->objectAtIndex(1);
		ChallengeUserLayer* challengeUserLayer2 = ChallengeUserLayer::create(role2,
			CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height*206/500));

		challengeUserLayer2->retain();
		this->getChallengeUserLayers()->addObject(challengeUserLayer2);
		challengeUserLayer2->displayOn(this);

	}
	if(players->count()>=3){
		Role* role3 = (Role*)players->objectAtIndex(2);
		ChallengeUserLayer* challengeUserLayer3 = ChallengeUserLayer::create(role3,
			CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height/5));

		challengeUserLayer3->retain();
		this->getChallengeUserLayers()->addObject(challengeUserLayer3);

		challengeUserLayer3->displayOn(this);
	}
}

void ChallengeScene::getRandomPlayers(int playersNumber,int minLevel,int maxLevel)
{
	players->removeAllObjects();
	map<string,string> post;
	post["api"] = "get_random_player";
	post["username"]=USER->getUsername().getCString();
	post["password"]=USER->getPassword().getCString();
	post["players_number"]=Utils::int2str(playersNumber);
	post["max_level"]=Utils::int2str(maxLevel);
	post["min_level"]=Utils::int2str(minLevel);

	std::string jsonStr = POST(post);
	JsonBox::Value data;
	CCLOG(jsonStr.c_str());
	data.loadFromString(jsonStr);

	if(data["result"].getString()=="OK"){
		int num = data["row_number"].getInt();
		for(int i=0;i<num;i++){
			RoleType roleType = (RoleType) atoi(data[Utils::int2str(i)]["role_type"].getString().c_str());
			Weapon weapon = (Weapon) atoi(data[Utils::int2str(i)]["current_weapon"].getString().c_str());
			Base base = (Base) atoi(data[Utils::int2str(i)]["current_base"].getString().c_str());
			Plate plate = (Plate) atoi(data[Utils::int2str(i)]["current_plate"].getString().c_str());
			Role* role = Role::create(roleType,Enemy,Equipment::create((Weapon)weapon,(Base)base,(Plate)plate));
			role->setUsername(data[Utils::int2str(i)]["username"].getString().c_str());
			role->setLevel(atoi(data[Utils::int2str(i)]["level"].getString().c_str()));
			role->setHonor(atoi(data[Utils::int2str(i)]["honor"].getString().c_str()));
			role->setAGI(atoi(data[Utils::int2str(i)]["basic_agi"].getString().c_str()));
			role->setDEF(atoi(data[Utils::int2str(i)]["basic_def"].getString().c_str()));
			role->setSTR(atoi(data[Utils::int2str(i)]["basic_str"].getString().c_str()));

			role->retain();
			players->addObject(role);
		}
	}



}

void ChallengeScene::clickHeadSculpture(CCObject* pSender)
{
	PersonalInfoLayer * personalInfo = PersonalInfoLayer::create(view_data);
	personalInfo->displayOn(this);

	TipsLayer* thisTip = this->getTipLayer();
	if(this->getHasShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setHasShowTip(false);
	}
}

void ChallengeScene::clickLevel(CCObject* pSender)
{
	TipsLayer* thisTip = this->getTipLayer();
	if(this->getHasShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setHasShowTip(false);
	}
	else
	{
		thisTip->displayOn(this);
		this->setHasShowTip(true);
	}

}

void ChallengeScene::clickUpdatePlayers(CCObject* pSender)
{
	TipsLayer* thisTip = this->getTipLayer();
	if(this->getHasShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setHasShowTip(false);
	}
	getRandomPlayers(3,USER->getLevel()-1,USER->getLevel()+1);
	this->drawPlayers();
}

void ChallengeScene::operateAllSchedulerAndActions(cocos2d::CCNode* node,
	OperateFlag flag)
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

void ChallengeScene::removeFromParentAndCleanup(){
	CCTransitionShrinkGrow* transitionToMenuScene = CCTransitionShrinkGrow::create(0.30f,StartLayer::scene());	
	CCDirector::sharedDirector()->replaceScene(transitionToMenuScene);
}

void ChallengeScene::displayOn()
{
	this->drawBackground();
	this->drawBackHome();
	this->drawWindow();
	this->drawHeadSculpture();
	this->drawUserName();
	this->drawLevel();
	this->drawHonor();
	this->drawUpdatePlayers();
	this->drawPlayers();
}
std::string ChallengeScene::intToString(int n)
{
	return Utils::int2str(n); 
}