#include "gameHelpBackgroud.h"

USING_NS_CC;

gameHelpBackgroud::gameHelpBackgroud():helpSprie1(nullptr),helpSprie2(nullptr),indexHelp(1){}

bool gameHelpBackgroud::init(){

	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->myPlaneChoose();
	Scale9Sprite *background = Scale9Sprite::createWithSpriteFrameName("gameHelp.png");
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);

	MenuItemSprite* ButtonReturnItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("arrow_right.png"), Sprite::createWithSpriteFrameName("arrow_right.png"), CC_CALLBACK_1(gameHelpBackgroud::ButtonReturn, this));
	Menu* ButtonReturn = Menu::create(ButtonReturnItem, nullptr);
	//ButtonReturn->setScale(0.2f);
	ButtonReturn->setAnchorPoint(Point(0, 0));
	ButtonReturn->setPosition(30, 450);
	this->addChild(ButtonReturn);


	MenuItemSprite* ButtonChangeUpItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("arrow_right.png"), Sprite::createWithSpriteFrameName("arrow_right.png"), CC_CALLBACK_1(gameHelpBackgroud::ButtonChangeUp, this));
	Menu* ButtonChangeUpHelp = Menu::create(ButtonChangeUpItem, nullptr);
	ButtonChangeUpHelp->setScale(0.8f);
	ButtonChangeUpHelp->setRotation(180);
	ButtonChangeUpHelp->setAnchorPoint(Point(0, 0));
	ButtonChangeUpHelp->setPosition(305, 200);
	this->addChild(ButtonChangeUpHelp);

	MenuItemSprite* ButtonChangeDownItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("arrow_right.png"), Sprite::createWithSpriteFrameName("arrow_right.png"), CC_CALLBACK_1(gameHelpBackgroud::ButtonChangeDown, this));
	Menu* ButtonChangeDownHelp = Menu::create(ButtonChangeDownItem, nullptr);
	ButtonChangeDownHelp->setScale(0.8f);
	ButtonChangeDownHelp->setAnchorPoint(Point(0, 0));
	ButtonChangeDownHelp->setPosition(20, 200);
	this->addChild(ButtonChangeDownHelp);

	helpSprie1 = Sprite::createWithSpriteFrameName("help_img_1.jpg");
	helpSprie1->setPosition(Point(165, 200));
	helpSprie1->setScale(0.5f);
	this->addChild(helpSprie1);


// 	MenuItemSprite* myplane1item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("myplane1_3.png"), Sprite::createWithSpriteFrameName("myplane1_3.png"), CC_CALLBACK_1(ArmsBackGroud::myPlaneSelect1, this));
// 	Menu* myPlane1 = Menu::create(myplane1item, nullptr);
// 	myPlane1->setScale(0.5f);
// 	myPlane1->setAnchorPoint(Point(0, 0));
// 	myPlane1->setPosition(110, 300);
// 	this->addChild(myPlane1);

	return true;
}

void gameHelpBackgroud::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}

void gameHelpBackgroud::ButtonReturn(Ref* pSender){
// 	Scene* welcomeWithAnimation = TransitionMoveInL::create(1.0f, WelcomeScene::create());
// 	Director::getInstance()->replaceScene(welcomeWithAnimation);
	Director::getInstance()->popScene();
}

void gameHelpBackgroud::ButtonChangeUp(Ref* pSender){
	if (indexHelp > 8) indexHelp = 0;
	char animitionFileName[32] = { 0 };
	sprintf(animitionFileName, "help_img_%01d.jpg", ++indexHelp );
	helpSprie1->setSpriteFrame(animitionFileName);
}

void gameHelpBackgroud::ButtonChangeDown(Ref* pSender){
	if (indexHelp < 2) indexHelp = 8;
	char animitionFileName[32] = { 0 };
	sprintf(animitionFileName, "help_img_%01d.jpg", --indexHelp);
	helpSprie1->setSpriteFrame(animitionFileName);
}

