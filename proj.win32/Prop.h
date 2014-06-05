#pragma once
#include<cocos2d.h>
#include<Role.h>
USING_NS_CC;

class GameScene;

typedef enum{
	STR_Addition_Prop=0,
	AGI_Addition_Prop,
	DEF_Addition_Prop,
	SP_Addition_Prop,
	Transposition_Prop,
	Reverse_Prop,
	Frozen_Prop,
	Gold_Coin_Prop,
	Banana_Skin_Prop,
	No_Prop,
	UnopenBlock_Prop
}PropType;

class Prop :
	public cocos2d::CCLayer
{
public:
	static Prop* create(PropType type);
	static const int totalPropsNumber = 20;
	bool init(PropType propType);

	CC_SYNTHESIZE(Role*,player,Player);
	CC_SYNTHESIZE(Role*,otherRole,OtherRole);
	CC_SYNTHESIZE(bool,isStepped,IsStepped);
	CC_SYNTHESIZE_READONLY(CCSprite*,propSprite,PropSprite);
	CC_SYNTHESIZE(GameScene*,gamescene,GameScene);
	
	PropType propType;
	void setPropType(PropType propType);
	PropType getPropType();
	void setPropSprite();
	CCRect getCollisionRectangle();
	CCPoint getSpritePosition();
	void placePropRandomly(GameScene* gamescene);
	void steppedBy(Role* role,Role* other);
	void STRAddition();
	void AGIAddition();
	void DEFAddition();
	void SPAddition();
	void transposition();
	void reverse();
	void frozen();
	void goldCoinAffect();
	void bananaSkinAffect(Role* role,Role* other);
	void playEffect();

	void AGIAdditionCallback(float delay);
	void reverseCallback(float delay);
	void removePropFromRoleLayerCallback(float delay);
	void removePropFromRoleLayer();
};

