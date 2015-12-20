#include "PlaneUserData.h"

#include "cocos2d.h"


PlaneUserData::PlaneUserData(int initHP):HP(initHP){
}

bool PlaneUserData::isAliveUnderAttack(int damage){
	this->HP -= damage;
	if(this->HP <= 0){
		return false;
	}else{
		return true;
	}
}

int PlaneUserData::getHP() const{
	return this->HP;
}

void PlaneUserData::addBlood(int num){
	this->HP += num;

}