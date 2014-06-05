#include "RegisterLayer.h"
#include "StaticData.h"
#include "Utils.h"
#include "PopWindowsLayer.h"
#include "CurlUtils.h"
#include "JsonBox.h"
#include "Language.h"
RegisterLayer* RegisterLayer::create()
{
	RegisterLayer* registerLayer = new RegisterLayer();
	registerLayer->init();
	registerLayer->autorelease();
	return registerLayer;
}

bool RegisterLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	showUsernameErrorTip = false;
	this->CreatTipLayer();
	this->creatUsernameText();
	this->creatPasswordText();

	return true;
}

void RegisterLayer::CreatTipLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*184/300,winSize.height*27/50);

	TipsLayer* tiplayer = TipsLayer::create((TipsType)2,(TipsDirType)1,pos);
	tiplayer->retain();

	tipUsernameErrorLayer = tiplayer;
	showUsernameErrorTip = false;
}

void RegisterLayer::creatUsernameText()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*250/500,winSize.height*35/50);

	CCTextFieldTTF* text = CCTextFieldTTF::textFieldWithPlaceHolder(
		"Input Your Name...","Arial",20);
	text->setColor(ccc3(INPUT_R,INPUT_G,INPUT_B));
	text->setPosition(pos);
	this->addChild(text,20);
	text->setDelegate(this);

	text->retain();
	usernameText = text;
	
}

void RegisterLayer::creatPasswordText()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*250/500,winSize.height*22/50);

	CCTextFieldTTF* text = CCTextFieldTTF::textFieldWithPlaceHolder(
		"Input Your Password...","Arial",20);
	text->setColor(ccc3(INPUT_R,INPUT_G,INPUT_B));
	text->setPosition(pos);
	this->addChild(text,20);
	text->setDelegate(this);
	text->retain();
	passwordText = text;
}

void RegisterLayer::removeFromParentCallback(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void RegisterLayer::drawBackground()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Register_window"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);	
}

void RegisterLayer::drawUsernameLeft()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Register_account"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width*9/30,winSize.height*35/50));
	this->addChild(pBg);	
}

void RegisterLayer::drawUsernameRight()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Register_inputbox-normal"),
			STATIC_DATA_STRING("Log_Register_Register_inputbox-click"),
			this,
			menu_selector(RegisterLayer::usernameTextFieldPressed)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*18/30,winSize.height*35/50);

	menu->setPosition(pos);
	this->addChild(menu);
}

void RegisterLayer::drawUsername()
{
	this->drawUsernameLeft();
	this->drawUsernameRight();
}

void RegisterLayer::drawPasswordLeft()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Register_password"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width*9/30,winSize.height*22/50));
	this->addChild(pBg);	
}

void RegisterLayer::drawPasswordRight()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Register_inputbox-normal"),
			STATIC_DATA_STRING("Log_Register_Register_inputbox-click"),
			this,
			menu_selector(RegisterLayer::passwordTextFieldPressed)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*18/30,winSize.height*22/50);

	menu->setPosition(pos);
	this->addChild(menu);	
}

void RegisterLayer::drawPassword()
{
	this->drawPasswordLeft();
	this->drawPasswordRight();
}

void RegisterLayer::drawBack()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Register_normal-back"),
			STATIC_DATA_STRING("Log_Register_Register_click-back"),
			this,
			menu_selector(RegisterLayer::clickBack)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*104/300,winSize.height*11/50);

	menu->setPosition(pos);
	this->addChild(menu);
}

void RegisterLayer::drawRegister()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Register_normal-signup"),
			STATIC_DATA_STRING("Log_Register_Register_click-signup"),
			this,
			menu_selector(RegisterLayer::clickRegister)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*196/300,winSize.height*11/50);

	menu->setPosition(pos);
	this->addChild(menu);
}

void RegisterLayer::clickUsernameRight(CCObject* pSender)
{
	/*
	if(usernameVerification())
		return ;
	if(!showUsernameErrorTip)
	{
		tipUsernameErrorLayer->displayOn(this);
		showUsernameErrorTip = true;
	}
	else
	{
		tipUsernameErrorLayer->removeFromParentAndCleanup();
		showUsernameErrorTip = false;
	}
	*/
}

void RegisterLayer::clickPasswordRight(CCObject* pSender)
{
	/*
	if(!showUsernameErrorTip)
	{
		tipUsernameErrorLayer->displayOn(this);
		showUsernameErrorTip = true;
	}
	else
	{
		tipUsernameErrorLayer->removeFromParentAndCleanup();
		showUsernameErrorTip = false;
	}
	*/
}

void RegisterLayer::clickBack(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void RegisterLayer::clickRegister(CCObject* pSender)
{
	map<string,string> post;
	post["api"] = "sign_up";
	post["username"] = usernameText->getString();
	post["password"] = passwordText->getString();
	post["role_type"] = Utils::int2str((int)USER->getRoleType());
	post["level"] = Utils::int2str(USER->getLevel());
	post["exp"] = Utils::int2str(USER->getExp());
	post["basic_agi"] = Utils::int2str(USER->getBasicAGI());
	post["basic_str"] = Utils::int2str(USER->getBasicSTR());
	post["basic_def"] = Utils::int2str(USER->getBasicDEF());
	post["current_weapon"] = Utils::int2str((int)USER->getEquipment().getWeapon());
	post["current_base"] = Utils::int2str((int)USER->getEquipment().getBase());
	post["current_plate"] = Utils::int2str((int)USER->getEquipment().getPlate());
	post["open_chapters_number"] = Utils::int2str(USER->getOpenChaptersNumber());
	post["win_online_game_number"] = Utils::int2str(USER->getWinOnlineGamesNumber());
	post["play_online_game_number"] = Utils::int2str(USER->getPlayOnlineGamesNumber());
	post["money"] = Utils::int2str(USER->getMoney());
	post["honor"] = Utils::int2str(USER->getHonor());

	std::string jsonStr = POST(post);
	
	JsonBox::Value data;
	CCLOG(jsonStr.c_str());
	data.loadFromString(jsonStr);
	if(data["result"].getString()=="OK"){
		USER->setUsername(usernameText->getString());
		USER->setPassword(passwordText->getString());
		USER->setHasSignin(true);
		USER->setIsBeginner(false);
		CCNode* parent = this->getParent();
		this->removeFromParentAndCleanup();
		INFORMATION_BOX(CN("register_and_login_successfully"),parent);
	}
	else if(data["result"].getString()=="Username existed"){
		INFORMATION_BOX(CN("username_existed"),this);
	}
	else{
		INFORMATION_BOX(CN("register_failed"),this);
	}
}

void RegisterLayer::usernameTextFieldPressed(cocos2d::CCObject *sender)
{
	passwordText->detachWithIME();
	usernameText->attachWithIME();
}

void RegisterLayer::passwordTextFieldPressed(cocos2d::CCObject *sender)
{
	usernameText->detachWithIME();
	passwordText->attachWithIME();
}


bool RegisterLayer::usernameVerification()
{
	return false;
}

void RegisterLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void RegisterLayer::removeFromParentAndCleanup(){
	usernameText->detachWithIME();
	passwordText->detachWithIME();
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
}

void RegisterLayer::displayOn(cocos2d::CCNode* node)
{
	this->drawBackground();
	this->drawUsername();
	this->drawPassword();
	this->drawBack();
	this->drawRegister();

	node->addChild(this,20);
}

bool RegisterLayer::onTextFieldAttachWithIME(CCTextFieldTTF * pSender){  
    CCLOG("启动输入");  
      
    return false;  
    //return true:不启动  
}  
bool RegisterLayer::onTextFieldDetachWithIME(CCTextFieldTTF * pSender){  
    CCLOG("关闭输入");  
    //得到输入内容  
    const char* inputStr = pSender->getString();  
    return false;  
    //return true:不关闭  
}  
bool RegisterLayer::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen){  
    CCLOG("输入字符...");  
    return false;  
    //return true:不会输入进字符  
}  
bool RegisterLayer::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen){  
    CCLOG("删除字符");  
    return false;  
    //return true:不删除  
}
