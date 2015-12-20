#include "GameMode.h"

USING_NS_CC;

GameMode::GameMode(){}
GameMode::~GameMode(){}

bool GameMode::getISEndlessGameMode(){
	return  UserDefault::getInstance()->getBoolForKey("ISEndlessGameMode");
}
