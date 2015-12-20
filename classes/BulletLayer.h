
#ifndef BULLETLAYER_H_
#define BULLETLAYER_H_

#include "cocos2d.h"
#include "audioEffect.h"

class BulletLayer : public cocos2d::Layer{
public:
	cocos2d::Vector<cocos2d::Sprite*> allBullet;

	CREATE_FUNC(BulletLayer);
	void bulletMoveFinished(Node* pSender); 
/*	void bigBombMoveFinished(Node* pSender);*/
	void stopShooting();
	void setBulletLevelUP();
	void setBulletNumUp();
	void launchBigBomb();
	audioEffect *audioEffectTemp = nullptr;

private:
	int eachBulletDamage;
	std::vector<std::string> bulletTextureName;
	int nowBulletLevel;
	std::vector<cocos2d::SpriteBatchNode*> bulletBatchNodeVector;

	BulletLayer();
	~BulletLayer();
	virtual bool init() override;
	void startShooting(int BulletNum);
	void HeroBulletOne(float useless);
	void HeroBulletTwo(float useless);
	void HeroBulletThree(float useless);
	int BulletNum;
};

#endif /* BULLETLAYER_H_ */
