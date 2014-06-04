
#include "ViewDataLayer.h";
#include "PersonalInfoLayer.h";

 PersonalInfoLayer* PersonalInfoLayer::create(CurrentWindowType type)
 {
	PersonalInfoLayer* personalInfoLayer = new PersonalInfoLayer();
	personalInfoLayer->init(type);
	personalInfoLayer->autorelease();
	return personalInfoLayer;
 }

 bool PersonalInfoLayer::init(CurrentWindowType type)
 {
	 if(!CCLayer::init())
	 {
		 return false;
	 }
	 this->setTouchEnabled(true);
	  currentWindow = type;
	  isUseData = true;
	  getdata();
	  
	  if( currentWindow == view_data)
	     CreatViewDataWindow();
	  if(currentWindow == view_equipment)
		  CreatViewEquipmentWindow();
	  if(currentWindow == view_property)
		  CreatViewProperyWindow();
		 
	
	 return true;
 }
 
 PersonalInfoLayer* PersonalInfoLayer::createOtherInfor(Role* role)
 {
	 PersonalInfoLayer* personalInfoLayer = new PersonalInfoLayer();
	personalInfoLayer->init(role);
	personalInfoLayer->autorelease();
	return personalInfoLayer;
 }

 bool PersonalInfoLayer::init(Role* role)
 {
	 currentWindow = view_data;
	 this->setTouchEnabled(true);
	 isUseData = false;
	 CreatViewDataWindow(role);
	 getdata();
	 return true;
 }

 void PersonalInfoLayer::CreatViewDataWindow()
 {
	 viewDataWindow = ViewDataLayer::create();
	 viewDataWindow->retain();
 }
 
   void PersonalInfoLayer::CreatViewDataWindow(Role* role)
 {
	 viewDataWindow = ViewDataLayer::createOtherData(role);
	 viewDataWindow->retain();
 }

 void PersonalInfoLayer::CreatViewProperyWindow()
 {
	 viewProperyindow = ViewProperyLayer::create();
	 viewProperyindow->retain();
 }

 void PersonalInfoLayer::CreatViewEquipmentWindow()
 {
	 viewEquipmentWindow = ViewEquipmentLayer::create();
	 viewEquipmentWindow->retain();
 }

 void PersonalInfoLayer::DrawBackground()
 {
	  CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"PersonalInfoLayer_background"));
	 pBg->setPosition(CCPointMake(WIN_SIZE.width/2,WIN_SIZE.height/2));
	 this->addChild(pBg);	
 }

 void PersonalInfoLayer::DrawBackTo()
 {
	 CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("PersonalInfoLayer_backto"),
			STATIC_DATA_STRING("PersonalInfoLayer_backto"),
			this,
			menu_selector(PersonalInfoLayer::ClickBackTo)
			);
	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*40/1100,WIN_SIZE.height*575/622);
	menu->setPosition(pos);
	this->addChild(menu);
 }

 void PersonalInfoLayer::registerWithTouchDispatcher(){
	 // 这里的触摸优先级设置为 -128 这保证了，屏蔽下方的触摸
	 CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
 }
void PersonalInfoLayer::DrawRole()
 {
	 
	 int weapontype = (int)equipment.getWeapon();
	 int basetype = (int)equipment.getBase();
	 int platetype = (int)equipment.getPlate();
	 int fivecanshu = 0;
	 int sixcanshu = 0;

	 const char* spriteFrameName = 
		  CCString::createWithFormat(
		  STATIC_DATA_STRING("PersonalInfoLayer_role_frame_name"),
		  roleType,
		  weapontype,
		  basetype,
		  platetype,
		  fivecanshu,
		  sixcanshu)->getCString();
	 std::cout<<"frame name:  "<<spriteFrameName<<std::endl;

	 CCSpriteFrame* petrifiedSpriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteFrameName);
	 CCSprite* pBg = CCSprite::spriteWithSpriteFrame(petrifiedSpriteFrame);
	 pBg->setScale(3);
	 pBg->setTag(22);
	 
	 //person info role img
	/*  CCSprite* pBg = CCSprite::create(
		  CCString::createWithFormat(
		  STATIC_DATA_STRING("PersonalInfoLayer_role"),1,1,1)->getCString());*/
	 CCPoint pos = CCPointMake(WIN_SIZE.width*197/1100,WIN_SIZE.height*303/622);
	 pBg->setPosition(pos);
	 this->addChild(pBg);	

 }


 bool PersonalInfoLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
	 //Draw
	 CCLog("LoseLayer touch");
	 return true;
 }

 void PersonalInfoLayer::DrawWindow()
 {
	 CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"PersonalInfoLayer_window"));
	 CCPoint pos = CCPointMake(WIN_SIZE.width*726/1100,WIN_SIZE.height*305/622);
	 pBg->setPosition(pos);
	 this->addChild(pBg);	
 }

 void PersonalInfoLayer::DrawViewData()
 {
	 CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("PersonalInfoLayer_view_data_normal"),
			STATIC_DATA_STRING("PersonalInfoLayer_view_data_click"),
			this,
			menu_selector(PersonalInfoLayer::ClickViewData)
			);
	 if(currentWindow == view_data)
	 {
	 CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"PersonalInfoLayer_view_data_click"));
		pBackItem->setNormalImage(pBg);
	 }

	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*535/1100,WIN_SIZE.height*531/622);
	menu->setPosition(pos);
	this->addChild(menu,11);
 }


  void PersonalInfoLayer::DrawViewEquipment()
 {
	 CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("PersonalInfoLayer_view_equipment_normal"),
			STATIC_DATA_STRING("PersonalInfoLayer_view_equipment_click"),
			this,
			menu_selector(PersonalInfoLayer::ClickViewEquipment)
			);

	  if(currentWindow == view_equipment)
	 {
	 CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"PersonalInfoLayer_view_equipment_click"));
		pBackItem->setNormalImage(pBg);
	 }

	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*725/1100,WIN_SIZE.height*531/622);
	menu->setPosition(pos);
	this->addChild(menu);
 }

    void PersonalInfoLayer::DrawViewProperty()
 {
	 CCMenuItemImage* pBackItem = CCMenuItemImage::create(
			STATIC_DATA_STRING("PersonalInfoLayer_view_property_normal"),
			STATIC_DATA_STRING("PersonalInfoLayer_view_property_click"),
			this,
			menu_selector(PersonalInfoLayer::ClickViewProperty)
			);

	  if(currentWindow == view_property)
	 {
	 CCSprite* pBg = CCSprite::create(STATIC_DATA_STRING(
		"PersonalInfoLayer_view_property_click"));
		pBackItem->setNormalImage(pBg);
	 }

	CCMenu* menu = CCMenu::create(pBackItem,NULL);
	CCPoint pos = CCPointMake(WIN_SIZE.width*914/1100,WIN_SIZE.height*531/622);
	menu->setPosition(pos);
	this->addChild(menu);
 }

	 void PersonalInfoLayer::DrawViewWindow()
 {
	 if(currentWindow == view_data )
	     viewDataWindow->displayOn(this);
	 if(currentWindow == view_equipment)
		 viewEquipmentWindow->displayOn(this);
	 if(currentWindow ==view_property )
		 viewProperyindow->displayOn(this);
 }



	void PersonalInfoLayer::ClickBackTo(CCObject* pSender)
	{
		USER->flush();
		removeFromParentAndCleanup();
	}

	void PersonalInfoLayer::ClickViewData(CCObject* pSender)
	{
	if(isUseData == false)
			return ;
		if(currentWindow != view_data)
		{
			CCNode* a = this->getParent();
			PersonalInfoLayer* newPersonalInfoLayer = 
				PersonalInfoLayer::create(view_data);
			newPersonalInfoLayer->displayOn(a);
			removeFromParentAndCleanup();

			
		}
		
		
	}

	void PersonalInfoLayer::ClickViewEquipment(CCObject* pSender)
	{
	if(isUseData == false)
			return ;
		if(currentWindow != view_equipment)
		{
			CCNode* a = this->getParent();
			PersonalInfoLayer* newPersonalInfoLayer = 
				PersonalInfoLayer::create(view_equipment);
			newPersonalInfoLayer->displayOn(a);
			removeFromParentAndCleanup();

		}
		
	}

	void PersonalInfoLayer::ClickViewProperty(CCObject* pSender)
	{
	if(isUseData == false)
			return ;
		if(currentWindow != view_property)
		{
			CCNode* a = this->getParent();
			PersonalInfoLayer* newPersonalInfoLayer = 
				PersonalInfoLayer::create(view_property);
			newPersonalInfoLayer->displayOn(a);
			removeFromParentAndCleanup();

		}
		
	}

	
void PersonalInfoLayer::operateAllSchedulerAndActions(cocos2d::CCNode* node,
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

void PersonalInfoLayer::removeFromParentAndCleanup(){
	this->operateAllSchedulerAndActions(this->getParent(),k_Operate_Resume);
	this->getParent()->removeChild(this,true);
}

void PersonalInfoLayer::displayOn(cocos2d::CCNode* node)
{
	DrawBackground();
	 DrawBackTo();
	 DrawRole();
	 DrawWindow();
	 DrawViewData();
	 DrawViewEquipment();
	 DrawViewProperty();
	 DrawViewWindow();

	 node->addChild(this,21);
}
void PersonalInfoLayer::ReDrawRole()
{
	this->removeChildByTag(22,true);
	getdata();
	this->DrawRole();
}

void PersonalInfoLayer::getdata()
{
	if(isUseData)
	{
		roleType = (int)UserData::sharedUserData()->getRoleType();
		equipment = UserData::sharedUserData()->getEquipment();
	}

}