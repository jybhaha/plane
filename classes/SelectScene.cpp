#include "SelectScene.h"

USING_NS_CC;

Scene* SelectScene::selectScene = nullptr;

Scene* SelectScene::create() {
	selectScene = Scene::create();

	SelectBackgroundLayer* selectBackgroundLayer = SelectBackgroundLayer::create();
	selectScene->addChild(selectBackgroundLayer);

	SelectButtonLayer* selectButtonLayer = SelectButtonLayer::create();
	selectScene->addChild(selectButtonLayer);

	return selectScene;

}
