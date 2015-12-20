#ifndef _AUDIOEFFECT_H
#define _AUDIOEFFECT_H

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class audioEffect : public cocos2d::Layer
{
public:
	audioEffect::audioEffect();
	void addWelcomSceneEffect();
	void addSelectSceneEffect();
	void addGameScene();
	void addEndlessGameMode();
	void addBossGameMode();
	void myPlaneChoose();
	void whenPause();
	void whenResume();
	void addFireEffect();
	void GameoverEffect();
	void enemyExplosion();
	void bossExplosion();
	void gainMissile();
	void gainBulletLevelUp();
	void MissleBlowUp();
	void warning();

	void stopAllAudio();
	void resumeAllAudio();

	//bool isSoundOn;

};

#endif 