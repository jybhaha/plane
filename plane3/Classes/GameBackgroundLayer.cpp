#include "GameBackgroundLayer.h"

USING_NS_CC;

const float backgroundMoveSpeed = 1;

bool GameBackgroundLayer::init(){
	audioEffect *audioEffectTemp = nullptr;
	if (UserDefault::getInstance()->getBoolForKey("ISOrdinaryGameMode"))
	{
		audioEffectTemp->addGameScene();
		switch (UserDefault::getInstance()->getIntegerForKey("CheckPoint"))
		{
		case 1:
			background1 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
			background1->setAnchorPoint(Point(0, 0));
			background1->setScale(2);
			this->addChild(background1);

			background2 = Sprite::createWithSpriteFrameName("img_bg_1.jpg");
			background2->setAnchorPoint(Point(0, 0));
			background2->setScale(2);
			this->addChild(background2);
			break;
		case 2:
			background1 = Sprite::createWithSpriteFrameName("img_bg_2.jpg");
			background1->setAnchorPoint(Point(0, 0));
			background1->setScale(2);
			this->addChild(background1);

			background2 = Sprite::createWithSpriteFrameName("img_bg_2.jpg");
			background2->setAnchorPoint(Point(0, 0));
			background2->setScale(2);
			this->addChild(background2);
			break;
		case 3:
			background1 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
			background1->setAnchorPoint(Point(0, 0));
			background1->setScale(2);
			this->addChild(background1);

			background2 = Sprite::createWithSpriteFrameName("img_bg_3.jpg");
			background2->setAnchorPoint(Point(0, 0));
			background2->setScale(2);
			this->addChild(background2);
			break;

		}
	
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode")){
		background1 = Sprite::createWithSpriteFrameName("img_bg_4.jpg");
		background1->setAnchorPoint(Point(0, 0));
		background1->setScale(2);
		this->addChild(background1);

		background2 = Sprite::createWithSpriteFrameName("img_bg_4.jpg");
		background2->setAnchorPoint(Point(0, 0));
		background2->setScale(2);
		this->addChild(background2);
		//ÒôÐ§
		audioEffectTemp->addEndlessGameMode();
	}
	else
	{
		audioEffectTemp->addBossGameMode();
		background1 = Sprite::createWithSpriteFrameName("img_bg_5.jpg");
		background1->setAnchorPoint(Point(0, 0));
		background1->setScale(2);
		this->addChild(background1);

		background2 = Sprite::createWithSpriteFrameName("img_bg_5.jpg");
		background2->setAnchorPoint(Point(0, 0));
		background2->setScale(2);
		this->addChild(background2);
	}


	winSize = Director::getInstance()->getWinSize();



	scheduleUpdate();
	return true;
}

void GameBackgroundLayer::update(float useless){
	background1->setPositionY(background1->getPositionY() - backgroundMoveSpeed);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height*2 - 1);
	if(background2->getPositionY() < 0){
		background1->setPositionY(0);
	}
}

