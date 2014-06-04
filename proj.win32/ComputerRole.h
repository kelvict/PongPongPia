#pragma once
#include "role.h"
#include<cocos2d.h>

USING_NS_CC;
class ComputerRole :
	public Role
{
public:
	static ComputerRole* create(RoleType roleType ,Status status,Equipment* pEquipment);
	bool init(RoleType roleType,Status status,Equipment* pEquipment);

};

