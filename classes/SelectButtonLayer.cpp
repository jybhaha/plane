

#include "SelectButtonLayer.h"

USING_NS_CC;

bool SelectButtonLayer::init() {


	MenuItemSprite* startGameButtonItemSprite1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("selectStartButton_2.png"), Sprite::createWithSpriteFrameName("selectStartButton_1.png"), CC_CALLBACK_1(SelectButtonLayer::startGameButtonCallback, this));
	Menu* startGameButton = Menu::create(startGameButtonItemSprite1, nullptr);	
	startGameButton->setScale(0.4f);
	startGameButton->setAnchorPoint(Point(0, 0));
	startGameButton->setPosition(40, 365);
	this->addChild(startGameButton);

	MenuItemSprite* startGameButtonItemSprite2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("selectStartButton_1.png"), Sprite::createWithSpriteFrameName("selectStartButton_2.png"), CC_CALLBACK_1(SelectButtonLayer::startGameEndlessButtonCallback, this));
	Menu* startGameButtonEndless = Menu::create(startGameButtonItemSprite2, nullptr);

	startGameButtonEndless->setScale(0.4f);
	startGameButtonEndless->setAnchorPoint(Point(0, 0));
	startGameButtonEndless->setPosition(40, 225);

	this->addChild(startGameButtonEndless);

	MenuItemSprite* startGameButtonItemSprite3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("selectStartButton_3.png"), Sprite::createWithSpriteFrameName("selectStartButton_3.png"), CC_CALLBACK_1(SelectButtonLayer::startGameAllBossButtonCallback, this));
	Menu* startGameButtonAllBoss = Menu::create(startGameButtonItemSprite3, nullptr);

	startGameButtonAllBoss->setScale(0.4f);
	startGameButtonAllBoss->setAnchorPoint(Point(0, 0));
	startGameButtonAllBoss->setPosition(40, 85);
	this->addChild(startGameButtonAllBoss);

	MenuItemSprite* startGameButtonItemSprite4 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("Arms.png"), Sprite::createWithSpriteFrameName("Arms.png"), CC_CALLBACK_1(SelectButtonLayer::startGameArmsButtonCallback, this));
	Menu* startGameButtonArms = Menu::create(startGameButtonItemSprite4, nullptr);
	
	startGameButtonArms->setScale(0.4f);
	startGameButtonArms->setAnchorPoint(Point(0, 0));
	startGameButtonArms->setPosition(Director::getInstance()->getWinSize().width - 40, 450);
	this->addChild(startGameButtonArms);
	
	//添加返回按钮
	MenuItemSprite* ButtonReturnItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("arrow_right.png"), Sprite::createWithSpriteFrameName("arrow_right.png"), CC_CALLBACK_1(SelectButtonLayer::ButtonReturn, this));
	Menu* ButtonReturn = Menu::create(ButtonReturnItem, nullptr);
	//ButtonReturn->setScale(0.2f);
	ButtonReturn->setAnchorPoint(Point(0, 0));
	ButtonReturn->setPosition(30, 450);
	this->addChild(ButtonReturn);



	//添加BGM
	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->addSelectSceneEffect();

	return true;
}

void SelectButtonLayer::startGameButtonCallback(Ref* pSender){
// 	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
// 	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
// 	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode",false);
// 	SelectBackgroundLayer* selectBackgroundLayer = SelectBackgroundLayer::create();
// 	this->addChild(selectBackgroundLayer);
// 	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());//2.0
// 	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void SelectButtonLayer::startGameEndlessButtonCallback(Ref* pSender){
// 	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", false);
// 	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", true);
// 	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
// 	SelectBackgroundLayer* selectBackgroundLayer = SelectBackgroundLayer::create();
// 	this->addChild(selectBackgroundLayer);
// 	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());//2.0
// 	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void SelectButtonLayer::startGameAllBossButtonCallback(Ref* pSender){
// 	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode",false);
// 	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
// 	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", true);
// 	SelectBackgroundLayer* selectBackgroundLayer = SelectBackgroundLayer::create();
// 	this->addChild(selectBackgroundLayer);
// 	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());//2.0
// 	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}
void SelectButtonLayer::startGameArmsButtonCallback(Ref* pSender){
	
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, AddArmsScene::create());//2.0
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void SelectButtonLayer::ButtonReturn(Ref* pSender){
	Director::getInstance()->popScene();
}