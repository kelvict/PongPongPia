#include "Prop.h"
#include "StaticData.h"
#include "GameScene.h"

Prop* Prop::create(PropType type){
	Prop* prop = new Prop();
	prop->init(type);
	prop->autorelease();
	return prop;
}

bool Prop::init(PropType type){
	this->setPropType(type);
	this->setPropSprite();
	this->setIsStepped(false);
	if(type!=No_Prop){
		this->addChild(propSprite);
	}
	return true;
}

void Prop::setPropSprite(){
	if(this->getPropType()!=No_Prop){
		CCString* spriteName = CCString::createWithFormat(STATIC_DATA_STRING("prop_format"),this->getPropType());
		this->propSprite = CCSprite::createWithSpriteFrameName(spriteName->getCString());
	}
}

void Prop::placePropRandomly(GameScene* gamescene){
	//propSprite->setVisible(true);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint position = CCPointMake(size.width/4+CCRANDOM_0_1()*size.width*1/2,size.height/4+CCRANDOM_0_1()*size.height*1/2);
	//this->setPropSprite();
	this->setGameScene(gamescene);
	this->propSprite->setPosition(position);
	this->scheduleOnce(schedule_selector(Prop::removePropFromRoleLayerCallback),5);
	//this->addChild(this->propSprite);
}

CCPoint Prop::getSpritePosition(){
	return this->propSprite->getPosition();
}

CCRect Prop::getCollisionRectangle(){
	return CCRectMake(this->getSpritePosition().x-35,this->getSpritePosition().y+35,70,70);
}

void Prop::steppedBy(Role* role,Role* other){
	this->setPlayer(role);
	this->setOtherRole(other);
	this->setIsStepped(true);
	this->getPropSprite()->removeFromParentAndCleanup(true);
}

void Prop::playEffect(){
	switch (this->getPropType())
	{
	case AGI_Addition_Prop:
		AGIAddition();
		break;
	case Transposition_Prop:
		transposition();
		break;
	case Reverse_Prop:
		reverse();
		break;
	case No_Prop:
		break;
	default:
		break;
		//×¢²áÓÃ»§
	}
//	this->removePropFromRoleLayer();
}

void Prop::AGIAddition(){
	player->setAGI(player->getAGI()+20);
	this->scheduleOnce(schedule_selector(Prop::AGIAdditionCallback),2);	
}
void Prop::AGIAdditionCallback(float delay){
	player->setAGI(player->getAGI()-20);
	this->removeFromParentAndCleanup(true);
}

void Prop::transposition(){
	CCPoint tempPosition = player->getBody()->getPosition();
	CCPoint otherPosition;
	bool hasOtherRole=false;
	CCArray* otherRoles = gamescene->getRoleLayer()->getOtherRoles();
	CCObject* temp;
	CCARRAY_FOREACH(otherRoles,temp){
		Role* otherRole = (Role*) temp;
		if(otherRole->getAlive()==true){
			hasOtherRole = true;
			otherPosition = otherRole->getBody()->getPosition();
			break;
		}
	}
	if(hasOtherRole){
		player->getBody()->setPosition(otherPosition);
		otherRole->getBody()->setPosition(tempPosition);
		this->removeFromParentAndCleanup(true);
	}
}

void Prop::reverse(){
	player->setIsReverse(true);
	player->setSTR(player->getSTR()*3);
	this->scheduleOnce(schedule_selector(Prop::reverseCallback),5);
}

void Prop::reverseCallback(float delay){
	player->setIsReverse(false);
	player->setSTR(player->getSTR()/3);
	this->removeFromParentAndCleanup(false);
}

void Prop::removePropFromRoleLayerCallback(float delay){
	if(this->getIsStepped()==false){
		this->removePropFromRoleLayer();
	}
}

void Prop::removePropFromRoleLayer(){
	RoleLayer* roleLayer = (RoleLayer*)this->getParent();
	roleLayer->getProps()->removeObject(this);
	this->removeFromParentAndCleanup(true);
}

void Prop::setPropType( PropType propType )
{
	this->propType=propType;
}

PropType Prop::getPropType()
{
	return propType;
}




