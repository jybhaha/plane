

#include "BulletUserData.h"

BulletUserData::BulletUserData(int initDamage, int initBulletLevel):damage(initDamage),bulletLevel(initBulletLevel){
}

int BulletUserData::getDamage() const{
	return this->damage;
}

int BulletUserData::getBulletLevel() const{
	return this->bulletLevel;
}
