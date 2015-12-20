#ifndef M_GAMEHELP_H_
#define M_GAMEHELP_H_

#include "cocos2d.h"
#include "gameHelpBackgroud.h"

class gameHelp:public cocos2d::Scene
{
public:
	static Scene* create();
private:
	static Scene* gamehelpscene;
};


#endif