/*
 * ResultScene.h
 *
 *  Created on: 2015Äê1ÔÂ25ÈÕ
 *      Author: netbeen
 */

#ifndef RESULTSCENE_H_
#define RESULTSCENE_H_

#include "cocos2d.h"
#include "ResultButtonLayer.h"
#include "ResultBackgroundLayer.h"

class ResultScene :public cocos2d::Scene{
public:
	ResultScene();
	~ResultScene();
	static Scene* create(bool isWin, int score);
private:
	static Scene* resultScene;
};

#endif /* RESULTSCENE_H_ */
