#include "gameHelp.h"

USING_NS_CC;

Scene* gameHelp::gamehelpscene = nullptr;

Scene* gameHelp::create() {
	gamehelpscene = Scene::create();

	gameHelpBackgroud* gamebackgroud = gameHelpBackgroud::create();
	gamehelpscene->addChild(gamebackgroud);

	return gamehelpscene;
}