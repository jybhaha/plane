#include "BulletLayer.h"
#include "PlaneLayer.h"
#include "BulletUserData.h"
#include "GameScene.h"

USING_NS_CC;

BulletLayer::BulletLayer() :
eachBulletDamage(UserDefault::getInstance()->getIntegerForKey("damageOfInitBullet")), nowBulletLevel(0), BulletNum(1) {
}

BulletLayer::~BulletLayer() {
}

bool BulletLayer::init() {
	if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
	{
		bulletTextureName.push_back("myPlane1_bullet1.png");
		bulletTextureName.push_back("myPlane1_bullet2.png");
		bulletTextureName.push_back("myPlane1_bullet3.png");
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane1_bullet1.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane1_bullet2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane1_bullet3.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBomb1.png")->getTexture()));	//定义大招层
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb3.png")->getTexture()));
		this->addChild(bulletBatchNodeVector[0]);
		this->addChild(bulletBatchNodeVector[1]);
		this->addChild(bulletBatchNodeVector[2]);
		this->addChild(bulletBatchNodeVector[3]);	//大招层
		this->addChild(bulletBatchNodeVector[4]);
		this->addChild(bulletBatchNodeVector[5]);
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
	{
		bulletTextureName.push_back("myPlane2_bullet1.png");
		bulletTextureName.push_back("myPlane2_bullet2.png");
		bulletTextureName.push_back("myPlane2_bullet3.png");
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane2_bullet1.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane2_bullet2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane2_bullet3.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBomb1.png")->getTexture()));	//定义大招层
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb3.png")->getTexture()));
		this->addChild(bulletBatchNodeVector[0]);
		this->addChild(bulletBatchNodeVector[1]);
		this->addChild(bulletBatchNodeVector[2]);
		this->addChild(bulletBatchNodeVector[3]);	//大招层
		this->addChild(bulletBatchNodeVector[4]);
		this->addChild(bulletBatchNodeVector[5]);
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 3)
	{
		bulletTextureName.push_back("myPlane3_bullet1.png");
		bulletTextureName.push_back("myPlane3_bullet2.png");
		bulletTextureName.push_back("myPlane3_bullet3.png");
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane3_bullet1.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane3_bullet2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("myPlane3_bullet3.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigBomb1.png")->getTexture()));	//定义大招层
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb2.png")->getTexture()));
		bulletBatchNodeVector.push_back(SpriteBatchNode::createWithTexture(SpriteFrameCache::getInstance()->getSpriteFrameByName("BigBomb3.png")->getTexture()));
		this->addChild(bulletBatchNodeVector[0]);
		this->addChild(bulletBatchNodeVector[1]);
		this->addChild(bulletBatchNodeVector[2]);
		this->addChild(bulletBatchNodeVector[3]);	//大招层
		this->addChild(bulletBatchNodeVector[4]);
		this->addChild(bulletBatchNodeVector[5]);
	}



	this->startShooting(BulletNum);
	return true;
}

void BulletLayer::HeroBulletOne(float useless) {
	/*
	/每次发射一个子弹
	*/
	Sprite* bullet = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	Point planePosition = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getPosition();

	Point bulletPosition = Point(planePosition.x, planePosition.y + 
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);

	bullet->setPosition(bulletPosition);
	bullet->setUserData(new BulletUserData(eachBulletDamage, nowBulletLevel));
	bullet->setScale(0.5f);
	allBullet.pushBack(bullet);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet);

	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition.y + (bullet->getContentSize().height / 2);
	float bulletFlySpeed = 900 / 1;
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bulletPosition.x, Director::getInstance()->getWinSize().height + bullet->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));
	//添加fire音效
	audioEffectTemp->addFireEffect();

	auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
	bullet->runAction(bulleAction);
}

void BulletLayer::HeroBulletTwo(float useless){
	/*
	/每次发射两个子弹
	*/
	Sprite* bullet1 = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	Sprite* bullet2 = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	bullet1->setScale(0.5f);
	bullet2->setScale(0.5f);
	Point planePosition = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getPosition();

	Point bulletPosition1 = Point(planePosition.x - 25, planePosition.y +
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);
	Point bulletPosition2 = Point(planePosition.x + 25, planePosition.y +
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);

	bullet1->setPosition(bulletPosition1);
	bullet1->setUserData(new BulletUserData(eachBulletDamage * 0.7, nowBulletLevel));
	bullet2->setPosition(bulletPosition2);
	bullet2->setUserData(new BulletUserData(eachBulletDamage * 0.7, nowBulletLevel));
	allBullet.pushBack(bullet1);
	allBullet.pushBack(bullet2);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet1);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet2);

	//设置子弹飞行时间
	float bulletFlyLenth = Director::getInstance()->getWinSize().height - bulletPosition1.y + (bullet1->getContentSize().height / 2);
	float bulletFlySpeed = 900 / 1;
	float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

	FiniteTimeAction* bulletMove1 = MoveTo::create(bulletFltTime, Point(bulletPosition1.x, Director::getInstance()->getWinSize().height + bullet1->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove1 = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	FiniteTimeAction* bulletMove2 = MoveTo::create(bulletFltTime, Point(bulletPosition2.x, Director::getInstance()->getWinSize().height + bullet2->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove2 = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	//添加fire音效
	audioEffectTemp->addFireEffect();

	auto bulleAction1 = Sequence::create(bulletMove1, bulletRemove1, NULL);
	bullet1->runAction(bulleAction1);

	auto bulleAction2 = Sequence::create(bulletMove2, bulletRemove2, NULL);
	bullet2->runAction(bulleAction2);

}

void BulletLayer::HeroBulletThree(float useless){
	/*
	/每次发射三个子弹
	*/
	double angle = M_PI * 6 / 180;//旋轉的角度 
	Sprite* bullet1 = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	Sprite* bullet2 = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	Sprite* bullet3 = Sprite::createWithSpriteFrameName(bulletTextureName[nowBulletLevel]);
	bullet1->setScale(0.5f);
	bullet2->setScale(0.5f);
	bullet3->setScale(0.5f);

	bullet1->setRotation(angle);
	bullet3->setRotation(-angle);

	Point planePosition = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getPosition();

	Point bulletPosition1 = Point(planePosition.x - 20, planePosition.y +
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);
	Point bulletPosition2 = Point(planePosition.x, planePosition.y +
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);
	Point bulletPosition3 = Point(planePosition.x + 20, planePosition.y +
		static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getChildByName("PLANE")->getContentSize().height);

	bullet1->setPosition(bulletPosition1);
	bullet1->setUserData(new BulletUserData(eachBulletDamage * 0.7, nowBulletLevel));
	bullet2->setPosition(bulletPosition2);
	bullet2->setUserData(new BulletUserData(eachBulletDamage * 0.7, nowBulletLevel));
	bullet3->setPosition(bulletPosition3);
	bullet3->setUserData(new BulletUserData(eachBulletDamage * 0.7, nowBulletLevel));

	allBullet.pushBack(bullet1);
	allBullet.pushBack(bullet2);
	allBullet.pushBack(bullet3);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet1);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet2);
	this->bulletBatchNodeVector[nowBulletLevel]->addChild(bullet3);

	auto planeHeight = Director::getInstance()->getWinSize().height - bulletPosition2.y + (bullet2->getContentSize().height) / 2;
	//设置子弹飞行时间
	float bulletFlyLenth1 = planeHeight / cos(angle);
	float bulletFlyLenth2 = planeHeight;
	float bulletFlyLenth3 = planeHeight / cos(angle);
	float bulletFlySpeed = 850 / 1;
	float bulletFltTime1 = bulletFlyLenth1 / bulletFlySpeed;
	float bulletFltTime2 = bulletFlyLenth2 / bulletFlySpeed;
	float bulletFltTime3 = bulletFlyLenth3 / bulletFlySpeed;

	//FiniteTimeAction* bulletMove1 = MoveTo::create(bulletFltTime1, Point(bulletPosition1.x, Director::getInstance()->getWinSize().height + bullet1->getContentSize().height / 2));
	FiniteTimeAction* bulletMove1 = MoveTo::create(bulletFltTime1, Point(bulletPosition1.x - planeHeight * tan(angle), Director::getInstance()->getWinSize().height + bullet1->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove1 = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	FiniteTimeAction* bulletMove2 = MoveTo::create(bulletFltTime2, Point(bulletPosition2.x, Director::getInstance()->getWinSize().height + bullet2->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove2 = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

	FiniteTimeAction* bulletMove3 = MoveTo::create(bulletFltTime3, Point(bulletPosition3.x + planeHeight * tan(angle), Director::getInstance()->getWinSize().height + bullet3->getContentSize().height / 2));
	FiniteTimeAction* bulletRemove3 = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));
	//添加fire音效
	audioEffectTemp->addFireEffect();

	auto bulleAction1 = Sequence::create(bulletMove1, bulletRemove1, NULL);
	bullet1->runAction(bulleAction1);

	auto bulleAction2 = Sequence::create(bulletMove2, bulletRemove2, NULL);
	bullet2->runAction(bulleAction2);

	auto bulleAction3 = Sequence::create(bulletMove3, bulletRemove3, NULL);
	bullet3->runAction(bulleAction3);

}

void BulletLayer::bulletMoveFinished(Node* pSender) {
	Sprite* bullet = static_cast<Sprite*>(pSender);
	BulletUserData* bulletUserData = static_cast<BulletUserData*>(bullet->getUserData());
	int bulletLevel = bulletUserData->getBulletLevel();
	delete bulletUserData;
	allBullet.eraseObject(bullet);
	this->bulletBatchNodeVector[bulletLevel]->removeChild(bullet, true);
}

// void BulletLayer::bigBombMoveFinished(Node* pSender){
// 	Sprite* bullet = static_cast<Sprite*>(pSender);
// 	BulletUserData* bulletUserData = static_cast<BulletUserData*>(bullet->getUserData());
// 	delete bulletUserData;
// 	allBullet.eraseObject(bullet);
// 	if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
// 		this->bulletBatchNodeVector[3]->removeChild(bullet, true);
// 	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
// 		this->bulletBatchNodeVector[4]->removeChild(bullet, true);
// 	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 3)
// 		this->bulletBatchNodeVector[5]->removeChild(bullet, true);
// }

void BulletLayer::startShooting(int BulletNum) {
	switch (BulletNum)
	{
	case 1:
		this->schedule(schedule_selector(BulletLayer::HeroBulletOne), UserDefault::getInstance()->getFloatForKey("intervalOfAddBullet"));
		UserDefault::getInstance()->setIntegerForKey("levelMyPlane", 1);
		break;
	case 2:
		stopShooting();
		this->schedule(schedule_selector(BulletLayer::HeroBulletTwo), UserDefault::getInstance()->getFloatForKey("intervalOfAddBullet"));
		UserDefault::getInstance()->setIntegerForKey("levelMyPlane", 2);
		break;
	case 3:
		stopShooting();
		this->schedule(schedule_selector(BulletLayer::HeroBulletThree), UserDefault::getInstance()->getFloatForKey("intervalOfAddBullet"));
		UserDefault::getInstance()->setIntegerForKey("levelMyPlane", 3);
		break;
	}
	
	

}

void BulletLayer::stopShooting() {
	switch (BulletNum)
	{
	case 1:
		break;
	case 2:
		this->unschedule(schedule_selector(BulletLayer::HeroBulletOne));
		break;
	case 3:
		this->unschedule(schedule_selector(BulletLayer::HeroBulletTwo));
		break;
	default:
		break;
	}
	this->unschedule(schedule_selector(BulletLayer::HeroBulletOne));
}



void BulletLayer::setBulletLevelUP() {

	if (nowBulletLevel < 2) {
		this->nowBulletLevel += 1;
		this->eachBulletDamage += UserDefault::getInstance()->getIntegerForKey("damageOfDeltaWhenLevelUp");
	}
	
}
void BulletLayer::setBulletNumUp(){
	if (BulletNum < 3){
		this->BulletNum += 1;
		startShooting(BulletNum);
	}
}
void BulletLayer::launchBigBomb() {
	if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") ==1){
		for (int i = 0; i < Director::getInstance()->getWinSize().width + Sprite::createWithSpriteFrameName("bigBomb1.png")->getContentSize().width /2; i += Sprite::createWithSpriteFrameName("bigBomb1.png")->getContentSize().width/2){
			Sprite* bigBomb = Sprite::createWithSpriteFrameName("bigBomb1.png");
			bigBomb->setScale(0.5f);
			bigBomb->setPosition(i + bigBomb->getContentSize().width / 2, -bigBomb->getContentSize().height / 2);
			bigBomb->setUserData(new BulletUserData(UserDefault::getInstance()->getIntegerForKey("damageOfBigBomb"), 3));
			allBullet.pushBack(bigBomb);
			this->bulletBatchNodeVector[3]->addChild(bigBomb);

			float bulletFlyLenth = Director::getInstance()->getWinSize().height - bigBomb->getPositionY() + (bigBomb->getContentSize().height / 2);
			float bulletFlySpeed = 1000 / 1; //1000
			float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

			FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bigBomb->getPositionX(), Director::getInstance()->getWinSize().height + bigBomb->getContentSize().height / 2));
			FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

			auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
			bigBomb->runAction(bulleAction);
		}
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
	{
		for (int i = 0; i < Director::getInstance()->getWinSize().width + Sprite::createWithSpriteFrameName("BigBomb2.png")->getContentSize().width / 4; i += Sprite::createWithSpriteFrameName("BigBomb2.png")->getContentSize().width / 4){
			Sprite* bigBomb = Sprite::createWithSpriteFrameName("BigBomb2.png");
			//bigBomb->setPosition(i, - bigBomb->getContentSize().height /2);
			bigBomb->setPosition(i + bigBomb->getContentSize().width / 2-40, -bigBomb->getContentSize().height / 2);
			bigBomb->setScale(0.5f);
			bigBomb->setUserData(new BulletUserData(UserDefault::getInstance()->getIntegerForKey("damageOfBigBomb"), 4));
			allBullet.pushBack(bigBomb);
			this->bulletBatchNodeVector[4]->addChild(bigBomb);

			float bulletFlyLenth = Director::getInstance()->getWinSize().height - bigBomb->getPositionY() + (bigBomb->getContentSize().height / 2);
			float bulletFlySpeed = 1000 / 1; //1000
			float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

			FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bigBomb->getPositionX(), Director::getInstance()->getWinSize().height + bigBomb->getContentSize().height / 2));
			FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

			auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
			bigBomb->runAction(bulleAction);
		}
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 3)
	{
		for (int i = 0; i < Director::getInstance()->getWinSize().width + Sprite::createWithSpriteFrameName("BigBomb3.png")->getContentSize().width/2; i += Sprite::createWithSpriteFrameName("BigBomb3.png")->getContentSize().width/2){
			Sprite* bigBomb = Sprite::createWithSpriteFrameName("BigBomb3.png");
			//bigBomb->setPosition(i, - bigBomb->getContentSize().height /2);
			bigBomb->setPosition(i + bigBomb->getContentSize().width / 2, -bigBomb->getContentSize().height / 2);
			bigBomb->setScale(1.5f);
			bigBomb->setUserData(new BulletUserData(UserDefault::getInstance()->getIntegerForKey("damageOfBigBomb"), 5));
			allBullet.pushBack(bigBomb);
			this->bulletBatchNodeVector[5]->addChild(bigBomb);

			float bulletFlyLenth = Director::getInstance()->getWinSize().height - bigBomb->getPositionY() + (bigBomb->getContentSize().height / 2);
			float bulletFlySpeed = 1000 / 1; //1000
			float bulletFltTime = bulletFlyLenth / bulletFlySpeed;

			FiniteTimeAction* bulletMove = MoveTo::create(bulletFltTime, Point(bigBomb->getPositionX(), Director::getInstance()->getWinSize().height + bigBomb->getContentSize().height / 2));
			FiniteTimeAction* bulletRemove = CallFuncN::create(CC_CALLBACK_1(BulletLayer::bulletMoveFinished, this));

			auto bulleAction = Sequence::create(bulletMove, bulletRemove, NULL);
			bigBomb->runAction(bulleAction);
		}
	}
	
}


