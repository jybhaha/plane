

#ifndef SELECTBACKGROUNDLAYER_H_
#define SELECTBACKGROUNDLAYER_H_

#include "cocos2d.h"
#include "GameScene.h"
#include "cocos-ext.h"
#include "audioEffect.h"
using namespace cocos2d::extension;

class SelectBackgroundLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(SelectBackgroundLayer);
private:
	virtual bool init() override;
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event) override;//¶ÔÓ¦back¼ü

	void selectCheckPoint_1(Ref* pSender);
	void selectCheckPoint_2(Ref* pSender);
	void selectCheckPoint_3(Ref* pSender);
	void selectCheckPoint_4(Ref* pSender);
	void selectCheckPoint_5(Ref* pSender);
};

#endif /* SELECTBACKGROUNDLAYER_H_ */
