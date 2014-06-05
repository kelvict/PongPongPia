#include "RoleLayer.h"
#include "StaticData.h"
#include "PersonalAudioEngine.h"
#include "GameScene.h"
#include "Prop.h"
#include "UserData.h"
#include "BackgroundLayer.h"
#include "CCShake.h"
#include "Stone.h"
bool RoleLayer::init(){
	if(CCLayer::init()){
		otherRoles = CCArray::createWithCapacity(10);
		CC_SAFE_RETAIN(otherRoles);
		stones = CCArray::create();
		CC_SAFE_RETAIN(stones);
		this->isFirstTimeUpdate = true;
		int capacity = 10;
		props = CCArray::createWithCapacity(capacity);
		CC_SAFE_RETAIN(props);
		this->setKilledNumber(0);
		this->setSwamp(NULL);
		this->setWind(NULL);
		this->initPropTypes();
		this->hasShowBoundaryPoint =0;
		return true;
	}
	return false;
}

bool RoleLayer::initPropTypes(){
	for(int i=0;i<MAX_AVAILABLE_PROP_NUMBER;i++){
		if(USER->canUseProps[i]!=No_Prop&&USER->canUseProps[i]!=UnopenBlock_Prop){
			propTypes.push_back(USER->canUseProps[i]);
		}
	}
	return true;
}

void RoleLayer::createSpark(int positionX,int positionY){
	CCSprite* spark = CCSprite::create("following_shader/feedback_crashing.png");
	spark->setPosition(ccp(positionX,positionY));
	this->addChild(spark);
	spark->scheduleOnce(schedule_selector(RoleLayer::removeSparkCallback),0.5f);
	
}

void RoleLayer::removeSparkCallback(float delay){
	this->removeFromParentAndCleanup(true);
}

RoleLayer::~RoleLayer(){
	delete polyX;
	delete polyY;
	CC_SAFE_RELEASE(otherRoles);
	CC_SAFE_RELEASE(props);
}

void RoleLayer::movePlayer(cocos2d::CCPoint velocity){
	if(player->getIsReverse()==false){
		player->moveBy(velocity);
	}
	else{
		player->moveBy(ccpNeg(velocity));
	}
}

void RoleLayer::addOtherRole(Role* role){
	role->retain();
	int count = otherRoles->count();
	count++;
	bool isOdd=count%2;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	otherRoles->addObject(role);
	role->getBody()->setPosition(ccp(size.width/2+50,size.height/2+(isOdd?+50:-50)));
	this->addChild(role);
}

void RoleLayer::setPlayer(Role* player){
	player->retain();
	this->player = player;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->player->getBody()->setPosition(ccp(size.width/2-50,size.height/2));
	this->addChild(this->player);
}

void RoleLayer::setComputer(Role* computer){
	this->computer = computer;
	this->computer->setStatus(Enemy);
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->computer->getBody()->setPosition(ccp(size.width/2+50,size.height/2));
	this->addChild(this->computer);
}

void RoleLayer::startAllNormalSpin_repeatForever(){
	this->player->startNormalSpin_repeatForever();	
//	this->computer->startNormalSpin_repeatForever();
	CCObject* iterator;
	if(this->otherRoles->count()>0){
		CCARRAY_FOREACH(this->otherRoles,iterator){
			Role* role = (Role*)(iterator);
			role->startNormalSpin_repeatForever();
		}
	}
}

void RoleLayer::stopAllNormalSpin_repeatForever(){
	this->player->stopNormalSpin_repeatForever();
//	this->computer->stopNormalSpin_repeatForever();
	CCObject* iterator=NULL;
	CCARRAY_FOREACH(this->otherRoles,iterator){
		Role* role = (Role*)(iterator);
		role->stopNormalSpin_repeatForever();
	}
}	

void RoleLayer::update(float delta){
	if(isFirstTimeUpdate){
		isFirstTimeUpdate=false;
		this->initBoundaryPolygon();
	}

	if (wind != NULL) {
		CCPoint speed = Wind::getWindSpeed();
		int agi = player->getAGI();
		player->moveBy(ccp(speed.x / agi, speed.y / agi));
	}

	this->handleCollision();
	//this->handleUltimateEvent();
}


void RoleLayer::addStone(Stone* stone) {
	this->stones->addObject(stone);
	this->addChild(stone);
	stone->setScaleAndZOrder();
}

void RoleLayer::setSwamp(Swamp* swamp)
{
	this->swamp = swamp;
	if (swamp != NULL) 
		this->addChild(this->swamp);
}
void RoleLayer::setWind(Wind* wind)
{
	this->wind = wind;
	if (wind != NULL)
		this->addChild(wind);
}
// End Test

void RoleLayer::handleUltimateEvent(){
	if(this->getPlayer()->getSP()>=STATIC_DATA_INT("ultimate_spin_SP_need")){
		this->getPlayer()->setSP(player->getSP()-STATIC_DATA_INT("ultimate_spin_SP_need"));
		this->getPlayer()->startUltimateSpin_FiniteTimeAction();
	}
}

void RoleLayer::handleCollision(){
	GameScene* gamescene = (GameScene*)this->getParent();
	if(gamescene->getGameSceneState()!=Playing_GameSceneState){return;}

	handleCollisionAroundPlayerAndOtherRoles();
	handleCollisionBetweenRolesAndBoundary();
	handleCollisionBetweenPropsAndPlayer();
	handleCollisionBetweenPlayAndSwamp();
	handleCollisionBetweenPlayAndStones();
}

void RoleLayer::handleCollisionAroundPlayerAndOtherRoles(){
	CCObject* iter;
	CCARRAY_FOREACH(otherRoles,iter){
		Role* role = (Role*)iter;
		if(isCollisionBetween(player,role)){
			GameScene* gamescene  = (GameScene*)this->getParent();
			//gamescene->_backgroundLayer->runAction(CCShake::create(0.1f,10));
			PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("collision_sound"));
			handleBumpBetween(player,role);
			this->createPropRandomly();
			//if (!gamescene->getisFullOfEnergy())
			//	gamescene->increaceEnetgy();
		}
	}

	for(int i=0;i<otherRoles->count();i++){
		for(int j = i+1;j<otherRoles->count();j++){
			Role* roleA = (Role*)otherRoles->objectAtIndex(i);
			Role* roleB = (Role*)otherRoles->objectAtIndex(j);

			if(isCollisionBetween(roleA,roleB)){
				PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("collision_sound"));
				handleBumpBetween(roleA,roleB);				
			}
		}
	}
}

void RoleLayer::handleCollisionBetweenPlayerAndComputer(){
	if(isCollisionBetweenPlayerAndComputer()){
		PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("collision_sound"));
		handleBumpBetween(this->getPlayer(),this->getComputer());
		// 出错点
		this->createPropRandomly();
		GameScene* gamescene =  (GameScene*)this->getParent();
		//if (!gamescene->getisFullOfEnergy())
		//	gamescene->increaceEnetgy();
	}
}
bool RoleLayer::isCollisionBetweenPlayerAndComputer(){
	return isCollisionBetween(this->getPlayer(),this->getComputer());
}

bool RoleLayer::isCollisionBetween(Role* roleA,Role* roleB){
	CCRect roleACollisionRectangle = roleA->getCollisionRectangle();
	CCRect roleBCollisionRectangle = roleB->getCollisionRectangle();
	return roleA->getCollisionRectangle().intersectsRect(roleB->getCollisionRectangle());
}

void RoleLayer::handleBumpBetween(Role* roleA,Role* roleB){
	roleA->getBump(roleB);
	roleB->getBump(roleA);
	if(roleA->getState() == state_ultimate&&roleB->getState()!=state_petrified){
		roleB->startPetrifiedStanding_FiniteTimeAction();
	}
	if(roleB->getState() == state_ultimate&&roleA->getState()!=state_petrified){
		roleA->startPetrifiedStanding_FiniteTimeAction();
	}
	this->createSpark((roleA->getBody()->getPositionX()+roleB->getBody()->getPositionX())/2,(roleA->getBody()->getPositionY()+roleB->getBody()->getPositionY())/2);
}

//边界碰撞处理
void RoleLayer::handleCollisionBetweenRolesAndBoundary()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* labelLose = CCLabelTTF::create("Lose the game", "Arial", 28);
	CCLabelTTF* labelWin = CCLabelTTF::create("Win the game", "Arial", 28);
	
	
	if (!pointInPolygon(this->player->getBody()->getPosition())) {
		this->playerLose();
		return;
	}
	if(killedNumber>=otherRoles->count()){
		this->playerWin();
		return ;
	}
	CCObject* iter;
	CCARRAY_FOREACH(otherRoles,iter){
		Role* role = (Role*) iter;
		if(role->getAlive()==false){continue;}
		if(!pointInPolygon(role->getBody()->getPosition())){
			role->killed();
			role->stopAllActions();
			role->getBody()->setVisible(false);
			killedNumber++;
		}
	}
}

void RoleLayer::playerLose(){
	this->player->killed();
	GameScene* gamescene =  (GameScene*)this->getParent();
	gamescene->showResult(false);
}

void RoleLayer::playerWin(){
	GameScene* gamescene =  (GameScene*)this->getParent();
	gamescene->showResult(true);
}

bool RoleLayer::pointInPolygon(cocos2d::CCPoint point)
{
	// get bounday from static file and dicide the polyX
	// GameScee Gametype


	int i, j = polySides - 1;
	bool oddNodes = false;
	
	for (i=0; i< polySides; i++) {

		if((polyY[i]< point.y && polyY[j] >= point.y 
			|| polyY[j] < point.y && polyY[i] >= point.y) 
			&& (polyX[i]<= point.x || polyX[j] <= point.x)) 
		{
			oddNodes^=(polyX[i]+(point.y-polyY[i])/(polyY[j]-polyY[i])*(polyX[j]-polyX[i])<point.x);
		}
		j=i;
	}
	return oddNodes;
}

bool RoleLayer::handleCollisionBetweenPropsAndPlayer()
{	
	bool isCollision=false;
	CCObject *temp = NULL;
	if (props && props->count() > 0) {
		CCARRAY_FOREACH(props,temp){
			Prop* prop = dynamic_cast<Prop*>(temp);

			CCRect propCollisionRect=prop->getCollisionRectangle();
			CCRect playerCollisionRect = player->getCollisionRectangle();
			if(propCollisionRect.intersectsRect(playerCollisionRect)){
				Role* role;
				bool flag =false;
				for(int i=0;i<this->getOtherRoles()->count();i++){
					role =(Role*)this->getOtherRoles()->objectAtIndex(0);
					if(role->getAlive()==true){
						flag=true;
						break;
					}
				}
				prop->steppedBy(player,role);
				GameScene* gamescene =  (GameScene*)this->getParent();
				gamescene->placeProp(prop);
				props->removeObject(prop);
				isCollision=true;
				PersonalAudioEngine::sharedEngine()->playEffect(STATIC_DATA_STRING("eat_prop"));
			}
		}
	}
	
	return isCollision;
}

void RoleLayer::createPropRandomly(){
	if(CCRANDOM_0_1()>=0.8 && props->count() < 5){
		if(propTypes.size()>0){
			Prop* prop;
			int i = int(CCRANDOM_0_1()*(propTypes.size()));
			if(i>=propTypes.size()){
				i=propTypes.size() - 1;
			}

			PropType type = (PropType)propTypes[i];

			props->addObject(prop = Prop::create(type));

			this->addChild(prop);
			prop->placePropRandomly((GameScene*)this->getParent());
			
		}
	}
	
}

void RoleLayer::handleCollisionBetweenPlayAndSwamp()
{
	if (swamp == NULL)
		return;

	// ÒªÊ¹ÓÃÒ»¸ö±äÁ¿Çø±ðµ±Ç°ÊÇ·ñÔÚÏÝÚåÖ®ÖÐ
	CCRect playerColRect = player->getCollisionRectangle();
	CCRect swampColRect = swamp->getCollisionRectangle();
	GameScene* gamescene =  (GameScene*)this->getParent();

	if (playerColRect.intersectsRect(swampColRect)) {
		// if player not in the swamp
		// set true and set the AGI
		if (player->getInSwamp() == false) {
			player->setInSwamp(true);
			float f = Swamp::getSlowDownSpeed();
			player->setAGI(player->getAGI() * f);
			gamescene->gameStateTagLayer->addGameStateTag(SWAMP_GAME_STATE);
		}
	} else {
		//gamescene->setInSwamp(false);
		if (player->getInSwamp() == true) {
			player->setInSwamp(false);
			float f = Swamp::getSlowDownSpeed();
			player->setAGI(player->getAGI() / f);
			gamescene->gameStateTagLayer->removeGameStateTag(SWAMP_GAME_STATE);
		}
	}

	//CCObject* iter;
	//CCARRAY_FOREACH(otherRoles,iter){
	//	Role* role = (Role*) iter;
	//	if(role->getAlive() == false){continue;}
	//	CCRect computerColRect = role->getCollisionRectangle();
	//	if(computerColRect.intersectsRect(swampColRect)){
	//		if (role->getInSwamp() == false) {
	//			role->setInSwamp(true);
	//			float f = Swamp::getSlowDownSpeed();
	//			role->setAGI(role->getAGI() * f);
	//		}
	//	} else {
	//		if (role->getInSwamp() == true) {
	//			role->setInSwamp(false);
	//			float f = Swamp::getSlowDownSpeed();
	//			if (f != 0)
	//				role->setAGI(role->getAGI() / f);
	//		}
	//	}
	//}

}


void RoleLayer::handleCollisionBetweenPlayAndStones()
{
	// TO-DO
	CCRect playerColRect = player->getCollisionRectangle();
	CCPoint playPosition = player->getBody()->getPosition();
	CCRect stoneColRect;

	CCObject* iter;
	CCARRAY_FOREACH(stones, iter) {
		Stone* stone = (Stone*)iter;
		stoneColRect = stone->getCollisionRectangle();
		CCPoint stonePosition = stone->getPosition();
		// collosion with player
		if (playerColRect.intersectsRect(stoneColRect)) {
			// relect
			CCPoint velocity = ccpNormalize(
				ccpSub(playPosition, stonePosition));
			player->moveBy(ccpMult(velocity, 2.0));
		}

		// collosion with bag persion
		CCObject* iter;
		CCARRAY_FOREACH(otherRoles,iter) {
			Role* role = (Role*) iter;
			if(role->getAlive() == false) { continue; }
			CCRect computerColRect = role->getCollisionRectangle();
			CCPoint rolePosition = role->getBody()->getPosition();
			if (computerColRect.intersectsRect(stoneColRect)) {
				// reflect
				CCLog("computer");
				CCPoint velocity = ccpNormalize(
					ccpSub(rolePosition, stonePosition));
				role->moveBy(ccpMult(velocity,5.0));
			}
		}

	}
}

void RoleLayer::initBoundaryPolygon()
{
	GameScene* gamescene = (GameScene*)this->getParent();

	polySides = 6;

	polyX = new int[polySides];
	polyY = new int[polySides];


	std::string mapPosition = STATIC_DATA_STRING(CCString::createWithFormat(STATIC_DATA_STRING("map_position_format"),(int)gamescene->getGameType())->getCString());
	// sscanf(speedStr->getCString(), "(%f,%f)", &speedX, &speedY);
	// (643,46)(1270,316)(1034,588),(662,688),(185,591),(1,290)
	sscanf(mapPosition.c_str(),"(%d,%d),(%d, %d),(%d,%d),(%d,%d),(%d,%d),(%d,%d)", 
		&polyX[0], &polyY[0], &polyX[1], &polyY[1], &polyX[2], &polyY[2], 
		&polyX[3], &polyY[3], &polyX[4], &polyY[4], &polyX[5], &polyY[5]);


	CCPoint playPosition = ((GameScene*)(this->getParent()))->getPlayer()->getBody()->getPosition();
	//tomodified
	for(int i=0;i<6;i++){
		polyX[i]+=0;
		polyY[i]+=0;
	}
}
