/*
 * ResultScene.cpp
 *
 *  Created on: 2015Äê1ÔÂ25ÈÕ
 *      Author: netbeen
 */

#include "ResultScene.h"

USING_NS_CC;

Scene* ResultScene::resultScene = nullptr;

ResultScene::ResultScene(){}
ResultScene::~ResultScene(){
	Scene::onExit();
}

Scene* ResultScene::create(bool isWin, int score) {
	resultScene = Scene::create();

	ResultBackgroundLayer* resultBackgroundLayer = ResultBackgroundLayer::create();
	//resultBackgroundLayer->setParent(resultScene);
	resultScene->addChild(resultBackgroundLayer);

	resultBackgroundLayer->setIsWin(isWin);
	resultBackgroundLayer->setScore(score);
	resultBackgroundLayer->displayInfomation();

	ResultButtonLayer* resultButtonLayer = ResultButtonLayer::create();
	//resultButtonLayer->setParent(resultScene);
	resultScene->addChild(resultButtonLayer);

	return resultScene;

}

