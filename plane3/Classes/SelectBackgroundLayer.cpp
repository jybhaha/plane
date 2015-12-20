#include "SelectBackgroundLayer.h"

USING_NS_CC;

bool SelectBackgroundLayer::init() {
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SelectBackgroundLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	//¼ÓÔØ±³¾°Í¼
	Scale9Sprite *background = Scale9Sprite::createWithSpriteFrameName("selectSceneBackground.jpg");
	background->setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);


	Sprite* bottomOfLevel1 = Sprite::createWithSpriteFrameName("bottomOfpicture.png");
	bottomOfLevel1->setAnchorPoint(Point(0, 0.5));
	bottomOfLevel1->setScale(1.1);
	//bottomOfLevel->setRotation(90);
	bottomOfLevel1->setPosition(70, 360);
	bottomOfLevel1->setOpacity(140);
	this->addChild(bottomOfLevel1);

	Sprite* blueBottom1 = Sprite::createWithSpriteFrameName("bottomOfpic.png");
	blueBottom1->setAnchorPoint(Point(0, 0.5));
	blueBottom1->setScale(0.65);
	//bottomOfLevel->setRotation(90);
	blueBottom1->setPosition(75, 295);
	this->addChild(blueBottom1);

	Sprite* bottomOfLevel2 = Sprite::createWithSpriteFrameName("bottomOfpicture.png");
	bottomOfLevel2->setAnchorPoint(Point(0, 0.5));
	bottomOfLevel2->setScale(1.1);
	//bottomOfLevel->setRotation(90);
	bottomOfLevel2->setPosition(70,220);
	bottomOfLevel2->setOpacity(140);
	this->addChild(bottomOfLevel2);

	Sprite* blueBottom2 = Sprite::createWithSpriteFrameName("bottomOfpic.png");
	blueBottom2->setAnchorPoint(Point(0, 0.5));
	blueBottom2->setScale(0.65);
	//bottomOfLevel->setRotation(90);
	blueBottom2->setPosition(75, 155);
	this->addChild(blueBottom2);

	Sprite* bottomOfLevel3 = Sprite::createWithSpriteFrameName("bottomOfpicture.png");
	bottomOfLevel3->setAnchorPoint(Point(0, 0.5));
	bottomOfLevel3->setScale(1.1);
	bottomOfLevel3->setPosition(70, 80);
	bottomOfLevel3->setOpacity(140);
	this->addChild(bottomOfLevel3);

	Sprite* blueBottom3 = Sprite::createWithSpriteFrameName("bottomOfpic.png");
	blueBottom3->setAnchorPoint(Point(0, 0.5));
	blueBottom3->setScale(0.65);
	blueBottom3->setPosition(75, 15);
	this->addChild(blueBottom3);

	MenuItemSprite* blank1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("img_bg_1.jpg"), Sprite::createWithSpriteFrameName("img_bg_1.jpg"), CC_CALLBACK_1(SelectBackgroundLayer::selectCheckPoint_1, this));
	Menu* menuBlank1 = Menu::create(blank1, nullptr);
	menuBlank1->setScale(0.15f);
	menuBlank1->setAnchorPoint(Point(0, 0));
	menuBlank1->setPosition(120, 365);//100
	this->addChild(menuBlank1);

	MenuItemSprite* blank2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("img_bg_2.jpg"), Sprite::createWithSpriteFrameName("img_bg_2.jpg"), CC_CALLBACK_1(SelectBackgroundLayer::selectCheckPoint_2, this));
	Menu* menuBlank2 = Menu::create(blank2, nullptr);
	menuBlank2->setScale(0.15f);
	menuBlank2->setAnchorPoint(Point(0, 0));
	menuBlank2->setPosition(195, 365);
	this->addChild(menuBlank2);

	MenuItemSprite* blank3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("img_bg_3.jpg"), Sprite::createWithSpriteFrameName("img_bg_3.jpg"), CC_CALLBACK_1(SelectBackgroundLayer::selectCheckPoint_3, this));
	Menu* menuBlank3 = Menu::create(blank3, nullptr);
	menuBlank3->setScale(0.15f);
	menuBlank3->setAnchorPoint(Point(0, 0));
	menuBlank3->setPosition(270, 365);
	this->addChild(menuBlank3);

		
	MenuItemSprite* blank4 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("img_bg_4.jpg"), Sprite::createWithSpriteFrameName("img_bg_4.jpg"), CC_CALLBACK_1(SelectBackgroundLayer::selectCheckPoint_4, this));
	Menu* menuBlank4 = Menu::create(blank4, nullptr);
	menuBlank4->setScale(0.15f);
	menuBlank4->setAnchorPoint(Point(0, 0));
	menuBlank4->setPosition(195, 225);//590
	this->addChild(menuBlank4);
	
	MenuItemSprite* blank5 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("img_bg_5.jpg"), Sprite::createWithSpriteFrameName("img_bg_5.jpg"), CC_CALLBACK_1(SelectBackgroundLayer::selectCheckPoint_5, this));
	Menu* menuBlank5 = Menu::create(blank5, nullptr);
	menuBlank5->setScale(0.15f);
	menuBlank5->setAnchorPoint(Point(0, 0));
	menuBlank5->setPosition(195, 85);//590
	this->addChild(menuBlank5);


	
	
// 	Sprite* blank2 = Sprite::createWithSpriteFrameName("img_bg_2.jpg");
// 	blank2->setScale(0.3);
// 	blank2->setPosition(365, 590);
// 	this->addChild(blank2);
// 	Sprite* blank2_locked = Sprite::createWithSpriteFrameName("locked.png");
// 	blank2_locked->setPosition(365, 590);
// 	this->addChild(blank2_locked);
// 
// 	Sprite* blank3 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
// 	blank3->setScale(0.3);
// 	blank3->setPosition(565, 590);
// 	this->addChild(blank3);
// 	Sprite* blank3_locked = Sprite::createWithSpriteFrameName("locked.png");
// 	blank3_locked->setPosition(565, 590);
// 	this->addChild(blank3_locked);

// 	Sprite* blank4 = Sprite::createWithSpriteFrameName("img_bg_4.jpg");
// 	blank4->setScale(0.3);
// 	blank4->setPosition(165, 390);
// 	this->addChild(blank4);
// 	Sprite* blank4_locked = Sprite::createWithSpriteFrameName("locked.png");
// 	blank4_locked->setPosition(165, 390);
// 	this->addChild(blank4_locked);
// 
// 	Sprite* blank5 = Sprite::createWithSpriteFrameName("img_bg_5.jpg");
// 	blank5->setScale(0.3);
// 	blank5->setPosition(365, 390);
// 	this->addChild(blank5);
// 	Sprite* blank5_locked = Sprite::createWithSpriteFrameName("locked.png");
// 	blank5_locked->setPosition(365, 390);
// 	this->addChild(blank5_locked);
// 
// 	Sprite* blank6 = Sprite::createWithSpriteFrameName("blank.png");
// 	blank6->setPosition(565, 390);
// 	blank6->setScale(0.6);
// 	this->addChild(blank6);
// 	Sprite* blank6_locked = Sprite::createWithSpriteFrameName("locked.png");
// 	blank6_locked->setPosition(565, 390);
// 	this->addChild(blank6_locked);

// 	TTFConfig ttfConfig("fonts/SIMLI.TTF", 50);
// 
// 	Label* titleLabel = Label::createWithTTF(ttfConfig, "ChoseCheckPoint", TextHAlignment::CENTER);
// 	titleLabel->enableShadow();
// 	titleLabel->setColor(Color3B(255, 201, 37));
// 	titleLabel->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height - 250);
// 	this->addChild(titleLabel);
	return true;
}

void SelectBackgroundLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}

void SelectBackgroundLayer::selectCheckPoint_1(Ref* pSender){

	UserDefault::getInstance()->setIntegerForKey("CheckPoint", 1);
	UserDefault::getInstance()->setIntegerForKey("ISBoss", 1);

	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}
void SelectBackgroundLayer::selectCheckPoint_2(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("CheckPoint", 2);
	UserDefault::getInstance()->setIntegerForKey("ISBoss", 2);
	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}
void SelectBackgroundLayer::selectCheckPoint_3(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("CheckPoint", 3);
	UserDefault::getInstance()->setIntegerForKey("ISBoss", 3);
	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void SelectBackgroundLayer::selectCheckPoint_4(Ref* pSender){
	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", true);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void SelectBackgroundLayer::selectCheckPoint_5(Ref* pSender){
	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", true);
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}