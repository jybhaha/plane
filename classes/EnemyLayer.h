
#ifndef ENEMYLAYER_H_
#define ENEMYLAYER_H_

#include <string>
#include <vector>
#include "cocos2d.h"
#include "audioEffect.h"
#include "PlaneLayer.h"



class EnemyLayer : public cocos2d::Layer{
public:
	CREATE_FUNC(EnemyLayer);
	cocos2d::Sprite* getBossSprite();
private:
	const float  baseEnemyAppearProbability;
	const float deltaEnemyAppearProbability;
	float nowEnemyAppearProbability;
	std::vector<std::string> enemyTextureName;
	std::vector<int> enemyFlyTime;
	std::vector<int> enemyInitHP;
	cocos2d::Vector<cocos2d::Sprite*> allEnemy;
	const cocos2d::Size winSize;
	bool bossAppeared;
	cocos2d::Sprite* bossWarning;
	cocos2d::Sprite* bossSprite;


	EnemyLayer();
	~EnemyLayer();
	virtual bool init() override;
	
	void enemyMoveFinished(Node* pSender);
	void startAddEnemy();
	void stopAddEnemy();
	void update(float useless) override;
	void addBossSprite();
	void changeSceneCallBack(float useless);
	void setBossWarningOn();
	void bossStartMove();
	void addEnemySprite(float useless);
	void addEnemySpriteEndless(float useless);
	void addEnemyBossSprite(float useless);

	bool isRandomEnemy1;//防止产生并行飞机
	bool isBoss;
	bool isCollectiveWithEnemy;
};

#endif /* ENEMYLAYER_H_ */
