#include "ControlLayer.h"

#include "GameScene.h"

USING_NS_CC;

ControlLayer::ControlLayer() :
		score(0), scoreLabel(nullptr), pauseButtonItem(nullptr),HPIndicator(nullptr),launchButton(nullptr),launchButtonItem(nullptr),pauseButton(nullptr) {
}

void ControlLayer::addScoreBy(int addScore) {
	this->score += addScore;
	this->updateScore();
	return;
}

bool ControlLayer::init() {
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ControlLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);

	scoreLabel = Label::createWithTTF("0", "fonts/MarkerFelt.ttf", 25);
	scoreLabel->setAnchorPoint(Point(0.0f, 0.0f));
	scoreLabel->setPosition(Director::getInstance()->getWinSize().width - 60, Director::getInstance()->getWinSize().height - 60);
	this->addChild(scoreLabel);

	pauseButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("pauseButton.png"), Sprite::createWithSpriteFrameName("pauseButton.png"),CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
	pauseButton = Menu::create(pauseButtonItem, nullptr);
	pauseButton->setAnchorPoint(Point(0.0f, 0.0f));
	pauseButton->setPosition(30, Director::getInstance()->getWinSize().height - 30);
	pauseButton->setScale(0.5f);
	this->addChild(pauseButton);

	Sprite* HPBottomSprite = Sprite::createWithSpriteFrameName("HPBottom.png");
	HPBottomSprite->setPosition(Director::getInstance()->getWinSize().width - 30, 30);
	HPBottomSprite->setScale(0.3f);
	this->addChild(HPBottomSprite);
	Sprite* HP = Sprite::createWithSpriteFrameName("HP.png");
	HPIndicator = ProgressTimer::create(HP);
	HPIndicator->setType(ProgressTimer::Type::RADIAL);
	HPIndicator->setPercentage(100);
	HPIndicator->setPosition(Director::getInstance()->getWinSize().width - 30, 30);//100,100
	HPIndicator->setScale(0.3f);
	addChild(HPIndicator, 0, 0);

	launchButtonItem = MenuItemSprite::create(Sprite::createWithSpriteFrameName("launchButton.png"), Sprite::createWithSpriteFrameName("launchButton.png"), Sprite::createWithSpriteFrameName("launchButtonUnable.png"), CC_CALLBACK_1(ControlLayer::menuLaunchCallback, this));
	launchButton = Menu::create(launchButtonItem, nullptr);
	launchButton->setAnchorPoint(Point(0, 0));
	launchButton->setPosition(30,30);
	launchButton->setOpacity(120);
	launchButton->setScale(0.35f);

	launchButtonItem->setEnabled(false);
	launchButton->setEnabled(false);

	this->addChild(launchButton);
	return true;
}

void ControlLayer::updateHPIndicator(){
	int HP = static_cast<PlaneUserData*>(static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getMyPlane()->getUserData())->getHP();
	int initHP = static_cast<GameScene*>(this->getParent())->getPlaneLayer()->getInitHP();
	float HPOld = HPIndicator->getPercentage();
	float HPPercentage;
	if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
	{
		HPPercentage = static_cast<float>(HP) / 500;
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
	{
		HPPercentage = static_cast<float>(HP) / 1000;
	}
	else{
		HPPercentage = static_cast<float>(HP) / 1500;
	}
	
	ProgressFromTo* animation = ProgressFromTo::create(0.2, HPOld, HPPercentage * 100);
	HPIndicator->runAction(animation);
}

void ControlLayer::updateScore() {
	std::string strScore;
	std::strstream ss;
	ss << this->score;
	ss >> strScore;
	scoreLabel->setString(strScore.c_str());
	if(this->score % 1000 == 0){
		static_cast<GameScene*>(this->getParent())->getUFOLayer()->addGiftSprite();
	}
}

void ControlLayer::menuPauseCallback(Ref* pSender) {
	audioEffect *audioEffectTemp = nullptr;
	//如果游戏已在暂停中
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("startButton.png"));
		audioEffectTemp->whenResume();
	} else {
	//如果游戏正在进行
		Director::getInstance()->pause();
		pauseButtonItem->setNormalImage(Sprite::createWithSpriteFrameName("startButton.png"));
		pauseButtonItem->setSelectedImage(Sprite::createWithSpriteFrameName("pauseButton.png"));
		audioEffectTemp->whenPause();
	}
}

void ControlLayer::menuLaunchCallback(Ref* pSender){
	launchButtonItem->setEnabled(false);
	launchButton->setEnabled(false);
	static_cast<GameScene*>(this->getParent())->getBulletLayer()->launchBigBomb();
	//发射炸弹音效
	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->MissleBlowUp();
}

void ControlLayer::setLaunchButtonEnable(){
	launchButtonItem->setEnabled(true);
	launchButton->setEnabled(true);
}

void ControlLayer::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event){
	switch (keycode) {
		case EventKeyboard::KeyCode::KEY_BACK:
			Director::getInstance()->end();
			break;
		default:
			break;
	}
}

int ControlLayer::getScore(){
	return this->score;
}



