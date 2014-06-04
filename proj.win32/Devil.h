#pragma once
#include <cocos2d.h>
#include"Person.h"
#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

class Pastor :
	public Person
{
private:
	virtual void setInit();//初始站位描绘
public:
	static Pastor* create(int adrID);
	bool init(int adrID); 

	virtual void TakeBoat();//上船
	virtual void GoAshore();//下船

	virtual void AcrossRiver() ; //过河

	virtual void ClickPerson(CCObject* pSender);//点击发生函数

	void KillPastor();//杀牧师

};