#ifndef RESULTBUTTONLAYER_H_
#define RESULTBUTTONLAYER_H_

#include "cocos2d.h"
#include "GameScene.h"
#include "WelcomeScene.h"

class ResultButtonLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(ResultButtonLayer);

	void restartGameButtonCallback(Ref* pSender);
	void backToMenuButtonCallback(Ref* pSender);
private:
	virtual bool init() override;

};

#endif /* RESULTBUTTONLAYER_H_ */
