//
//  RoleLayer.h
//  PongPongPia
//
//  Created by Kelvict on 13-9-20.
//
//

#ifndef ROLELAYER_H
#define ROLELAYER_H

#include "cocos2d.h"
#include "Role.h"
#include <vector>
#include "Prop.h"
#include "Swamp.h"
#include "Wind.h"
#include "Stone.h"
class RoleLayer : public cocos2d::CCLayer
{
public:
	CREATE_FUNC(RoleLayer);
	CC_SYNTHESIZE_READONLY(Role*, player, Player);
	CC_SYNTHESIZE_READONLY(Role*, computer, Computer);
	CC_SYNTHESIZE(CCArray*, stones, Stones);
	CC_SYNTHESIZE(CCArray*,otherRoles,OtherRoles);
	CC_SYNTHESIZE_READONLY(Swamp*, swamp, Swamp);
	CC_SYNTHESIZE_READONLY(Wind*, wind, Wind);
	CC_SYNTHESIZE(CCArray*,swamps,Swamps); 
	CC_SYNTHESIZE(CCArray*,props,Props);
	CC_SYNTHESIZE(int,killedNumber,KilledNumber);
	CC_SYNTHESIZE(bool,isFirstTimeUpdate,IsFirstTimeUpdate);

	std::vector<PropType> propTypes;
	bool init();
	//Swamp* swamp;
	//Wind* wind;
	void setSwamp(Swamp* swamp);
	void setWind(Wind* wind);	
	void setPlayer(Role* player);
	void setComputer(Role* computer);
	void movePlayer(cocos2d::CCPoint velocity);
	void addOtherRole(Role* role);
	void startAllNormalSpin_repeatForever(void);
	void stopAllNormalSpin_repeatForever(void);


	void addStone(Stone* stone);
	void update(float delta);
	~RoleLayer();
	void handleCollision();
	void handleCollisionBetweenPlayAndStones();
	void handleCollisionBetweenPlayerAndComputer();
	void handleCollisionBetweenRolesAndBoundary();
	bool handleCollisionBetweenPropsAndPlayer();
	void handleCollisionBetweenPlayAndSwamp();
	void handleUltimateEvent();
	void playerLose();
	void playerWin();
protected:
	bool isCollisionBetween(Role* roleA,Role* roleB);
	bool isCollisionBetweenPlayerAndComputer();
	int hasShowBoundaryPoint;

	//boundary
	int polySides;
	int* polyX;
	int* polyY;

	void initBoundaryPolygon();

	void handleBumpBetween(Role* roleA,Role* roleB);
	bool pointInPolygon(cocos2d::CCPoint point);
	void createPropRandomly();
	bool initPropTypes();
	void handleCollisionAroundPlayerAndOtherRoles();
	void removeSparkCallback(float delay);
	void createSpark(int positionX,int positionY);
};
#endif
