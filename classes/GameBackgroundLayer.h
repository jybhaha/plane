

#ifndef GAMEBACKGROUNDLAYER_H_
#define GAMEBACKGROUNDLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "audioEffect.h"

class GameBackgroundLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(GameBackgroundLayer);
	//void addCloud(float useless);

private:
	void update(float useless) override;
	cocos2d::Sprite* background1;
	cocos2d::Sprite* background2;
	cocos2d::Size winSize;

	virtual bool init();
	//void cloudMoveFinished(Node* pSender);
};

#endif /* GAMEBACKGROUNDLAYER_H_ */
