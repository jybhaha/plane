#ifndef PLANEUSERDATA_H_
#define PLANEUSERDATA_H_

#include "cocos2d.h"

class PlaneUserData {
public:
	PlaneUserData(int initHP);
	bool isAliveUnderAttack(int damage);
	void addBlood(int num);
	int getHP() const;
private:
	int HP;
};

#endif /* PLANEUSERDATA_H_ */
