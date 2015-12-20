

#include "GameBackgroundLayerEndless.h"

USING_NS_CC;

const float backgroundMoveSpeed = 1;

bool GameBackgroundLayerEndless::init(){
	background1 = Sprite::createWithSpriteFrameName("img_bg_2.jpg");
	background1->setAnchorPoint(Point(0, 0));
	background1->setScale(2);
	this->addChild(background1);

	background2 = Sprite::createWithSpriteFrameName("img_bg_2.jpg");
	background2->setAnchorPoint(Point(0, 0));
	background2->setScale(2);
	this->addChild(background2);

	winSize = Director::getInstance()->getWinSize();

	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->addGameSceneEffect();

	scheduleUpdate();
	//this->schedule(schedule_selector(GameBackgroundLayer::addCloud), UserDefault::getInstance()->getFloatForKey("intervalOfAddCloud"));
	//this->addCloud(0.5);
	return true;
}

void GameBackgroundLayerEndless::update(float useless){
	background1->setPositionY(background1->getPositionY() - backgroundMoveSpeed);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height * 2 - 1);
	if (background2->getPositionY() < 0){
		background1->setPositionY(0);
	}
}

/*void GameBackgroundLayer::addCloud(float useless){
Sprite* cloud;
if(CCRANDOM_0_1() < 0.5){
cloud = Sprite::createWithSpriteFrameName("cloud1.png");
}else{
cloud = Sprite::createWithSpriteFrameName("cloud2.png");
}
int randomX = CCRANDOM_0_1()*winSize.width;
cloud->setPosition(randomX, winSize.height + cloud->getContentSize().height/2);
this->addChild(cloud);

FiniteTimeAction* cloudMove = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfCloud"), Point(randomX, - cloud->getContentSize().height/2));
FiniteTimeAction* cloudRemove = CallFuncN::create(CC_CALLBACK_1(GameBackgroundLayer::cloudMoveFinished, this));
Action* cloudAction = Sequence::create(cloudMove, cloudRemove, NULL);
cloud->runAction(cloudAction);
}*/

/*void GameBackgroundLayer::cloudMoveFinished(Node* pSender) {
Sprite* cloud = (Sprite*) pSender;
this->removeChild(cloud, true);
}*/
