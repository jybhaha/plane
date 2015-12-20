
#include "ResultButtonLayer.h"

USING_NS_CC;

bool ResultButtonLayer::init() {
	MenuItemSprite* restartGameButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("restartGameButton.png"), Sprite::createWithSpriteFrameName("restartGameButton.png"), CC_CALLBACK_1(ResultButtonLayer::restartGameButtonCallback, this));
	Menu* restartGameButton = Menu::create(restartGameButtonItemSprite, nullptr);
	restartGameButton->setPosition(Director::getInstance()->getWinSize().width/2-30,280);
	restartGameButton->setAnchorPoint(Point(0.5,0.5));
	restartGameButton->setScale(0.8f);
	this->addChild(restartGameButton);

	MenuItemSprite* backToMenuButtonItemSprite = MenuItemSprite::create(Sprite::createWithSpriteFrameName("backToMenuButton.png"), Sprite::createWithSpriteFrameName("backToMenuButton.png"), CC_CALLBACK_1(ResultButtonLayer::backToMenuButtonCallback, this));
	Menu* backToMenuButton = Menu::create(backToMenuButtonItemSprite, nullptr);
	backToMenuButton->setPosition(Director::getInstance()->getWinSize().width/2-30,230);
	backToMenuButton->setScale(0.8f);
	backToMenuButton->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(backToMenuButton);

	return true;
}

void ResultButtonLayer::restartGameButtonCallback(Ref* pSender){
	Scene* GameScene = TransitionJumpZoom::create(2.0f, GameScene::create());
	//Director::getInstance()->replaceScene(GameScene);
	Director::getInstance()->pushScene(GameScene);
}

void ResultButtonLayer::backToMenuButtonCallback(Ref* pSender){
	Scene* welcomeScene = TransitionJumpZoom::create(2.0f, WelcomeScene::create());
	Director::getInstance()->pushScene(welcomeScene);
}

