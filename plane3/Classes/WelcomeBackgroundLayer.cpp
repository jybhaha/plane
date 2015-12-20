
#include "WelcomeBackgroundLayer.h"

USING_NS_CC;

bool WelcomeBackgroundLayer::init() {
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(WelcomeBackgroundLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);


	Scale9Sprite *background = Scale9Sprite::createWithSpriteFrameName("img_bg_welcome.jpg");//
	background->setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
	background->setAnchorPoint(Point(0, 0));
	this->addChild(background);

	Sprite* logo = Sprite::createWithSpriteFrameName("logo.png");
	logo->setAnchorPoint(Point(0.5, 0.5));
	logo->setScale(0.25f);
	logo->setPosition(Director::getInstance()->getWinSize().width / 2, 330);
	this->addChild(logo);
	Sprite* logo1 = Sprite::createWithSpriteFrameName("logo1.png");
	logo1->setAnchorPoint(Point(0.5, 0.5));
	logo1->setScale(1.3f);
	logo1->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height-30);
	this->addChild(logo1);

	audioEffect *audioTemp = nullptr;
	audioTemp->addWelcomSceneEffect();

	return true;
}

void WelcomeBackgroundLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
