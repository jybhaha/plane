#include "AddArmsScene.h"

USING_NS_CC;

Scene* AddArmsScene::addarmsscene = nullptr;

Scene* AddArmsScene::create() {
	addarmsscene = Scene::create();

	ArmsBackGroud* armsBackGroud = ArmsBackGroud::create();
	addarmsscene->addChild(armsBackGroud);

	return addarmsscene;
}
