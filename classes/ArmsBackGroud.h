#ifndef ARMSBACKGROUD_H_
#define ARMSBACKGROUD_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SelectScene.h"
#include "audioEffect.h"
using namespace cocos2d::extension;

class ArmsBackGroud :public cocos2d::Layer
{
public:
	CREATE_FUNC(ArmsBackGroud);
protected:
private:
	virtual bool init() override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;

	void ButtonReturn(Ref* pSender);
	void myPlaneSelect1(Ref* pSender);
	void myPlaneSelect2(Ref* pSender);
	void myPlaneSelect3(Ref* pSender);

};

#endif
