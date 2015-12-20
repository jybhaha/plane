

#include "WelcomeButtonLayer.h"

USING_NS_CC;

WelcomeButtonLayer::WelcomeButtonLayer():buttonSoundOff(nullptr),buttonSoundOn(nullptr),setting(false){}

bool WelcomeButtonLayer::init() {
	MenuItemSprite* startGameButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("startGameButton.png"), Sprite::createWithSpriteFrameName("startGameButton.png"), CC_CALLBACK_1(WelcomeButtonLayer::startGameButtonCallback, this));
	Menu* startGameButton = Menu::create(startGameButtonItemSprite, nullptr);
	startGameButton->setAnchorPoint(Point(0.0f, 0.5f));
	startGameButton->setScale(0.5f);
	startGameButton->setPosition(Director::getInstance()->getWinSize().width / 2, 130);
	this->addChild(startGameButton);

	MenuItemSprite* helpButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mHelp.png"), Sprite::createWithSpriteFrameName("mHelp.png"), CC_CALLBACK_1(WelcomeButtonLayer::helpGameButtonCallback, this));
	Menu* helpGameButton = Menu::create(helpButtonItemSprite, nullptr);
	helpGameButton->setAnchorPoint(Point(0.0f, 0.5f));
	helpGameButton->setScale(0.5f);
	helpGameButton->setPosition(Director::getInstance()->getWinSize().width / 2, 80);
	this->addChild(helpGameButton);

	MenuItemSprite* settingButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("setting.png"), Sprite::createWithSpriteFrameName("setting.png"), CC_CALLBACK_1(WelcomeButtonLayer::settingBotton, this));
	Menu* settingGameButton = Menu::create(settingButtonItemSprite, nullptr);
	settingGameButton->setAnchorPoint(Point(0.0f, 0.5f));
	settingGameButton->setScale(0.5f);
	settingGameButton->setPosition(Director::getInstance()->getWinSize().width / 2 -10, 30);
	this->addChild(settingGameButton);


	bottomOfPic = Sprite::createWithSpriteFrameName("blank.png");
	bottomOfPic->setAnchorPoint(Point(0.5, 0.5));
	bottomOfPic->setScale(0.7f);
	bottomOfPic->setOpacity(0);
	bottomOfPic->setRotation(90);
	bottomOfPic->setPosition(155,65);
	this->addChild(bottomOfPic);

	soundSprite = Sprite::createWithSpriteFrameName("soundSprite.png");
	soundSprite->setPosition(Point(90,70));
	soundSprite->setScale(0.35f);
	soundSprite->setOpacity(0);
	this->addChild(soundSprite);


	easyOrHardSprite = Sprite::createWithSpriteFrameName("gamenandu.png");
	easyOrHardSprite->setPosition(Point(190, 70));
	easyOrHardSprite->setScale(0.5f);
	easyOrHardSprite->setOpacity(0);
	this->addChild(easyOrHardSprite);

	//实现静音的按钮
	buttonSoundOn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonsingle1.png"), Sprite::createWithSpriteFrameName("buttonsingle2.png"), CC_CALLBACK_1(WelcomeButtonLayer::soundOn, this));
	buttonSoundOff = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonsingle1.png"), Sprite::createWithSpriteFrameName("buttonsingle2.png"), CC_CALLBACK_1(WelcomeButtonLayer::soundOff, this));
	buttonSoundOn->setScale(0.1f);
	buttonSoundOff->setScale(0.1f);
	buttonSoundOff->setOpacity(0);
	buttonSoundOn->setOpacity(0);
	
	Menu* soundOnOrOff = Menu::create(buttonSoundOn,buttonSoundOff, nullptr);
	soundOnOrOff->setPosition(Point(140, 70));
	
	soundOnOrOff->alignItemsVerticallyWithPadding(15);
	buttonSoundOn->selected();
	this->addChild(soundOnOrOff);
	


	buttonGameEasy = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonsingle1.png"), Sprite::createWithSpriteFrameName("buttonsingle2.png"), CC_CALLBACK_1(WelcomeButtonLayer::GameEasy, this));
	buttonGameNormal = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonsingle1.png"), Sprite::createWithSpriteFrameName("buttonsingle2.png"), CC_CALLBACK_1(WelcomeButtonLayer::GameNormal, this));
	buttonGameHard = MenuItemSprite::create(Sprite::createWithSpriteFrameName("buttonsingle1.png"), Sprite::createWithSpriteFrameName("buttonsingle2.png"), CC_CALLBACK_1(WelcomeButtonLayer::GameHard, this));
	buttonGameEasy->setPosition(Point(200,105));//Director::sharedDirector()->getVisibleSize().width- 180
	buttonGameNormal->setPosition(Point(200, 65));
	buttonGameHard->setPosition(Point(200, 25));
	buttonGameEasy->setOpacity(0);
	buttonGameNormal->setOpacity(0);
	buttonGameHard->setOpacity(0);
	buttonGameEasy->selected();
	buttonGameEasy->setScale(0.1f);
	buttonGameNormal->setScale(0.1f);
	buttonGameHard->setScale(0.1f);

	Menu* gameEasyOrNormalOrHard = Menu::create(buttonGameEasy, buttonGameNormal,buttonGameHard, nullptr);
	gameEasyOrNormalOrHard->setPosition(Point(Director::sharedDirector()->getVisibleSize().width - 80, 70));

	gameEasyOrNormalOrHard->alignItemsVertically();
	this->addChild(gameEasyOrNormalOrHard);


	return true;
}

void WelcomeButtonLayer::startGameButtonCallback(Ref* pSender) {
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
	Scene* resultSceneWithAnimation = TransitionRotoZoom::create(2.0f, SelectScene::create());
	Director::getInstance()->replaceScene(resultSceneWithAnimation);
}
void WelcomeButtonLayer::helpGameButtonCallback(Ref* pSender){
	Director::getInstance()->pushScene(Director::sharedDirector()->getRunningScene());
 	Scene* resultSceneWithAnimation = TransitionRotoZoom::create(2.0f, gameHelp::create());
 	Director::getInstance()->replaceScene(resultSceneWithAnimation);

}
void WelcomeButtonLayer::soundOn(Ref* pSender) {
	UserDefault::getInstance()->setBoolForKey("isSoundOn", true);
	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->resumeAllAudio();

	buttonSoundOn->selected();
	buttonSoundOff->unselected();
}

void WelcomeButtonLayer::soundOff(Ref* pSender) {
	UserDefault::getInstance()->setBoolForKey("isSoundOn", false);
	audioEffect *audioEffectTemp = nullptr;
	audioEffectTemp->stopAllAudio();

	buttonSoundOff->selected();
	buttonSoundOn->unselected();
}

void WelcomeButtonLayer::GameEasy(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("GameDifficulty", 1);
	buttonGameEasy->selected();
	buttonGameNormal->unselected();
	buttonGameHard->unselected();
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy1", 300);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy2", 400);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy3", 500);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy4", 350);//飞向主角的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy5", 150);//横飞的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_1", 8000); //第一关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_2", 13000);//第二关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss", 18000);//第三关boss
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyBullet", 0.5f);
}
void WelcomeButtonLayer::GameNormal(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("GameDifficulty", 2);
	buttonGameEasy->unselected();
	buttonGameNormal->selected();
	buttonGameHard->unselected();
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy1", 500);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy2", 600);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy3", 700);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy4", 550);//飞向主角的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy5", 350);//横飞的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_1", 18000); //第一关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_2", 23000);//第二关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss", 28000);//第三关boss
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyBullet", 0.3f);
}
void WelcomeButtonLayer::GameHard(Ref* pSender){
	UserDefault::getInstance()->setIntegerForKey("GameDifficulty", 3);
	buttonGameEasy->unselected();
	buttonGameNormal->unselected();
	buttonGameHard->selected();
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy1", 700);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy2", 800);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy3", 900);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy4", 750);//飞向主角的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy5", 550);//横飞的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_1", 28000); //第一关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_2", 33000);//第二关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss", 38000);//第三关boss
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyBullet", 0.1f);
}

void WelcomeButtonLayer::settingBotton(Ref* pSender){
	if (!setting)
	{
		buttonSoundOn->setOpacity(255);
		buttonSoundOff->setOpacity(255);
		buttonGameEasy->setOpacity(255);
		buttonGameNormal->setOpacity(255);
		buttonGameHard->setOpacity(255);
		soundSprite->setOpacity(255);
		easyOrHardSprite->setOpacity(255);
		bottomOfPic->setOpacity(255);
		setting = true;

	}
	else{
	
		buttonSoundOn->setOpacity(0);
		buttonSoundOff->setOpacity(0);
		buttonGameEasy->setOpacity(0);
		buttonGameNormal->setOpacity(0);
		buttonGameHard->setOpacity(0);
		soundSprite->setOpacity(0);
		easyOrHardSprite->setOpacity(0);
		bottomOfPic->setOpacity(0);
		setting = false;
	}
}