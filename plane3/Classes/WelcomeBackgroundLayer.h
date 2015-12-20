

#ifndef WELCOMEBACKGROUNDLAYER_H_
#define WELCOMEBACKGROUNDLAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

#include "audioEffect.h"

using namespace cocos2d::extension;



class WelcomeBackgroundLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(WelcomeBackgroundLayer);
private:
	virtual bool init() override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;//¶ÔÓ¦back¼ü
	cocos2d::Label* Title;
};

#endif /* WELCOMEBACKGROUNDLAYER_H_ */
