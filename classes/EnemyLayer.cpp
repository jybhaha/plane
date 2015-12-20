#include "EnemyLayer.h"
#include "PlaneLayer.h"
#include "EnemyUserData.h"
#include "BulletLayer.h"
#include "BulletUserData.h"
#include "PlaneLayer.h"
#include "PlaneUserData.h"
#include "ControlLayer.h"
#include "ResultScene.h"
#include "GameScene.h"

USING_NS_CC;

EnemyLayer::EnemyLayer() :
		winSize(Director::getInstance()->getWinSize()),bossWarning(nullptr),bossSprite(nullptr), baseEnemyAppearProbability(UserDefault::getInstance()->getFloatForKey("probabilityOfBaseEnemyAppear")), deltaEnemyAppearProbability(UserDefault::getInstance()->getFloatForKey("probabilityOfDeltaEnemyAppear")), nowEnemyAppearProbability(baseEnemyAppearProbability), bossAppeared(false),isRandomEnemy1(true),isCollectiveWithEnemy(false) {
}

EnemyLayer::~EnemyLayer() {
}

bool EnemyLayer::init() {
	std::string name1 = "enemy1.png";
	std::string name2 = "enemy2.png";
	std::string name3 = "enemy3.png";
	std::string name4 = "enemy7.png";
	std::string name5 = "enemy5.png";
	enemyTextureName.push_back(name1);
	enemyTextureName.push_back(name2);
	enemyTextureName.push_back(name3);
	enemyTextureName.push_back(name4);
	enemyTextureName.push_back(name5);



	//添加普通敌人
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy1"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy2"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy3"));
	enemyFlyTime.push_back(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemy4"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy1"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy2"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy3"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy4"));
	enemyInitHP.push_back(UserDefault::getInstance()->getIntegerForKey("HPOfEnemy5"));

	//addEnemySprite(0);
	if (UserDefault::getInstance()->getBoolForKey("ISOrdinaryGameMode") || UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode"))
	{
		startAddEnemy();
		this->scheduleUpdate();

		bossWarning = Sprite::createWithSpriteFrameName("bossWarning.png");
		bossWarning->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2);
		bossWarning->setScale(1.5f);
		bossWarning->setOpacity(0);
		this->addChild(bossWarning, 128);

		//设置isboss为false
		isBoss = false;

		return true;
	}
	if (UserDefault::getInstance()->getBoolForKey("ISAllBossGameMode"))
	{
		startAddEnemy();
		this->scheduleUpdate();
		return true;
	}
	return true;
}

void EnemyLayer::addEnemySprite(float useless) {
	if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 1){//第一关
		float testProbability = CCRANDOM_0_1();
		if (testProbability < nowEnemyAppearProbability) {
			int randomLevel = CCRANDOM_0_1() * 100;

			if (randomLevel >= 0 && randomLevel < 30){//一种飞机走贝塞尔曲线
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[0].c_str());
				enemySprite->setScale(0.5f);
				ccBezierConfig tr0;
				if (CCRANDOM_0_1() < 0.5)
				{
					enemySprite->setPosition(Vec2(0, 450));
					tr0.controlPoint_1 = Vec2(200, 300);
					tr0.controlPoint_2 = Vec2(140, 200);
					tr0.endPosition = Vec2(0, 10);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, 90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
				else
				{
					enemySprite->setPosition(Vec2(Director::getInstance()->getWinSize().width, 450));
					tr0.controlPoint_1 = Vec2(Director::getInstance()->getWinSize().width - 200, 300);
					tr0.controlPoint_2 = Vec2(Director::getInstance()->getWinSize().width - 140, 200);
					tr0.endPosition = Vec2(Director::getInstance()->getWinSize().width , 10);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, -90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
			}
			else if (randomLevel >= 30 && randomLevel < 65 && isRandomEnemy1){
				isRandomEnemy1 = false; //防止重复产生并行的飞机

				Sprite* enemySprite1 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite2 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite3 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());

				enemySprite1->setScale(0.5f);
				enemySprite2->setScale(0.5f);
				enemySprite3->setScale(0.5f);

				//int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite1->setPosition(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100,
					winSize.height + enemySprite1->getContentSize().height);
				enemySprite2->setPosition(Director::getInstance()->getWinSize().width / 2,
					winSize.height + enemySprite2->getContentSize().height / 2);
				enemySprite3->setPosition(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100,
					winSize.height + enemySprite3->getContentSize().height);
				enemySprite1->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite2->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite3->setUserData(new EnemyUserData(enemyInitHP[1]));
				this->addChild(enemySprite1);
				this->addChild(enemySprite2);
				this->addChild(enemySprite3);
				allEnemy.pushBack(enemySprite1);
				allEnemy.pushBack(enemySprite2);
				allEnemy.pushBack(enemySprite3);

				FiniteTimeAction* enemyMove1 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100, -enemySprite1->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove1 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction1 = Sequence::create(enemyMove1, enemyRemove1, NULL);
				enemySprite1->runAction(enemyAction1);

				FiniteTimeAction* enemyMove2 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2, -enemySprite2->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove2 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction2 = Sequence::create(enemyMove2, enemyRemove2, NULL);
				enemySprite2->runAction(enemyAction2);

				FiniteTimeAction* enemyMove3 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100, -enemySprite3->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove3 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction3 = Sequence::create(enemyMove3, enemyRemove3, NULL);
				enemySprite3->runAction(enemyAction3);
			}
			else if (randomLevel >= 65 && randomLevel <= 100){
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[2].c_str());
				enemySprite->setScale(0.5f);
				int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite->setPosition(randomX, winSize.height + enemySprite->getContentSize().height / 2);
				enemySprite->setUserData(new EnemyUserData(enemyInitHP[2]));
				this->addChild(enemySprite);
				allEnemy.pushBack(enemySprite);

				FiniteTimeAction* enemyMove = MoveTo::create(enemyFlyTime[2], Point(randomX, -enemySprite->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
				enemySprite->runAction(enemyAction);
			}
		}
		nowEnemyAppearProbability += deltaEnemyAppearProbability;
		if (nowEnemyAppearProbability > 1) {
			this->stopAddEnemy();
			this->setBossWarningOn();
			this->addBossSprite();
			isBoss = true;
		}
	}

	else if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 2) //第二关
	{

		float testProbability = CCRANDOM_0_1();
		if (testProbability < nowEnemyAppearProbability){
			float randomLevel = CCRANDOM_0_1() * 100;

			if (randomLevel >= 0 && randomLevel < 30){//一种飞机走贝塞尔曲线
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[0].c_str());
				enemySprite->setScale(0.5f);
				ccBezierConfig tr0;
				if (CCRANDOM_0_1() < 0.5)
				{
					enemySprite->setPosition(Vec2(0, 450));
					tr0.controlPoint_1 = Vec2(200, 300);
					tr0.controlPoint_2 = Vec2(140, 200);
					tr0.endPosition = Vec2(0, 10);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, 90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
				else
				{
					enemySprite->setPosition(Vec2(Director::getInstance()->getWinSize().width, 450));
					tr0.controlPoint_1 = Vec2(Director::getInstance()->getWinSize().width - 200, 300);
					tr0.controlPoint_2 = Vec2(Director::getInstance()->getWinSize().width - 140, 200);
					tr0.endPosition = Vec2(Director::getInstance()->getWinSize().width , 10);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, -90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
			}
			else if (randomLevel >= 30 && randomLevel < 55 && isRandomEnemy1){
				isRandomEnemy1 = false; //防止重复产生并行的飞机

				Sprite* enemySprite1 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite2 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite3 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				enemySprite1->setScale(0.5f);
				enemySprite2->setScale(0.5f);
				enemySprite3->setScale(0.5f);

				//int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite1->setPosition(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100,
					winSize.height + enemySprite1->getContentSize().height);
				enemySprite2->setPosition(Director::getInstance()->getWinSize().width / 2,
					winSize.height + enemySprite2->getContentSize().height / 2);
				enemySprite3->setPosition(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100,
					winSize.height + enemySprite3->getContentSize().height);
				enemySprite1->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite2->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite3->setUserData(new EnemyUserData(enemyInitHP[1]));
				this->addChild(enemySprite1);
				this->addChild(enemySprite2);
				this->addChild(enemySprite3);
				allEnemy.pushBack(enemySprite1);
				allEnemy.pushBack(enemySprite2);
				allEnemy.pushBack(enemySprite3);

				FiniteTimeAction* enemyMove1 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100, -enemySprite1->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove1 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction1 = Sequence::create(enemyMove1, enemyRemove1, NULL);
				enemySprite1->runAction(enemyAction1);

				FiniteTimeAction* enemyMove2 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2, -enemySprite2->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove2 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction2 = Sequence::create(enemyMove2, enemyRemove2, NULL);
				enemySprite2->runAction(enemyAction2);

				FiniteTimeAction* enemyMove3 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100, -enemySprite3->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove3 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction3 = Sequence::create(enemyMove3, enemyRemove3, NULL);
				enemySprite3->runAction(enemyAction3);
			}
			else if (randomLevel >= 55 && randomLevel < 70){
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[2].c_str());
				enemySprite->setScale(0.5f);
				int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite->setPosition(randomX, winSize.height + enemySprite->getContentSize().height / 2);
				enemySprite->setUserData(new EnemyUserData(enemyInitHP[2]));
				this->addChild(enemySprite);
				allEnemy.pushBack(enemySprite);

				FiniteTimeAction* enemyMove = MoveTo::create(enemyFlyTime[2], Point(randomX, -enemySprite->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
				enemySprite->runAction(enemyAction);
			}
			else if (randomLevel >= 70 && randomLevel <= 100)
			{//冲向主角的敌机
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[3].c_str());
				int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite->setPosition(randomX - enemySprite->getContentSize().width / 5, winSize.height + enemySprite->getContentSize().height / 3);
				enemySprite->setUserData(new EnemyUserData(enemyInitHP[3]));
				enemySprite->setAnchorPoint(Point(0.5, 0.5));
				enemySprite->setScale(0.3f);

				float x = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().x;
				float y = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().y;
				float a = randomX - x;//winSize.width
				float b = winSize.height - y;

				float radians = atanf(a / b); //弧度转角度
				float mDegree = CC_RADIANS_TO_DEGREES(radians);
				enemySprite->setRotation(mDegree);

				this->addChild(enemySprite);
				allEnemy.pushBack(enemySprite);

				float endX = randomX - (a / b)*winSize.height;//winSize.width
				float endY = 0;

				float flyVelocity = 250;//运行速度，可以自己控制，每秒所走的像素  
				float flyLen = sqrt((winSize.width - endX)*(winSize.width - endX) + (winSize.height - endY)*(winSize.height - endY));
				float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间  

				FiniteTimeAction* enemyMove = MoveTo::create(realFlyDuration, Point(endX, endY));
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
				enemySprite->runAction(enemyAction);
			}
		}


		nowEnemyAppearProbability += deltaEnemyAppearProbability;
		if (nowEnemyAppearProbability > 1) {
			this->stopAddEnemy();
			this->setBossWarningOn();
			this->addBossSprite();
			isBoss = true;
		}
	}

	else if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 3) //第三关
	{

		float testProbability = CCRANDOM_0_1();
		if (testProbability < nowEnemyAppearProbability){
			float randomLevel = CCRANDOM_0_1() * 100;

			if (randomLevel >= 0 && randomLevel < 30){//一种飞机走贝塞尔曲线
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[0].c_str());
				enemySprite->setScale(0.5f);
				ccBezierConfig tr0;
				if (CCRANDOM_0_1() < 0.5)
				{
					enemySprite->setPosition(Vec2(0, 450));
					tr0.controlPoint_1 = Vec2(200, 300);
					tr0.controlPoint_2 = Vec2(140, 200);
					tr0.endPosition = Vec2(0, 20);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, 90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
				else
				{
					enemySprite->setPosition(Vec2(Director::getInstance()->getWinSize().width, 450));
					tr0.controlPoint_1 = Vec2(Director::getInstance()->getWinSize().width - 200, 300);
					tr0.controlPoint_2 = Vec2(Director::getInstance()->getWinSize().width - 140, 200);
					tr0.endPosition = Vec2(Director::getInstance()->getWinSize().width, 20);
					ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
					ActionInterval* forwardBy = RotateBy::create(3.f, -90);
					Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
					enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
					this->addChild(enemySprite);
					allEnemy.pushBack(enemySprite);
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

					enemySprite->runAction(sequence);
				}
			}
			else if (randomLevel >= 30 && randomLevel < 45 && isRandomEnemy1){
				isRandomEnemy1 = false; //防止重复产生并行的飞机

				Sprite* enemySprite1 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite2 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				Sprite* enemySprite3 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
				enemySprite1->setScale(0.5f);
				enemySprite2->setScale(0.5f);
				enemySprite3->setScale(0.5f);

				//int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite1->setPosition(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100,
					winSize.height + enemySprite1->getContentSize().height);
				enemySprite2->setPosition(Director::getInstance()->getWinSize().width / 2,
					winSize.height + enemySprite2->getContentSize().height / 2);
				enemySprite3->setPosition(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100,
					winSize.height + enemySprite3->getContentSize().height);
				enemySprite1->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite2->setUserData(new EnemyUserData(enemyInitHP[1]));
				enemySprite3->setUserData(new EnemyUserData(enemyInitHP[1]));
				this->addChild(enemySprite1);
				this->addChild(enemySprite2);
				this->addChild(enemySprite3);
				allEnemy.pushBack(enemySprite1);
				allEnemy.pushBack(enemySprite2);
				allEnemy.pushBack(enemySprite3);

				FiniteTimeAction* enemyMove1 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100, -enemySprite1->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove1 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction1 = Sequence::create(enemyMove1, enemyRemove1, NULL);
				enemySprite1->runAction(enemyAction1);

				FiniteTimeAction* enemyMove2 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2, -enemySprite2->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove2 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction2 = Sequence::create(enemyMove2, enemyRemove2, NULL);
				enemySprite2->runAction(enemyAction2);

				FiniteTimeAction* enemyMove3 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100, -enemySprite3->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove3 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction3 = Sequence::create(enemyMove3, enemyRemove3, NULL);
				enemySprite3->runAction(enemyAction3);
			}
			else if (randomLevel >= 45 && randomLevel < 60){
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[2].c_str());
				enemySprite->setScale(0.5f);
				int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite->setPosition(randomX, winSize.height + enemySprite->getContentSize().height / 2);
				enemySprite->setUserData(new EnemyUserData(enemyInitHP[2]));
				this->addChild(enemySprite);
				allEnemy.pushBack(enemySprite);

				FiniteTimeAction* enemyMove = MoveTo::create(enemyFlyTime[2], Point(randomX, -enemySprite->getContentSize().height / 2));
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
				enemySprite->runAction(enemyAction);
			}
			else if (randomLevel >= 60 && randomLevel <80)
			{//冲向主角的敌机
				Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[3].c_str());
				int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
				enemySprite->setPosition(randomX - enemySprite->getContentSize().width / 5, winSize.height + enemySprite->getContentSize().height / 3);
				enemySprite->setUserData(new EnemyUserData(enemyInitHP[3]));
				enemySprite->setAnchorPoint(Point(0.5, 0.5));
				enemySprite->setScale(0.3f);

				float x = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().x;
				float y = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().y;
				float a = randomX - x;//winSize.width
				float b = winSize.height - y;

				float radians = atanf(a / b); //弧度转角度
				float mDegree = CC_RADIANS_TO_DEGREES(radians);
				enemySprite->setRotation(mDegree);

				this->addChild(enemySprite);
				allEnemy.pushBack(enemySprite);

				float endX = randomX - (a / b)*winSize.height;//winSize.width
				float endY = 0;

				float flyVelocity = 250;//运行速度，可以自己控制，每秒所走的像素  
				float flyLen = sqrt((winSize.width - endX)*(winSize.width - endX) + (winSize.height - endY)*(winSize.height - endY));
				float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间  

				FiniteTimeAction* enemyMove = MoveTo::create(realFlyDuration, Point(endX, endY));
				FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
				enemySprite->runAction(enemyAction);
			}
			else if (randomLevel >= 80 && randomLevel <100)
			{
				//生成左边敌机  
				auto spritePlane1 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
				auto spritePlane2 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
				//生成边敌机  
				auto spritePlane4 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
				//auto spritePlane5 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());

				spritePlane1->setUserData(new EnemyUserData(enemyInitHP[4]));
				spritePlane2->setUserData(new EnemyUserData(enemyInitHP[3]));
				spritePlane4->setUserData(new EnemyUserData(enemyInitHP[3]));
				//spritePlane5->setUserData(new EnemyUserData(enemyInitHP[3]));


				//旋转的角度  
				spritePlane1->setRotation(-90);
				spritePlane2->setRotation(-90);

				spritePlane4->setRotation(90);
				//spritePlane5->setRotation(90);

				//设置缩放  
				spritePlane1->setScale(0.7f);
				spritePlane2->setScale(0.7f);
				spritePlane4->setScale(0.7f);
				//spritePlane5->setScale(0.7f);

				//得到精灵宽和高  
				float height = spritePlane1->getContentSize().height;
				float width = spritePlane1->getContentSize().width;

				//放置敌机位置  
				spritePlane1->setPosition(Vec2(-width / 2, winSize.height - height / 2 - 10));
				spritePlane2->setPosition(Vec2(-width / 2, spritePlane1->getPosition().y - 2 * height - 10));

				spritePlane4->setPosition(Vec2(winSize.width + width / 2, spritePlane1->getPosition().y - height - 10));
				//spritePlane5->setPosition(Vec2(winSize.width + width / 2, spritePlane4->getPosition().y - 2 * height - 10));


				//层中加入精灵  
				this->addChild(spritePlane1);
				this->addChild(spritePlane2);
				this->addChild(spritePlane4);
				//this->addChild(spritePlane5);
				allEnemy.pushBack(spritePlane1);
				allEnemy.pushBack(spritePlane2);
				allEnemy.pushBack(spritePlane4);
				//allEnemy.pushBack(spritePlane5);


				//计算飞行时间  
				float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素  
				float flyLen = winSize.width + width;
				float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间  


				//子弹运行的距离和时间，从飞机处开始运行到屏幕底部  
				auto actionMove1 = MoveBy::create(realFlyDuration, Point(flyLen, 0));
				auto actionMove2 = MoveBy::create(realFlyDuration, Point(-flyLen, 0));


				FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
				//连续动作  
				Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
				Sequence* sequence2 = Sequence::create(actionMove1->clone(), actionDone, NULL);
				Sequence* sequence4 = Sequence::create(actionMove2, actionDone, NULL);
				//Sequence* sequence5 = Sequence::create(actionMove2->clone(), actionDone, NULL);
				//飞机开始跑动  
				spritePlane1->runAction(sequence1);
				spritePlane2->runAction(sequence2);
				spritePlane4->runAction(sequence4);
				//spritePlane5->runAction(sequence5);
			}


		}



		nowEnemyAppearProbability += deltaEnemyAppearProbability;
		if (nowEnemyAppearProbability > 1) {
			this->stopAddEnemy();
			this->setBossWarningOn();
			this->addBossSprite();
			isBoss = true;
		}
	}
	
}

void EnemyLayer::addEnemySpriteEndless(float useless) {
	float randomLevel = CCRANDOM_0_1() * 100;

	if (randomLevel >= 0 && randomLevel < 30){//一种飞机走贝塞尔曲线
		Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[0].c_str());
		enemySprite->setScale(0.5f);
		ccBezierConfig tr0;
		if (CCRANDOM_0_1() < 0.5)
		{
			enemySprite->setPosition(Vec2(0, 450));
			tr0.controlPoint_1 = Vec2(200, 300);
			tr0.controlPoint_2 = Vec2(140, 200);
			tr0.endPosition = Vec2(0, 20);
			ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
			ActionInterval* forwardBy = RotateBy::create(3.f, 90);
			Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
			enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
			this->addChild(enemySprite);
			allEnemy.pushBack(enemySprite);
			FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
			Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

			enemySprite->runAction(sequence);
		}
		else
		{
			enemySprite->setPosition(Vec2(Director::getInstance()->getWinSize().width, 450));
			tr0.controlPoint_1 = Vec2(Director::getInstance()->getWinSize().width - 200, 300);
			tr0.controlPoint_2 = Vec2(Director::getInstance()->getWinSize().width - 140, 200);
			tr0.endPosition = Vec2(Director::getInstance()->getWinSize().width, 20);
			ActionInterval* bezierFoward = BezierTo::create(3.f, tr0);
			ActionInterval* forwardBy = RotateBy::create(3.f, -90);
			Spawn* spawn = Spawn::create(bezierFoward, forwardBy, NULL);
			enemySprite->setUserData(new EnemyUserData(enemyInitHP[0]));
			this->addChild(enemySprite);
			allEnemy.pushBack(enemySprite);
			FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
			Sequence* sequence = Sequence::create(spawn, enemyRemove, NULL);

			enemySprite->runAction(sequence);
		}
	}
	else if (randomLevel >= 30 && randomLevel < 45 && isRandomEnemy1){
		isRandomEnemy1 = false; //防止重复产生并行的飞机

		Sprite* enemySprite1 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
		Sprite* enemySprite2 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
		Sprite* enemySprite3 = Sprite::createWithSpriteFrameName(enemyTextureName[1].c_str());
		enemySprite1->setScale(0.5f);
		enemySprite2->setScale(0.5f);
		enemySprite3->setScale(0.5f);

		//int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
		enemySprite1->setPosition(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100,
			winSize.height + enemySprite1->getContentSize().height);
		enemySprite2->setPosition(Director::getInstance()->getWinSize().width / 2,
			winSize.height + enemySprite2->getContentSize().height / 2);
		enemySprite3->setPosition(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100,
			winSize.height + enemySprite3->getContentSize().height);
		enemySprite1->setUserData(new EnemyUserData(enemyInitHP[1]));
		enemySprite2->setUserData(new EnemyUserData(enemyInitHP[1]));
		enemySprite3->setUserData(new EnemyUserData(enemyInitHP[1]));
		this->addChild(enemySprite1);
		this->addChild(enemySprite2);
		this->addChild(enemySprite3);
		allEnemy.pushBack(enemySprite1);
		allEnemy.pushBack(enemySprite2);
		allEnemy.pushBack(enemySprite3);

		FiniteTimeAction* enemyMove1 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 - enemySprite1->getContentSize().width + 100, -enemySprite1->getContentSize().height / 2));
		FiniteTimeAction* enemyRemove1 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction1 = Sequence::create(enemyMove1, enemyRemove1, NULL);
		enemySprite1->runAction(enemyAction1);

		FiniteTimeAction* enemyMove2 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2, -enemySprite2->getContentSize().height / 2));
		FiniteTimeAction* enemyRemove2 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction2 = Sequence::create(enemyMove2, enemyRemove2, NULL);
		enemySprite2->runAction(enemyAction2);

		FiniteTimeAction* enemyMove3 = MoveTo::create(enemyFlyTime[1], Point(Director::getInstance()->getWinSize().width / 2 + enemySprite1->getContentSize().width - 100, -enemySprite3->getContentSize().height / 2));
		FiniteTimeAction* enemyRemove3 = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction3 = Sequence::create(enemyMove3, enemyRemove3, NULL);
		enemySprite3->runAction(enemyAction3);
	}
	else if (randomLevel >= 45 && randomLevel < 60){
		Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[2].c_str());
		enemySprite->setScale(0.5f);
		int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
		enemySprite->setPosition(randomX, winSize.height + enemySprite->getContentSize().height / 2);
		enemySprite->setUserData(new EnemyUserData(enemyInitHP[2]));
		this->addChild(enemySprite);
		allEnemy.pushBack(enemySprite);

		FiniteTimeAction* enemyMove = MoveTo::create(enemyFlyTime[2], Point(randomX, -enemySprite->getContentSize().height / 2));
		FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
		enemySprite->runAction(enemyAction);
	}
	else if (randomLevel >= 60 && randomLevel <80)
	{//冲向主角的敌机
		Sprite* enemySprite = Sprite::createWithSpriteFrameName(enemyTextureName[3].c_str());
		int randomX = CCRANDOM_0_1()*(winSize.width - enemySprite->getContentSize().height) + enemySprite->getContentSize().height / 2;
		enemySprite->setPosition(randomX - enemySprite->getContentSize().width/5, winSize.height + enemySprite->getContentSize().height/3);
		enemySprite->setUserData(new EnemyUserData(enemyInitHP[3]));
		enemySprite->setAnchorPoint(Point(0.5, 0.5));
		enemySprite->setScale(0.3f);

		float x = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().x;
		float y = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getPosition().y;
		float a = randomX - x;//winSize.width
		float b = winSize.height - y;

		float radians = atanf(a / b); //弧度转角度
		float mDegree = CC_RADIANS_TO_DEGREES(radians);
		enemySprite->setRotation(mDegree);

		this->addChild(enemySprite);
		allEnemy.pushBack(enemySprite);

		float endX = randomX - (a / b)*winSize.height;//winSize.width
		float endY = 0;

		float flyVelocity = 250;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = sqrt((winSize.width - endX)*(winSize.width - endX) + (winSize.height - endY)*(winSize.height - endY));
		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间  

		FiniteTimeAction* enemyMove = MoveTo::create(realFlyDuration, Point(endX, endY));
		FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		Action* enemyAction = Sequence::create(enemyMove, enemyRemove, NULL);
		enemySprite->runAction(enemyAction);
	}
	else if (randomLevel >= 80 && randomLevel <100)
	{
		//生成左边敌机  
		auto spritePlane1 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
		auto spritePlane2 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
		//生成边敌机  
		auto spritePlane4 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());
		//auto spritePlane5 = Sprite::createWithSpriteFrameName(enemyTextureName[4].c_str());

		spritePlane1->setUserData(new EnemyUserData(enemyInitHP[4]));
		spritePlane2->setUserData(new EnemyUserData(enemyInitHP[3]));
		spritePlane4->setUserData(new EnemyUserData(enemyInitHP[3]));
		//spritePlane5->setUserData(new EnemyUserData(enemyInitHP[3]));


		//旋转的角度  
		spritePlane1->setRotation(-90);
		spritePlane2->setRotation(-90);

		spritePlane4->setRotation(90);
		//spritePlane5->setRotation(90);

		//设置缩放  
		spritePlane1->setScale(0.7f);  
		spritePlane2->setScale(0.7f);  
		spritePlane4->setScale(0.7f);
		//spritePlane5->setScale(0.7f);

		//得到精灵宽和高  
		float height = spritePlane1->getContentSize().height;
		float width = spritePlane1->getContentSize().width;

		//放置敌机位置  
		spritePlane1->setPosition(Vec2(-width / 2, winSize.height - height / 2 - 10));
		spritePlane2->setPosition(Vec2(-width / 2, spritePlane1->getPosition().y - 2 * height - 10));

		spritePlane4->setPosition(Vec2(winSize.width + width / 2, spritePlane1->getPosition().y - height - 10));
		//spritePlane5->setPosition(Vec2(winSize.width + width / 2, spritePlane4->getPosition().y - 2 * height - 10));


		//层中加入精灵  
		this->addChild(spritePlane1);
		this->addChild(spritePlane2);
		this->addChild(spritePlane4);
		//this->addChild(spritePlane5);
		allEnemy.pushBack(spritePlane1);
		allEnemy.pushBack(spritePlane2);
		allEnemy.pushBack(spritePlane4);
		//allEnemy.pushBack(spritePlane5);


		//计算飞行时间  
		float flyVelocity = 200;//运行速度，可以自己控制，每秒所走的像素  
		float flyLen = winSize.width + width;
		float realFlyDuration = flyLen / flyVelocity;//实际飞行的时间  


		//子弹运行的距离和时间，从飞机处开始运行到屏幕底部  
		auto actionMove1 = MoveBy::create(realFlyDuration, Point(flyLen, 0));
		auto actionMove2 = MoveBy::create(realFlyDuration, Point(-flyLen, 0));


		FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
		//连续动作  
		Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
		Sequence* sequence2 = Sequence::create(actionMove1->clone(), actionDone, NULL);
		Sequence* sequence4 = Sequence::create(actionMove2, actionDone, NULL);
		//Sequence* sequence5 = Sequence::create(actionMove2->clone(), actionDone, NULL);
		//飞机开始跑动  
		spritePlane1->runAction(sequence1);
		spritePlane2->runAction(sequence2);
		spritePlane4->runAction(sequence4);
		//spritePlane5->runAction(sequence5);
	}
}

void EnemyLayer::addEnemyBossSprite(float useless){
	float randomBoss = CCRANDOM_0_1();
	while (!this->bossAppeared)
	{
		if (randomBoss < 0.33)
		{
			bossSprite = Sprite::createWithSpriteFrameName("enemyBoss_1.png");
			UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 1);
			bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
			bossSprite->setRotation(180);
			bossSprite->setScale(0.5f);
			bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_1")));
			this->addChild(bossSprite);
			allEnemy.pushBack(bossSprite);

			FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
			FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

			Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
			bossSprite->runAction(enemyAppearAction);

			this->bossAppeared = true;
		}
		else if (randomBoss >= 0.33 && randomBoss < 0.60)
		{
			bossSprite = Sprite::createWithSpriteFrameName("enemyBoss_2.png");
			UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 2);
			bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
			bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_1")));;
			bossSprite->setRotation(180);
			bossSprite->setScale(0.5f);
			this->addChild(bossSprite);
			allEnemy.pushBack(bossSprite);

			FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
			FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

			Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
			bossSprite->runAction(enemyAppearAction);

			this->bossAppeared = true;
		}
		else if (randomBoss >= 0.60 && randomBoss < 0.8)
		{
			UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 3);
			bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
			bossSprite->setScale(0.5f);
			bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
			bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_1")));
			this->addChild(bossSprite);
			allEnemy.pushBack(bossSprite);

			FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
			FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

			Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
			bossSprite->runAction(enemyAppearAction);

			this->bossAppeared = true;
		}
		else if (randomBoss >= 0.80 && randomBoss <= 1)
		{
			UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 4);
			bossSprite = Sprite::createWithSpriteFrameName("enemyBoss_3.png");
			bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
			bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_1")));
			bossSprite->setRotation(180);
			bossSprite->setScale(0.5f);
			this->addChild(bossSprite);
			allEnemy.pushBack(bossSprite);

			FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
			FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

			Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
			bossSprite->runAction(enemyAppearAction);

			this->bossAppeared = true;
		}
	}
}

void EnemyLayer::enemyMoveFinished(Node* pSender) {
	Sprite* enemy = (Sprite*) pSender;
	if (enemy->getTag() == 2)
	{
		isRandomEnemy1 = true;
	}
	allEnemy.eraseObject(enemy);
	delete static_cast<EnemyUserData*>(enemy->getUserData());
	this->removeChild(enemy, true);
}

void EnemyLayer::startAddEnemy() {

	if (UserDefault::getInstance()->getBoolForKey("ISOrdinaryGameMode")){
		this->schedule(schedule_selector(EnemyLayer::addEnemySprite), UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemy"));
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode")){
		this->schedule(schedule_selector(EnemyLayer::addEnemySpriteEndless), UserDefault::getInstance()->getFloatForKey("intervalOfAddEnemyEndless"));
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISAllBossGameMode")){
		this->schedule(schedule_selector(EnemyLayer::addEnemyBossSprite), UserDefault::getInstance()->getFloatForKey("intervalOfAddBoss"));
	}	
}

void EnemyLayer::stopAddEnemy() {
	this->unschedule(schedule_selector(EnemyLayer::addEnemySprite));
}

// 通关检测、碰撞检测
void EnemyLayer::update(float useless) {
	audioEffect *audioEffectTemp = nullptr;
	Animation* animationExplosion = AnimationCache::getInstance()->getAnimation("explosion");
	animationExplosion->setRestoreOriginalFrame(false);
	animationExplosion->setDelayPerUnit(0.5f / 9.0f);
	auto actionExplosion = Animate::create(animationExplosion);

	//判断是否已经通关
	if (!UserDefault::getInstance()->getBoolForKey("ISAllBossGameMode"))
	{
		if ((allEnemy.empty() == true) && (this->bossAppeared == true) ) {
		static_cast<GameScene*>(this->getParent())->getEnemyBulletLayer()->bossStopShooting();
		if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 1 || UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 2)
		{
			Sprite *loadingPic = Sprite::createWithSpriteFrameName("medal.png");
			loadingPic->setPosition(160, 200);
			loadingPic->setScale(0.5f);
			this->addChild(loadingPic, 8);
		}
		
		scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);
		}

		//遍历敌机
		for (Sprite* enemy : this->allEnemy) {
			//判断敌机是否正在爆炸
			if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {

				//for (Sprite* bullet : static_cast<GameScene*>(this->getParent())->getBulletLayer()->allBullet) {
				Vector<cocos2d::Sprite*> allBullet_1 = static_cast<GameScene*>(this->getParent())->getBulletLayer()->allBullet;
				for (Sprite* bullet : allBullet_1) {
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					//判断子弹是否与敌机碰撞，之所以要重复判断是否isDeleting是为了防止两个弹头同时命中目标会造成程序崩溃的bug

					if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false)) {

						//读取子弹的伤害，给敌机造成伤害
						if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
							enemy->stopAllActions();
							static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
							enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));

							//子弹打死敌人后音效,判断是boss还是
							if (isBoss){
								audioEffectTemp->bossExplosion();
								static_cast<GameScene*>(this->getParent())->getEnemyBulletLayer()->bossStopShooting();
								//摧毁敌机后加分
								static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(700);
							}

							else{
								audioEffectTemp->enemyExplosion();
								//摧毁敌机后加分
								static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);
							}

						}
						//end读取子弹的伤害，给敌机造成伤害

						//回收子弹

						static_cast<GameScene*>(this->getParent())->getBulletLayer()->bulletMoveFinished(bullet);

					}
					//end判断子弹是否与敌机碰撞

					//判断我方飞机是否与敌机碰撞
					if (enemy->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox())
						&& static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->getHP() > 0
						&& isCollectiveWithEnemy == false) {

						isCollectiveWithEnemy = true;//防止与同一飞机一直处于相撞状态
						//给敌机造成碰撞伤害
						if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
							enemy->stopAllActions();
							static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
							enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
							//撞毁敌机后音效
							audioEffectTemp->enemyExplosion();
							//撞毁敌机后加分
							static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);

						}//end给敌机造成碰撞伤害

						//给我方飞机造成碰撞伤害
						if (static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->isAliveUnderAttack(200) == false) {
							static_cast<GameScene*>(this->getParent())->getBulletLayer()->stopShooting();
							static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->runAction(Sequence::create(actionExplosion, NULL));
							scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);

						}
						//end给我方飞机造成碰撞伤害

						//更新HP指示器
						static_cast<GameScene*>(this->getParent())->getControlLayer()->updateHPIndicator();
					}//end判断我方飞机是否与敌机碰撞

					//当敌机与我方飞机离开时，将iscollectivewithenemy值为假
					if (!(enemy->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox()))
						){
						isCollectiveWithEnemy = false;
					}
				}
			}
			//end判断敌机是否正在爆炸
		}//end遍历敌机

		// 	//根据目前子弹数目改变当前主角外观
		// 	static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->update(useless);
		if (UserDefault::getInstance()->getIntegerForKey("levelMyPlane") == 2)
		{
			if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane1_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane2_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane3_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.5f);
			}
		}
		else if (UserDefault::getInstance()->getIntegerForKey("levelMyPlane") == 3)
		{
			if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane1_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane2_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane3_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.5f);
			}
		}
	}

	//**************************************//
	//如果是boss模式的话
	else if (UserDefault::getInstance()->getBoolForKey("ISAllBossGameMode"))
	{
// 		if ((allEnemy.empty() == true) && (this->bossAppeared == true)) {
// 			static_cast<GameScene*>(this->getParent())->getEnemyBulletLayer()->bossStopShooting();
// 			scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);
// 		}

		//遍历敌机
		for (Sprite* enemy : this->allEnemy) {
			//判断敌机是否正在爆炸
			if (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false) {

				//for (Sprite* bullet : static_cast<GameScene*>(this->getParent())->getBulletLayer()->allBullet) {
				Vector<cocos2d::Sprite*> allBullet_1 = static_cast<GameScene*>(this->getParent())->getBulletLayer()->allBullet;
				for (Sprite* bullet : allBullet_1) {
					FiniteTimeAction* enemyRemove = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::enemyMoveFinished, this));
					//判断子弹是否与敌机碰撞，之所以要重复判断是否isDeleting是为了防止两个弹头同时命中目标会造成程序崩溃的bug

					if (bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox()) && (static_cast<EnemyUserData*>(enemy->getUserData())->getIsDeleting() == false)) {

						//读取子弹的伤害，给敌机造成伤害
						if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(static_cast<BulletUserData*>(bullet->getUserData())->getDamage()) == false) {
							enemy->stopAllActions();
							static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
							enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));

							//子弹打死敌人后音效,判断是boss还是
/*							if (isBoss){*/
								audioEffectTemp->bossExplosion();
								//摧毁敌机后加分
								this->bossAppeared = false;
								static_cast<GameScene*>(this->getParent())->getEnemyBulletLayer()->bossStopShooting();
								static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(700);
/*							}*/

// 							else{
// 								audioEffectTemp->enemyExplosion();
// 								//摧毁敌机后加分
// 								static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);
// 							}

						}
						//end读取子弹的伤害，给敌机造成伤害

						//回收子弹

						static_cast<GameScene*>(this->getParent())->getBulletLayer()->bulletMoveFinished(bullet);

					}
					//end判断子弹是否与敌机碰撞

					//判断我方飞机是否与敌机碰撞
					if (enemy->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox())
						&& static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->getHP() > 0
						&& isCollectiveWithEnemy == false) {

						isCollectiveWithEnemy = true;//防止与同一飞机一直处于相撞状态
						//给敌机造成碰撞伤害
						if (static_cast<EnemyUserData*>(enemy->getUserData())->isAliveUnderAttack(400) == false) {
							enemy->stopAllActions();
							static_cast<EnemyUserData*>(enemy->getUserData())->setIsDeleting();
							enemy->runAction(Sequence::create(actionExplosion, enemyRemove, NULL));
							//撞毁敌机后音效
							audioEffectTemp->enemyExplosion();
							//撞毁敌机后加分
							static_cast<GameScene*>(this->getParent())->getControlLayer()->addScoreBy(100);

						}//end给敌机造成碰撞伤害

						//给我方飞机造成碰撞伤害
						if (static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->isAliveUnderAttack(200) == false) {
							static_cast<GameScene*>(this->getParent())->getBulletLayer()->stopShooting();
							static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->runAction(Sequence::create(actionExplosion, NULL));
							scheduleOnce(schedule_selector(EnemyLayer::changeSceneCallBack), 1.0f);

						}
						//end给我方飞机造成碰撞伤害

						//更新HP指示器
						static_cast<GameScene*>(this->getParent())->getControlLayer()->updateHPIndicator();
					}//end判断我方飞机是否与敌机碰撞

					//当敌机与我方飞机离开时，将iscollectivewithenemy值为假
					if (!(enemy->getBoundingBox().intersectsRect(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getBoundingBox()))
						){
						isCollectiveWithEnemy = false;
					}
				}
			}
			//end判断敌机是否正在爆炸
		}//end遍历敌机

		// 	//根据目前子弹数目改变当前主角外观
		// 	static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->update(useless);
		if (UserDefault::getInstance()->getIntegerForKey("levelMyPlane") == 2)
		{
			if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane1_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane2_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane3_2.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.5f);
			}
		}
		else if (UserDefault::getInstance()->getIntegerForKey("levelMyPlane") == 3)
		{
			if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane1_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
			{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane2_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.7f);
			}
			else{
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setSpriteFrame("myplane3_3.png");
				static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->setScale(0.5f);
			}
		}
	}
	
}

void EnemyLayer::addBossSprite() {
	if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 1){
		UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss",1);
		bossSprite = Sprite::createWithSpriteFrameName("enemyBoss_1.png");
		bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
		bossSprite->setRotation(180);
		bossSprite->setScale(0.5f);
		bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_1")));
		this->addChild(bossSprite);
		allEnemy.pushBack(bossSprite);

		FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
		FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

		Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
		bossSprite->runAction(enemyAppearAction);

		this->bossAppeared = true;
	}
	else if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 2)
	{
		UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 2);
		bossSprite = Sprite::createWithSpriteFrameName("enemyBoss_2.png");
		bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
		bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss_2")));
		bossSprite->setRotation(180);
		bossSprite->setScale(0.5f);
		this->addChild(bossSprite);
		allEnemy.pushBack(bossSprite);

		FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
		FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

		Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
		bossSprite->runAction(enemyAppearAction);

		this->bossAppeared = true;
	}
	else{
		UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 3);
		bossSprite = Sprite::createWithSpriteFrameName("enemyBoss.png");
		bossSprite->setPosition(winSize.width / 2, winSize.height + bossSprite->getContentSize().height);
		bossSprite->setUserData(new EnemyUserData(UserDefault::getInstance()->getIntegerForKey("HPOfEnemyBoss")));
		bossSprite->setScale(0.35f);
		this->addChild(bossSprite);
		allEnemy.pushBack(bossSprite);

		FiniteTimeAction* bossAppear = MoveTo::create(UserDefault::getInstance()->getIntegerForKey("FlytimeOfEnemyBossAppear"), Point(winSize.width / 2, winSize.height - 100 - bossSprite->getContentSize().height / 2));
		FiniteTimeAction* bossAppearDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::bossStartMove, this));

		Action* enemyAppearAction = Sequence::create(bossAppear, bossAppearDone, NULL);
		bossSprite->runAction(enemyAppearAction);

		this->bossAppeared = true;
	}
}

// 通关 / 阵亡后，调用该函数进行场景切换
void EnemyLayer::changeSceneCallBack(float useless) {
	Scene* resultSceneWithAnimation;
	if((allEnemy.empty() == true) && (this->bossAppeared == true)){//闯关模式
		if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 1)
		{
			UserDefault::getInstance()->setIntegerForKey("CheckPoint", 2);
			UserDefault::getInstance()->setIntegerForKey("ISBoss", 2);
			UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
			UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
			UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);

			Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
			
			Sleep(3000);
			Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
			Director::getInstance()->replaceScene(gameSceneWithAnimation);
		}
		else if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 2)
		{
			UserDefault::getInstance()->setIntegerForKey("CheckPoint", 3);
			UserDefault::getInstance()->setIntegerForKey("ISBoss", 3);
			UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", true);
			UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
			UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
			Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
			Sleep(3000);
			Scene* gameSceneWithAnimation = TransitionMoveInL::create(1.0f, GameScene::create());
			Director::getInstance()->replaceScene(gameSceneWithAnimation);
		}
		else if (UserDefault::getInstance()->getIntegerForKey("CheckPoint") == 3)
		{
			resultSceneWithAnimation = TransitionFlipX::create(2.0f, ResultScene::create(true, static_cast<GameScene*>(this->getParent())->getControlLayer()->getScore()));
			Director::getInstance()->replaceScene(resultSceneWithAnimation);
		}
		//resultSceneWithAnimation = TransitionFlipX::create(2.0f, ResultScene::create(true, static_cast<GameScene*>(this->getParent())->getControlLayer()->getScore()));
	}else{//无尽模式
		resultSceneWithAnimation = TransitionFlipX::create(2.0f, ResultScene::create(false, static_cast<GameScene*>(this->getParent())->getControlLayer()->getScore()));
		Director::getInstance()->replaceScene(resultSceneWithAnimation);
	}
	
}

void EnemyLayer::setBossWarningOn() {
	Sequence* sequenceFront = Sequence::create(FadeIn::create(0.5f), FadeOut::create(1.5f), FadeIn::create(0.5f), FadeOut::create(2.0f), NULL);
	//Boss warning音效
	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->warning();
	this->bossWarning->runAction(sequenceFront);
}

void EnemyLayer::bossStartMove() {
	Vector<FiniteTimeAction*> bossMoveBezier;
	for (int i = 0; i < 10; i++) {
		ccBezierConfig bezierConfig;
		bezierConfig.controlPoint_1 = Point(CCRANDOM_0_1()*winSize.width,CCRANDOM_0_1()*winSize.height);
		bezierConfig.controlPoint_2 = Point(CCRANDOM_0_1()*winSize.width,CCRANDOM_0_1()*winSize.height);
		bezierConfig.endPosition = Point(CCRANDOM_0_1()*winSize.width,winSize.height/3*2 + (CCRANDOM_0_1()*winSize.height /3 ));
		FiniteTimeAction* tempBossMoveBezier = BezierTo::create(3.0f, bezierConfig);
		bossMoveBezier.pushBack(tempBossMoveBezier);
	}
	Sequence* bossMoveSequence = Sequence::create(bossMoveBezier.at(0),bossMoveBezier.at(1),bossMoveBezier.at(2),bossMoveBezier.at(3),bossMoveBezier.at(4),bossMoveBezier.at(5),bossMoveBezier.at(6),bossMoveBezier.at(7),bossMoveBezier.at(8),bossMoveBezier.at(9),NULL);
	RepeatForever* bossMoveSequenceRepeat = RepeatForever::create(bossMoveSequence);
	bossSprite->runAction(bossMoveSequenceRepeat);

	static_cast<GameScene*>(this->getParent())->getEnemyBulletLayer()->bossStartShooting();
}

Sprite* EnemyLayer::getBossSprite(){
	return this->bossSprite;
}
