#pragma once
#include <cocos2d.h>

#define WIN_SIZE CCDirector::sharedDirector()->getWinSize()

typedef enum{
	riverLeft,
	riverRight
}RiverAdr;//河的左边或右边

typedef enum{
	bank,
	boardLeft,
	boardRight
}AdrBoard;//在岸上，船左，船右

class Person :
	public cocos2d::CCNode
{
private:
	int adrID;//地址编号1-6
	RiverAdr riverAdr;//在河流的左边或右边
	AdrBoard adrBoard;//位置（在岸上还是船左或船右）

	virtual void setInit() = 0;//初始站位描绘
public:
	static Person* create(int adrID);
	bool init(int adrID); 

	virtual void TakeBoat() = 0;//上船
	virtual void GoAshore() = 0;//下船
	
	virtual void AcrossRiver() = 0; //过河
	virtual void ClickPerson(CCObject* pSender) = 0;//点击发生函数

	RiverAdr GetRiverAdr();
	AdrBoard GetAdrBoard();

};