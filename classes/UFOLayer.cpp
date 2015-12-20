
#include "UFOLayer.h"

#include "ControlLayer.h"
#include "UFOUserData.h"
#include "BulletLayer.h"
#include "GameScene.h"

USING_NS_CC;

UFOLayer::UFOLayer() :
		winSize(Director::getInstance()->getWinSize()), sequenceBack(nullptr), sequenceFront(nullptr) {
}

bool UFOLayer::init() {
	std::string name1 = "bigBombGet.png";		// Kind 0
	std::string name2 = "bulletUpgrade.png";	// Kind 1
	std::string name3 = "MoreBullet.png";       //kind 2
	std::string name4 = "blood.png";            //kind3
	giftTextureName.push_back(name1);
	giftTextureName.push_back(name2);
	giftTextureName.push_back(name3);
	giftTextureName.push_back(name4);

	giftFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfGiftBigBomb"));
	giftFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfGiftLevelUp"));
	giftFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfGiftMoreBullet"));
	giftFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfGiftBlood"));
	this->scheduleUpdate();
	return true;
}

void UFOLayer::addGiftSprite() {
	float testProbability = CCRANDOM_0_1();
	int giftKinds ;
	if (testProbability < 0.3) {
		giftKinds = 0;
	}
	else if (testProbability >= 0.3 && testProbability < 0.6){
		giftKinds = 1;
	}
	else if (testProbability >= 0.6 && testProbability < 0.8){
		giftKinds = 2;
	}
	else{
		giftKinds = 3;
	}
	Sprite* giftSprite = Sprite::createWithSpriteFrameName(giftTextureName[giftKinds].c_str());
	int randomX = CCRANDOM_0_1()*winSize.width;
	giftSprite->setPosition(randomX, winSize.height +giftSprite->getContentSize().height/2 );
	giftSprite->setUserData(new UFOUserData(giftKinds));

	if (giftKinds == 2){
		giftSprite->setScale(1.0f);
	}
		
	else if (giftKinds == 3){
		giftSprite->setScale(0.3f);
	}	
	else
	{
		giftSprite->setScale(0.5f);
	}
	this->addChild(giftSprite);
	allGift.pushBack(giftSprite);

	FiniteTimeAction* giftMove = MoveTo::create(giftFlyTime[giftKinds], Point(randomX, - giftSprite->getContentSize().height/2));
	FiniteTimeAction* giftRemove = CallFuncN::create(CC_CALLBACK_1(UFOLayer::giftMoveFinished, this));
	Action* giftAction = Sequence::create(giftMove, giftRemove, NULL);
	giftSprite->runAction(giftAction);
}

void UFOLayer::giftMoveFinished(Node* pSender) {
	Sprite* gift = (Sprite*) pSender;
	delete static_cast<UFOUserData*>(gift->getUserData());
	allGift.eraseObject(gift);	
	this->removeChild(gift, true);
}

void UFOLayer::update(float useless) {

	audioEffect *audioEffectTemp = nullptr;

	for (Sprite* gift : this->allGift) {
	
		//判断我方飞机是否与gift碰撞		
		if (gift->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox())) {
		
			if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 0) {
				static_cast<GameScene*>(this->getParent())->getControlLayer()->setLaunchButtonEnable();
				audioEffectTemp->gainMissile();
				if (allGift.empty())
				{
					break;
				}
			}
			else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 1){
				static_cast<GameScene*>(this->getParent())->getBulletLayer()->setBulletLevelUP();
				audioEffectTemp->gainBulletLevelUp();
				if (allGift.empty())
				{
					break;
				}
			}
			else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 2){
				static_cast<GameScene*>(this->getParent())->getBulletLayer()->setBulletNumUp();
				if (allGift.empty())
				{
					break;
				}
			}
			else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 3)
			{
				static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->addBlood(100);
				static_cast<GameScene*>(this->getParent())->getControlLayer()->updateHPIndicator();
				if (allGift.empty())
				{
					break;
				}
			}
			this->showAnnotation(gift);
			this->giftMoveFinished(gift);
// 			if (allGift.empty())
// 			{
// 				break;
// 			}
			break;
		}		
		//end判断我方飞机是否与gift碰撞

	}

}

void UFOLayer::showAnnotation(Sprite* gift) {
	Sprite* GiftAnnotation1;
	Sprite* GiftAnnotation2;
	if(static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 0){
		GiftAnnotation1 = Sprite::createWithSpriteFrameName("getBigBomb1.png");
		GiftAnnotation2 = Sprite::createWithSpriteFrameName("getBigBomb2.png");
	}
	else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 1){
		GiftAnnotation1 = Sprite::createWithSpriteFrameName("bulletLevelUp1.png");
		GiftAnnotation2 = Sprite::createWithSpriteFrameName("bulletLevelUp2.png");
	}
	else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 2)
	{
		GiftAnnotation1 = Sprite::createWithSpriteFrameName("getMoreBullet1.png");
		GiftAnnotation2 = Sprite::createWithSpriteFrameName("getMoreBullet2.png");
	}
	else if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 3)
	{
		GiftAnnotation1 = Sprite::createWithSpriteFrameName("addBlood1.png");
		GiftAnnotation2 = Sprite::createWithSpriteFrameName("addBlood2.png");
	}
	sequenceFront = Sequence::create(FadeIn::create(0.5f), FadeOut::create(2.0f), NULL);
	sequenceBack = Sequence::create(FadeIn::create(1.0f), FadeOut::create(3.0f), NULL);
	GiftAnnotation1->setPosition(gift->getPosition());
	if (static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 2 || static_cast<UFOUserData*>(gift->getUserData())->getGiftKind() == 3)
	{
		GiftAnnotation1->setScale(0.5f);
		GiftAnnotation2->setScale(0.5f);
	}
	else {
		GiftAnnotation1->setScale(0.5f);
		GiftAnnotation2->setScale(0.5f);
	}
	
	GiftAnnotation1->setOpacity(0);
	GiftAnnotation2->setPosition(gift->getPosition());
	GiftAnnotation2->setOpacity(0);
	this->addChild(GiftAnnotation1);
	this->addChild(GiftAnnotation2);
	GiftAnnotation1->runAction(sequenceFront);
	GiftAnnotation2->runAction(sequenceBack);
}
