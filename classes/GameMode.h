#ifndef GAMEMODE_H
#define GAMEMODE_H

#include "cocos2d.h"

class GameMode :public cocos2d::Layer
{
public:
	GameMode();
	~GameMode();
	bool getISEndlessGameMode();
	/*bool setISEndlessGameMode(bool ChooseMode);*/
};


#endif