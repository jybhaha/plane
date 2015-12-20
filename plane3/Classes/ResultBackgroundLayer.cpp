#include "ResultBackgroundLayer.h"

USING_NS_CC;

bool ResultBackgroundLayer::init() {
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ResultBackgroundLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	auto background = Sprite::createWithSpriteFrameName("img_bg_welcome.jpg");
	background->setAnchorPoint(Point(0, 0));
	background->setScale(2);
	this->addChild(background);
	return true;
}

void ResultBackgroundLayer::setIsWin(bool isWin) {
	this->isWin = isWin;
}

void ResultBackgroundLayer::setScore(int score) {
	this->score = score;
	if ( UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode"))
	{	
		if (score > UserDefault::getInstance()->getIntegerForKey("BestScoreOfTheGameEndless") )
		{
			UserDefault::getInstance()->setIntegerForKey("BestScoreOfTheGameEndless", score);
			UserDefault::getInstance()->flush();
		}
		
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISOrdinaryGameMode"))
	{
		if (score > UserDefault::getInstance()->getIntegerForKey("BestScoreOfTheGame"))
		{
			UserDefault::getInstance()->setIntegerForKey("BestScoreOfTheGame", score);
			UserDefault::getInstance()->flush();
		}

	}
	else
	{
		if (score > UserDefault::getInstance()->getIntegerForKey("BestScoreOfGameAllBoss"))
		{
			UserDefault::getInstance()->setIntegerForKey("BestScoreOfTheGameAllBoss", score);
			UserDefault::getInstance()->flush();
		}
	}
}

void ResultBackgroundLayer::displayInfomation() {
	audioEffect *audioEffectTemp = nullptr;

	std::string strScore;
	std::strstream ss;
	ss << this->score;
	ss >> strScore;

	char BestScoreTemp[10];
	if (UserDefault::getInstance()->getBoolForKey("ISOrdinaryGameMode"))
	{
		sprintf(BestScoreTemp, "%05d", UserDefault::getInstance()->getIntegerForKey("BestScoreOfTheGame"));
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode")){
		sprintf(BestScoreTemp, "%05d", UserDefault::getInstance()->getIntegerForKey("BestScoreOfTheGameEndless"));
	}
	else{
		sprintf(BestScoreTemp, "%05d", UserDefault::getInstance()->getIntegerForKey("BestScoreOfTheGameAllBoss"));
	}
		

	TTFConfig ttfConfig("fonts/MarkerFelt.ttf", 30);

	scoreDisplay = Label::createWithTTF(ttfConfig, "SCORE:", TextHAlignment::LEFT);
	scoreLabel = Label::createWithTTF(ttfConfig, strScore.c_str(), TextHAlignment::CENTER);
	if (UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode"))
	{
		BestScoreDisplay = Label::createWithTTF(ttfConfig, "BEST SCORE(ENDLESS):", TextHAlignment::LEFT);
	}
	else if (UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode")){
		BestScoreDisplay = Label::createWithTTF(ttfConfig, "BEST SCORE:", TextHAlignment::LEFT);
	}
	else
		BestScoreDisplay = Label::createWithTTF(ttfConfig, "BEST SCORE(ALLBOSS):", TextHAlignment::LEFT);
		
	
	Bestscore = Label::createWithTTF(ttfConfig, BestScoreTemp, TextHAlignment::CENTER);

	if (this->isWin == true) {
		winOrLose = Label::createWithTTF(ttfConfig, "WIN!!!", TextHAlignment::CENTER);
		winOrLose->enableShadow();
		winOrLose->setColor(Color3B(255, 201, 37));
		scoreLabel->setColor(Color3B(255, 201, 37));
		Bestscore->setColor(Color3B(255, 201, 37));
		scoreDisplay->setColor(Color3B(255, 201, 37));
		BestScoreDisplay->setColor(Color3B(255, 201, 37));

		audioEffectTemp->whenPause();
	} else {
		winOrLose = Label::createWithTTF(ttfConfig, "LOSE", TextHAlignment::CENTER);
		winOrLose->enableShadow();
		winOrLose->setColor(Color3B(100, 100, 100));
		scoreLabel->setColor(Color3B(100, 100, 100));
		Bestscore->setColor(Color3B(100, 100, 100));
		scoreDisplay->setColor(Color3B(100, 100, 100));
		BestScoreDisplay->setColor(Color3B(100, 100, 100));
		
		audioEffectTemp->whenPause();
		audioEffectTemp->GameoverEffect();
	}

	winOrLose->setPosition(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height-100 );
	this->addChild(winOrLose);


	scoreDisplay->setPosition(50,  100);
	this->addChild(scoreDisplay);

	scoreLabel->setPosition(250,  100);
	this->addChild(scoreLabel);

	BestScoreDisplay->setPosition(50, 50);
	this->addChild(BestScoreDisplay);

	Bestscore->setPosition(250, 50);
	this->addChild(Bestscore);



}

void ResultBackgroundLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) {
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_BACK:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}
