#ifndef SELECTBUTTONLAYER_H_
#define SELECTBUTTONLAYER_H_

#include "cocos2d.h"
#include "GameScene.h"
#include "audioEffect.h"
#include "cocos-ext.h"
#include "SelectBackgroundLayer.h"
#include "AddArmsScene.h"
using namespace cocos2d::extension;


class SelectButtonLayer :public cocos2d::Layer{
public:
	CREATE_FUNC(SelectButtonLayer);
private:
	virtual bool init() override;
	void ButtonReturn(Ref* pSender);
	void startGameButtonCallback(Ref* pSender);
	void startGameEndlessButtonCallback(Ref* pSender);
	void startGameAllBossButtonCallback(Ref* pSender);
	void startGameArmsButtonCallback(Ref* pSender);

};

#endif /* SELECTBUTTONLAYER_H_ */
