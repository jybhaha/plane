#ifndef GAMEHELPBACKGROUD_H
#define GAMEHELPBACKGROUD_H

#include "cocos2d.h"
#include "cocos-ext.h"
/*#include "WelcomeScene.h"*/
#include "audioEffect.h"
using namespace cocos2d::extension;

class gameHelpBackgroud :public cocos2d::Layer
{
public:
	CREATE_FUNC(gameHelpBackgroud);
	gameHelpBackgroud();
protected:
private:
	virtual bool init() override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;

	void ButtonReturn(Ref* pSender);
	void ButtonChangeUp(Ref* pSender);
	void ButtonChangeDown(Ref* pSender);

	cocos2d::Sprite* helpSprie1;
	int indexHelp;
	cocos2d::Sprite* helpSprie2;
};

#endif
