#pragma once
#include <cocos2d.h>
#include "cocos2d.h"
#include"Equipment.h"
#include"StartScene.h"
#include "Role.h"
#include "UserData.h"
#include "GameScene.h"
#include"TipsLayer.h"

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()
#define INPUT_R 0
#define INPUT_G 0
#define INPUT_B 0

typedef enum{
	RL_PasswordInput_tag,
	RL_UsernameInput_tag
}RegisterLayerTag;


class RegisterLayer :
	public cocos2d::CCLayer,public cocos2d::CCTextFieldDelegate  
{
public:
	static RegisterLayer* create();
	bool init();

	void CreatTipLayer();

	void creatUsernameText();
	void creatPasswordText();

	CC_SYNTHESIZE(bool,showUsernameErrorTip,ShowUsernameErrorTip);
	CC_SYNTHESIZE(TipsLayer*,tipUsernameErrorLayer,TipUsernameErrorLayer);
	CC_SYNTHESIZE(CCTextFieldTTF*,passwordText,PasswordText);
	CC_SYNTHESIZE(CCTextFieldTTF*,usernameText,usernameText);

	void removeFromParentCallback(CCObject* pSender);

protected:
	void drawBackground();//������

	void drawUsernameLeft();
	void drawUsernameRight();
	void drawUsername();

	void drawPasswordLeft();
	void drawPasswordRight();
	void drawPassword();

	void drawBack();
	void drawRegister();

	void clickUsernameRight(CCObject* pSender);
	void clickPasswordRight(CCObject* pSender);
	void clickBack(CCObject* pSender);
	void clickRegister(CCObject* pSender);

	void usernameTextFieldPressed(cocos2d::CCObject *sender);
	void passwordTextFieldPressed(cocos2d::CCObject *sender);

	bool usernameVerification();

public:
	void operateAllSchedulerAndActions(cocos2d::CCNode* node, OperateFlag flag);
	virtual void removeFromParentAndCleanup();
	void displayOn(cocos2d::CCNode* node);

	//��дCCTextFieldDelegate�Ļص�����  
    //���û������������ʱ�Ļص�����  
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF * pSender);  
    //���û��ر��������ʱ�Ļص�����  
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);  
    //���û���������ʱ�Ļص�����  
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);  
    //���û�ɾ������ʱ�Ļص�����  
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);  
      
};
