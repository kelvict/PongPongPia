#pragma once
#include<cocos2d.h>

USING_NS_CC;

typedef enum{
	k_WEAPON,
	k_BASE,
	k_PLATE
}Equipment_type;

typedef enum{
	weapon_none=0,
	blue_lolly,
	strawberry_lolly,
	watermelon_lolly,
	sunflower_lolly
}Weapon;

typedef enum{
	base_none=0,
	blue_chocolate_cake,
	blue_icecream_cake
}Base;

typedef enum{
	plate_none=0,
	strawberry_plate,
	apple_plate,
	pineapple_plate
}Plate;



class Equipment :
	public CCObject
{
public:
	CC_SYNTHESIZE(Weapon,weapon,Weapon);
	CC_SYNTHESIZE(Base,base,Base);
	CC_SYNTHESIZE(Plate,plate,Plate);

	static Equipment* create(Weapon weapon=weapon_none,Base base=base_none,Plate plate=plate_none);
	bool init(Weapon weapon=blue_lolly,Base base=base_none,Plate plate=plate_none);

	
};

