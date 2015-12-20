

#ifndef M_WELCOMESCENE_H_
#define M_WELCOMESCENE_H_



#include "cocos2d.h"
#include "WelcomeButtonLayer.h"
#include "WelcomeBackgroundLayer.h"
#include "audioEffect.h"

class WelcomeScene : public cocos2d::Scene{
public:
	static cocos2d::Scene* create();
private:
	static Scene* welcomeScene;
	static WelcomeBackgroundLayer* welcomeBackgroundLayer;
	static WelcomeButtonLayer* welcomeButtonLayer;	
};

#endif /* WELCOMESCENE_H_ */
