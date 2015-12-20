#include "PlaneLayer.h"

USING_NS_CC;

bool PlaneLayer::init() {
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PlaneLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PlaneLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 1)
	{
		myPlane = Sprite::createWithSpriteFrameName("myplane1_1.png");
		myPlane->setAnchorPoint(Point(0.5, 0));
		myPlane->setPosition(winSize.width / 2, 0);
		myPlane->setScale(0.5f);
		myPlane->setUserData(new PlaneUserData(500));
		this->addChild(myPlane, 0, "PLANE");
		return true;
	}
	else if (UserDefault::getInstance()->getIntegerForKey("MyPlaneSelect") == 2)
	{
		myPlane = Sprite::createWithSpriteFrameName("myplane2_1.png");
		myPlane->setAnchorPoint(Point(0.5, 0));
		myPlane->setPosition(winSize.width / 2, 0);
		myPlane->setUserData(new PlaneUserData(1000));
		myPlane->setScale(0.5f);
		this->addChild(myPlane, 0, "PLANE");
		return true;
	}
	else{
		myPlane = Sprite::createWithSpriteFrameName("myplane3_1.png");
		myPlane->setAnchorPoint(Point(0.5,0));
		myPlane->setPosition(winSize.width / 2, 0);
		myPlane->setScale(0.5f);
		myPlane->setUserData(new PlaneUserData(1500));
		this->addChild(myPlane, 0, "PLANE");
		return true;
	}
}

PlaneLayer::PlaneLayer() :
		initHP(1000), myPlane(nullptr), winSize(Director::getInstance()->getWinSize()) {
}

bool PlaneLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	return true;
}

int PlaneLayer::getInitHP() const{
	return this->initHP;
}

//做适当修改，使飞机不能出窗口外
void PlaneLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
	if (Director::getInstance()->isPaused() == false) {
		myPlane->setPosition(myPlane->getPosition() + touch->getDelta());
		if ((myPlane->getPositionX() - myPlane->getContentSize().width / 4 < 0)){//myPlane->getPositionX() - myPlane->getContentSize().width / 2
			myPlane->setPositionX(0 + myPlane->getContentSize().width / 4);
		}
		else if ((myPlane->getPositionX() + myPlane->getContentSize().width / 4) > winSize.width) {//myPlane->getPositionX() + myPlane->getContentSize().width / 2
			myPlane->setPositionX(winSize.width - myPlane->getContentSize().width / 4);
		}
		if (myPlane->getPositionY() < 0) {
			myPlane->setPositionY(0);
		} else if (myPlane->getPositionY()+ myPlane->getContentSize().height /2> winSize.height) {
			myPlane->setPositionY(winSize.height - myPlane->getContentSize().height / 2);
		}
	}

}

Sprite* PlaneLayer::getMyPlane() {
	return this->myPlane;
}

