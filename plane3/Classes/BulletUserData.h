/*
 * BulletUserData.h
 *
 *  Created on: 2015��1��18��
 *      Author: netbeen
 */

#ifndef BULLETUSERDATA_H_
#define BULLETUSERDATA_H_

class BulletUserData {
public:
	BulletUserData(int initDamage, int initBulletLevel);
	int getDamage() const;
	int getBulletLevel() const;
private:
	int damage;
	int bulletLevel;
};

#endif /* BULLETUSERDATA_H_ */
