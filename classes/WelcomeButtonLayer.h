

#ifndef WELCOMEBUTTONLAYER_H_
#define WELCOMEBUTTONLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScene.h"
#include "gameHelp.h"
#include "SelectScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

class WelcomeButtonLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(WelcomeButtonLayer);
	WelcomeButtonLayer();
private:
	void startGameButtonCallback(Ref* pSender);
	void helpGameButtonCallback(Ref* pSender);
	void soundOn(Ref* pSender);
	void soundOff(Ref* pSender);
	void GameEasy(Ref* pSender);
	void GameNormal(Ref* pSender);
	void GameHard(Ref* pSender);
	void settingBotton(Ref* pSender);
	bool setting; //设置是否按下,默认没有按下

	virtual bool init() override;

	MenuItemSprite* buttonSoundOn;
	MenuItemSprite* buttonSoundOff;
	MenuItemSprite* buttonGameEasy;
	MenuItemSprite* buttonGameNormal;
	MenuItemSprite* buttonGameHard;

	Sprite* soundSprite;
	Sprite* easyOrHardSprite;
	Sprite* bottomOfPic;

};

#endif /* WELCOMEBUTTONLAYER_H_ */
