#include "Equipment.h"

Equipment* Equipment::create(Weapon weapon,Base base,Plate plate){
	Equipment* equipment = new Equipment();
	equipment->init(weapon,base,plate);
	equipment->autorelease();
	return equipment;
}

bool Equipment::init(Weapon weapon,Base base,Plate plate){
	this->weapon=weapon;
	this->base=base;
	this->plate=plate;
	return true;
}

