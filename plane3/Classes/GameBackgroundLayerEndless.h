#ifndef GAMEBACKGROUNDLAYERENDLESS_H_
#define GAMEBACKGROUNDLAYERENDLESS_H_

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
#include "audioEffect.h"

class GameBackgroundLayerEndless : public cocos2d::Layer{
public:
	CREATE_FUNC(GameBackgroundLayerEndless);
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