#include "ChallengeUserLayer.h"
#include "StaticData.h"
#include "PersonalInfoLayer.h"

ChallengeUserLayer* ChallengeUserLayer::create(Role* role,CCPoint position)
{
	ChallengeUserLayer* challengeUserLayer = new ChallengeUserLayer();
	challengeUserLayer->init(role,position);
	challengeUserLayer->autorelease();
	return challengeUserLayer;
}

bool ChallengeUserLayer::init(Role* role,CCPoint position)
{
	if(!role)
		return false;
	role->retain();
	this->setRole(role);
	this->setUsername(role->getUsername());
	this->setLevel(role->getLevel());
	this->setHonor(role->getHonor());
	this->setThisPosition(position);
	this->setShowTip(false);
	this->CreatTipLayer();


//	intToString(honor);
	//

	//
//	std::cout<<"x: "<<position.x<<"    y: "<<position.y<<std::endl;
	//
	return true;
}

void ChallengeUserLayer::CreatTipLayer()
{

	CCPoint pos = this->getThisPosition();

	pos.x +=287;
	pos.y -=16;

	TipsLayer* tiplayer = TipsLayer::create((TipsType)2,(TipsDirType)1,pos);
	tiplayer->retain();
	this->setTipLayer(tiplayer);
}

void ChallengeUserLayer::removeFromParentCallback(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void ChallengeUserLayer::drawBackground()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("challenge_select"),
			STATIC_DATA_STRING("challenge_select"),
			this,
			menu_selector(ChallengeUserLayer::ClickBackground)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	menu->setPosition(this->getThisPosition());
	this->addChild(menu);
}

void ChallengeUserLayer::DrawHeadSculpture()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("challenge_headshot-player1"),
			STATIC_DATA_STRING("challenge_headshot-player1"),
			this,
			menu_selector(ChallengeUserLayer::ClickHeadSculpture)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCPoint pos = this->getThisPosition();
	pos.x -=340;
	menu->setPosition(pos);
	this->addChild(menu);
}

void ChallengeUserLayer::DrawUserName()
{
	/*
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"challenge_name-player1"));
	*/
	const char *a = username.getCString();
	CCLabelTTF* pBg =
		CCLabelTTF::labelWithString(a, "Thonburi", 34);
	pBg->setColor(ccc3(0,0,255));
	CCPoint pos = this->getThisPosition();
	pos.x -=115;
	pos.y +=30;

	pBg->setPosition(pos);
	this->addChild(pBg);
}

void ChallengeUserLayer::DrawLevel()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
		STATIC_DATA_STRING("challenge_level-normal"),
		STATIC_DATA_STRING("challenge_level-click"),
		this,
		menu_selector(ChallengeUserLayer::ClickLevel)
		);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCPoint pos = this->getThisPosition();
	pos.x -=130;
	pos.y -= 30;
	menu->setPosition(pos);
	this->addChild(menu);

	std::string  a ;
	std::string st = (CCString::createWithFormat(STATIC_DATA_STRING("user_level"),level/5))->m_sString;
	a.append(STATIC_DATA_STRING(st));



	a.append(intToString(level));
	a.append(")");
	const char *b = a.data();
	CCLabelTTF* pBg =
		CCLabelTTF::labelWithString(b, "Thonburi", 34);


	pos = this->getThisPosition();
	pos.x -=135;
	pos.y -=35;

	pBg->setPosition(pos);
	this->addChild(pBg);
}

void ChallengeUserLayer::DrawHonor()
{
	CCSprite* pBg1 = CCSprite::create(STATIC_DATA_STRING(
		"challenge_rongyu-user"));

	std::string  a = intToString(honor);
	//a.append(intToString(honor));
//	std::cout<<"a "<<a<<std::endl;
	const char *b = a.data();
	CCLabelTTF* pBg2 =
	CCLabelTTF::labelWithString(b, "Thonburi", 34);

	CCPoint pos1 = this->getThisPosition();
	pos1.x +=75;
	pos1.y -=2;
	CCPoint pos2 = pos1;
	pos2.y -=18;
	pBg1->setPosition(pos1);
	pBg2->setPosition(pos2);
	this->addChild(pBg1);
	this->addChild(pBg2);
}

void ChallengeUserLayer::DrawPK()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("challenge_normal-PK"),
			STATIC_DATA_STRING("challenge_click-PK"),
			this,
			menu_selector(ChallengeUserLayer::ClickPK)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCPoint pos = this->getThisPosition();
	pos.x +=280;

	menu->setPosition(pos);
	this->addChild(menu);
}

void ChallengeUserLayer::ClickBackground(CCObject* pSender)
{
	TipsLayer* thisTip = this->getTipLayer();
	if(this->getShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setShowTip(false);
	}

}

void ChallengeUserLayer::ClickHeadSculpture(CCObject* pSender)
{
	PersonalInfoLayer * personalInfo = PersonalInfoLayer::createOtherInfor(role);
	personalInfo->displayOn(this->getParent());

	//this->getParent()->removeChildByTag(20,true);

	TipsLayer* thisTip = this->getTipLayer();
	if(this->getShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setShowTip(false);
	}
}

void ChallengeUserLayer::ClickLevel(CCObject* pSender)
{
	//this->getTipLayer()->displayOn(this);
	
	TipsLayer* thisTip = this->getTipLayer();
	if(this->getShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setShowTip(false);
	}
	else
	{
		thisTip->displayOn(this);
		this->setShowTip(true);
	}
	
}

void ChallengeUserLayer::ClickPK(CCObject* pSender)
{
	TipsLayer* thisTip = this->getTipLayer();
	if(this->getShowTip())
	{
		thisTip->removeFromParentAndCleanup();
		this->setShowTip(false);
	}
	Equipment temp = USER->getEquipment();
	Equipment* equip = &temp;
	equip->retain();
	Role* player = Role::create(USER->getRoleType(),Player, equip);
	player->setAGI(USER->getAGI());
	player->setDEF(USER->getDEF());
	player->setSTR(USER->getSTR());
	player->retain();

	CCArray* otherRoles = CCArray::create();
	otherRoles->addObject(this->getRole());
	otherRoles->retain();
	
	CCArray* rewards = CCArray::create();
	rewards->retain();

	GameScene* gamescene = GameScene::create(player,otherRoles,rewards,Challenge_Background,k_Chanllenge_Game);
	CCTransitionShrinkGrow* transitionToGameScene= CCTransitionShrinkGrow::create(0.30f,gamescene);
	CCDirector::sharedDirector()->replaceScene(transitionToGameScene);		
}

void ChallengeUserLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void ChallengeUserLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
	//this->removeFromParentAndCleanup();
}

void ChallengeUserLayer::displayOn(cocos2d::CCNode* node)
{
	this->drawBackground();
	this->DrawHeadSculpture();
	this->DrawUserName();
	this->DrawLevel();
	this->DrawHonor();
	this->DrawPK();

	this->setTag(20);
	node->addChild(this);
}

std::string ChallengeUserLayer::intToString(int n)
{
	
	char a;
	std::string result ;
	int i;
	while(n>9)
	{
//		std::cout<<"n "<<n<<std::endl;
		for(i=1;i<=n;i*=10)
		{}
		i/=10;
//		std::cout<<"i "<<i<<std::endl;
		a =(char)(n/i+48);
		n= n%i;
//		std::cout<<"n "<<n<<std::endl;
		result.append(&a,1);
//		std::cout<<"a "<<a<<std::endl;

//		std::cin>>a;
	}
	a =(char)(n+48);
//	std::cout<<"a "<<a<<std::endl;
	result.append(&a,1);
//	std::cout<<"honor "<<result<<std::endl;
	return result;
}