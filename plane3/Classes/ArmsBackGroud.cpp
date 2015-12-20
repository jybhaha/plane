#include "ArmsBackGroud.h"

USING_NS_CC;

bool ArmsBackGroud::init(){

	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->myPlaneChoose();
	Scale9Sprite *background = Scale9Sprite::createWithSpriteFrameName("ArmsBackground.png");
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);

	MenuItemSprite* ButtonReturnItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("arrow_right.png"), Sprite::createWithSpriteFrameName("arrow_right.png"), CC_CALLBACK_1(ArmsBackGroud::ButtonReturn, this));
	Menu* ButtonReturn = Menu::create(ButtonReturnItem, nullptr);
	//ButtonReturn->setScale(0.2f);
	ButtonReturn->setAnchorPoint(Point(0, 0));
	ButtonReturn->setPosition(30,450);
	this->addChild(ButtonReturn);


	MenuItemSprite* myplane1item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("plane1Show.png"), Sprite::createWithSpriteFrameName("plane1Show.png"), CC_CALLBACK_1(ArmsBackGroud::myPlaneSelect1, this));
	Menu* myPlane1 = Menu::create(myplane1item, nullptr);
	myPlane1->setScale(0.5f);
	myPlane1->setAnchorPoint(Point(0, 0));
	myPlane1->setPosition(50, 380);
	this->addChild(myPlane1);

	Sprite* myPlane1Atr = Sprite::createWithSpriteFrameName("myPlane1atr.png");
	myPlane1Atr->setAnchorPoint(Point(0.5, 0.5));
	myPlane1Atr->setScale(0.4);
	myPlane1Atr->setPosition(200, 380);
	this->addChild(myPlane1Atr);

	MenuItemSprite* myplane2item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("plane2Show.png"), Sprite::createWithSpriteFrameName("plane2Show.png"), CC_CALLBACK_1(ArmsBackGroud::myPlaneSelect2, this));
	Menu* myPlane2 = Menu::create(myplane2item, nullptr);
	myPlane2->setScale(0.5f);
	myPlane2->setAnchorPoint(Point(0, 0));
	myPlane2->setPosition(50, 230);
	this->addChild(myPlane2);

	Sprite* myPlane2Atr = Sprite::createWithSpriteFrameName("myPlane2atr.png");
	myPlane2Atr->setAnchorPoint(Point(0.5, 0.5));
	myPlane2Atr->setScale(0.4);
	myPlane2Atr->setPosition(200, 230);
	this->addChild(myPlane2Atr);

	MenuItemSprite* myplane3item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("plane3Show.png"), Sprite::createWithSpriteFrameName("plane3Show.png"), CC_CALLBACK_1(ArmsBackGroud::myPlaneSelect3, this));
	Menu* myPlane3 = Menu::create(myplane3item, nullptr);
	myPlane3->setScale(0.5f);
	myPlane3->setAnchorPoint(Point(0, 0));
	myPlane3->setPosition(50, 80);
	this->addChild(myPlane3);

	Sprite* myPlane3Atr = Sprite::createWithSpriteFrameName("myPlane3atr.png");
	myPlane3Atr->setAnchorPoint(Point(0.5, 0.5));
	myPlane3Atr->setScale(0.4);
	myPlane3Atr->setPosition(200, 80);
	this->addChild(myPlane3Atr);


	return true;
}

void ArmsBackGroud::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}

void ArmsBackGroud::ButtonReturn(Ref* pSender){
	Scene* selectSceneWithAnimation = TransitionMoveInL::create(1.0f, SelectScene::create());
	Director::getInstance()->replaceScene(selectSceneWithAnimation);
}

void ArmsBackGroud::myPlaneSelect1(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("MyPlaneSelect", 1);
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, SelectScene::create());
	UserDefault::getInstance()->setIntegerForKey("damageOfInitBullet", 150);
	UserDefault::getInstance()->setIntegerForKey("damageOfDeltaWhenLevelUp", 50);
	UserDefault::getInstance()->setIntegerForKey("damageOfBigBomb", 800);
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void ArmsBackGroud::myPlaneSelect2(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("MyPlaneSelect", 2);
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, SelectScene::create());
	UserDefault::getInstance()->setIntegerForKey("damageOfInitBullet", 100);
	UserDefault::getInstance()->setIntegerForKey("damageOfDeltaWhenLevelUp", 35);
	UserDefault::getInstance()->setIntegerForKey("damageOfBigBomb", 400);
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

void ArmsBackGroud::myPlaneSelect3(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("MyPlaneSelect", 3);
	UserDefault::getInstance()->setIntegerForKey("damageOfInitBullet",50);
	UserDefault::getInstance()->setIntegerForKey("damageOfDeltaWhenLevelUp", 20);
	UserDefault::getInstance()->setIntegerForKey("damageOfBigBomb", 200);
	Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, SelectScene::create());
	Director::getInstance()->replaceScene(gameSceneWithAnimation);
}

