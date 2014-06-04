#include "LogIntoLayer.h"
#include "StaticData.h"
#include"RegisterLayer.h"
#include "JsonBox.h"
#include"CurlUtils.h"
#include"PopWindowsLayer.h"
LogIntoLayer* LogIntoLayer::create()
{
	LogIntoLayer* logIntoLayer = new LogIntoLayer();
	logIntoLayer->init();
	logIntoLayer->autorelease();
	return logIntoLayer;
}

bool LogIntoLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	showUsernameErrorTip = false;
	showPasswordErrorTip = false;

	this->CreatTipLayer();
	this->creatUsernameText();
	this->creatPasswordText();
	

	return true;
}

void LogIntoLayer::CreatTipLayer()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos1 = CCPointMake(winSize.width*35/60,winSize.height/2);

	TipsLayer* tiplayer1 = TipsLayer::create((TipsType)2,(TipsDirType)1,pos1);
	tiplayer1->retain();

	tipUsernameErrorLayer = tiplayer1;
	showUsernameErrorTip = false;


	CCPoint pos2 = CCPointMake(winSize.width*35/60,winSize.height*9/30);

	TipsLayer* tiplayer2 = TipsLayer::create((TipsType)2,(TipsDirType)1,pos2);
	tiplayer2->retain();

	tipPasswordErrorLayer = tiplayer2;
	showPasswordErrorTip = false;
}

void LogIntoLayer::creatUsernameText()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*220/500,winSize.height*318/500);

	CCTextFieldTTF* text = CCTextFieldTTF::textFieldWithPlaceHolder(
		"Input Your Name...","Arial",20);
	text->setColor(ccc3(INPUT_R,INPUT_G,INPUT_B));
	text->setPosition(pos);
	this->addChild(text,20);
	text->setDelegate(this);

	text->retain();
	usernameText = text;
	
}

void LogIntoLayer::creatPasswordText()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*220/500,winSize.height*22/50);

	CCTextFieldTTF* text = CCTextFieldTTF::textFieldWithPlaceHolder(
		"Input Your Password...","Arial",20);
	text->setColor(ccc3(INPUT_R,INPUT_G,INPUT_B));
	text->setPosition(pos);
	this->addChild(text,20);
	text->setDelegate(this);
	text->retain();
	passwordText = text;
}

void LogIntoLayer::removeFromParentCallback(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void LogIntoLayer::drawBackground()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Register_window"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width/2,winSize.height/2));
	this->addChild(pBg);	
}

void LogIntoLayer::drawRegisterNewUser()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Log_into_newaccount-normal"),
			STATIC_DATA_STRING("Log_Register_Log_into_newaccount-click"),
			this,
			menu_selector(LogIntoLayer::clickRegisterNewUser)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*368/500,winSize.height*505/600);

	menu->setPosition(pos);
	this->addChild(menu);
}

void LogIntoLayer::drawUsernameLeft()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Log_into_account"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width*105/400,winSize.height*318/500));
	this->addChild(pBg);	
}

void LogIntoLayer::drawUsernameRight()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Log_into_inputbox-normal"),
			STATIC_DATA_STRING("Log_Register_Log_into_inputbox-click"),
			this,
			menu_selector(LogIntoLayer::usernameTextFieldPressed)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*283/500,winSize.height*318/500);

	menu->setPosition(pos);
	this->addChild(menu);

}

void LogIntoLayer::drawUsername()
{
	this->drawUsernameLeft();
	this->drawUsernameRight();
}


void LogIntoLayer::drawPasswordLeft()
{
	CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"Log_Register_Log_into_password"));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pBg->setPosition(CCPointMake(winSize.width*105/400,winSize.height*224/500));
	this->addChild(pBg);	
}

void LogIntoLayer::drawPasswordRight()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Log_into_inputbox-normal"),
			STATIC_DATA_STRING("Log_Register_Log_into_inputbox-click"),
			this,
			menu_selector(LogIntoLayer::passwordTextFieldPressed)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*283/500,winSize.height*22/50);

	menu->setPosition(pos);
	this->addChild(menu);	
}

void LogIntoLayer::drawPassword()
{
	this->drawPasswordLeft();
	this->drawPasswordRight();
}

void LogIntoLayer::drawBack()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Log_into_normal-back"),
			STATIC_DATA_STRING("Log_Register_Log_into_click-back"),
			this,
			menu_selector(LogIntoLayer::clickBack)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*104/300,winSize.height*11/50);

	menu->setPosition(pos);
	this->addChild(menu);
}

void LogIntoLayer::drawLogInto()
{
	CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("Log_Register_Log_into_normal-longin"),
			STATIC_DATA_STRING("Log_Register_Log_into_click-longin"),
			this,
			menu_selector(LogIntoLayer::clickLogInto)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = CCPointMake(winSize.width*196/300,winSize.height*11/50);

	menu->setPosition(pos);
	this->addChild(menu);
}

void LogIntoLayer::clickRegisterNewUser(CCObject* pSender)
{
	RegisterLayer* registerLayer = RegisterLayer::create();
	registerLayer->displayOn(this->getParent());
	this->removeFromParentAndCleanup();
}

void LogIntoLayer::clickUsernameRight(CCObject* pSender)
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

void LogIntoLayer::clickPasswordRight(CCObject* pSender)
{
	/*
	if(passwordVerification())
		return ;
	if(!showPasswordErrorTip)
	{
		tipPasswordErrorLayer->displayOn(this);
		showPasswordErrorTip = true;
	}
	else
	{
		tipPasswordErrorLayer->removeFromParentAndCleanup();
		showPasswordErrorTip = false;
	}*/
}

void LogIntoLayer::clickBack(CCObject* pSender)
{
	this->removeFromParentAndCleanup();
}

void LogIntoLayer::clickLogInto(CCObject* pSender)
{
	map<string,string> post;
	post["api"] = "login";
	post["username"]=usernameText->getString();
	post["password"]=passwordText->getString();
	std::string jsonStr = POST(post);
	JsonBox::Value data;
	CCLOG(jsonStr.c_str());
	data.loadFromString(jsonStr);
	if(data["result"].getString()=="OK"){
		CCLOG("Login Successfully!");
		USER->setUserID(atoi(data["0"]["user_id"].getString().c_str()));
		USER->setUsername(data["0"]["username"].getString());
		USER->setPassword(data["0"]["password"].getString());
		USER->setLevel(atoi(data["0"]["level"].getString().c_str()));
		USER->setExp(atoi(data["0"]["exp"].getString().c_str()));
		USER->setBasicAGI(atoi(data["0"]["basic_agi"].getString().c_str()));
		USER->setBasicSTR(atoi(data["0"]["basic_str"].getString().c_str()));
		USER->setBasicDEF(atoi(data["0"]["basic_def"].getString().c_str()));
		Equipment* equipment = new Equipment();
		equipment->setWeapon(Weapon(atoi(data["0"]["current_weapon"].getString().c_str())));
		equipment->setBase(Base(atoi(data["0"]["current_base"].getString().c_str())));
		equipment->setPlate(Plate(atoi(data["0"]["current_plate"].getString().c_str())));//
		USER->setOpenChaptersNumber(atoi(data["0"]["open_chapters_number"].getString().c_str()));
		USER->setWinOnlineGamesNumber(atoi(data["0"]["win_online_game_number"].getString().c_str()));
		USER->setPlayOnlineGamesNumber(atoi(data["0"]["play_online_game_number"].getString().c_str()));
		USER->setMoney(atoi(data["0"]["money"].getString().c_str()));
		CCLOG(data["0"]["money"].getString().c_str());
		USER->setHonor(atoi(data["0"]["honor"].getString().c_str()));
		USER->setHasSignin(true);
		USER->setIsBeginner(false);
		USER->flush();
		CCNode* parent = this->getParent();
		this->removeFromParentAndCleanup();
		INFORMATION_BOX("Login successfully!",parent);
	}
	else{
		PopWindowsLayer::createInfomationBox("Login failed!",this);
	}
}

void LogIntoLayer::usernameTextFieldPressed(cocos2d::CCObject *sender)
{
	passwordText->detachWithIME();
	usernameText->attachWithIME();
}

void LogIntoLayer::passwordTextFieldPressed(cocos2d::CCObject *sender)
{
	usernameText->detachWithIME();
	passwordText->attachWithIME();
}

bool LogIntoLayer::usernameVerification()
{
	return false;
}

bool LogIntoLayer::passwordVerification()
{
	return false;
}

void LogIntoLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void LogIntoLayer::removeFromParentAndCleanup(){
	usernameText->detachWithIME();
	passwordText->detachWithIME();
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
}

void LogIntoLayer::displayOn(cocos2d::CCNode* node)
{
	this->drawBackground();
	this->drawRegisterNewUser();
	this->drawUsername();
	this->drawPassword();
	this->drawBack();
	this->drawLogInto();

	node->addChild(this,20);

}

bool LogIntoLayer::onTextFieldAttachWithIME(CCTextFieldTTF * pSender){  
    CCLOG("启动输入");  
      
    return false;  
    //return true:不启动  
}  
bool LogIntoLayer::onTextFieldDetachWithIME(CCTextFieldTTF * pSender){  
    CCLOG("关闭输入");  
    //得到输入内容  
    const char* inputStr = pSender->getString();  
    return false;
    //return true:不关闭  
}  
bool LogIntoLayer::onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen){  
    CCLOG("输入字符...");  
    return false;  
    //return true:不会输入进字符  
}  
bool LogIntoLayer::onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen){  
    CCLOG("删除字符");  
    return false;  
    //return true:不删除  
}  