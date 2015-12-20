#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::~AppDelegate(){
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs() {
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
	GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
	//载入XML初始化参数
	this->initConfigXML();

	// initialize director
	Director* director = Director::getInstance();
	auto glview = director->getOpenGLView();

	if (!glview) {
		glview = GLViewImpl::create("JIAO'S PLANE");
		director->setOpenGLView(glview);
	}

	director->setOpenGLView(glview);

	glview->setDesignResolutionSize(320, 480, ResolutionPolicy::SHOW_ALL);

	// turn on display FPS
	director->setDisplayStats(false);//bu xianshi

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	//读取纹理贴度集合
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
															UserDefault::getInstance()->getStringForKey("textureFileName"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		UserDefault::getInstance()->getStringForKey("textureFileName_1"));
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		UserDefault::getInstance()->getStringForKey("textureFileName_2"));

	//读取爆炸动画帧并存入AnimationCache
	Vector<SpriteFrame*> explosionAnimationVector;
	for (int i = 0; i < 9; i++){
		    char animitionFileName[32] = {0};
		    sprintf(animitionFileName, "explosion%02d.png", i+1);
		    SpriteFrame* fm = SpriteFrameCache::getInstance()->getSpriteFrameByName(animitionFileName);
		    explosionAnimationVector.pushBack(fm);
		}
	Animation* explosionAnimation = Animation::createWithSpriteFrames(explosionAnimationVector, 0.5f / 9.0f, 1);
	AnimationCache::getInstance()->addAnimation(explosionAnimation,"explosion");

	//预存储音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/mainMainMusic.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/selectScene.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/gameScene.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/GameOver.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/enenmyexplodeEffect.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/bossDestroyEffect.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/GainMissle.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/BulletLevelUp.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/Fly.mp3");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("music/warning.wav");

	Scene* welcomeScene = WelcomeScene::create();
	
	director->runWithScene(welcomeScene);
	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}


void AppDelegate::initConfigXML(){
	UserDefault::getInstance()->setStringForKey("textureFileName","texture.plist");
	UserDefault::getInstance()->setStringForKey("textureFileName_1", "texture_1.plist");
	UserDefault::getInstance()->setStringForKey("textureFileName_2", "texture_2.plist");
	UserDefault::getInstance()->setFloatForKey("intervalOfAddBullet",0.2f);
	//UserDefault::getInstance()->setFloatForKey("intervalOfAddCloud",20.0f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemy", 0.5f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyEndless", 0.7f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddBoss", 2.0f);
	UserDefault::getInstance()->setFloatForKey("intervalOfAddEnemyBullet", 0.2f);
	UserDefault::getInstance()->setIntegerForKey("damageOfInitBullet",100);
	UserDefault::getInstance()->setIntegerForKey("damageOfDeltaWhenLevelUp", 50);
	UserDefault::getInstance()->setIntegerForKey("damageOfBigBomb", 400);
	UserDefault::getInstance()->setFloatForKey("probabilityOfBaseEnemyAppear", 0.4f);
	UserDefault::getInstance()->setFloatForKey("probabilityOfDeltaEnemyAppear", 0.007f);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy1", 300);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy2", 400);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy3", 500);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy4", 350);//飞向主角的飞机
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemy5", 150);//横飞的飞机

	UserDefault::getInstance()->setIntegerForKey("HPOfMyPlane1", 1000);
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_1",8000); //第一关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss_2",13000);//第二关boss
	UserDefault::getInstance()->setIntegerForKey("HPOfEnemyBoss", 18000);//第三关boss
	//UserDefault::getInstance()->setIntegerForKey("FlytimeOfCloud",35);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy1",10);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy2",10);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy3",5);
	//UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemy4", 4); //飞向主角的飞机
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfEnemyBossAppear",7);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftLevelUp",12);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftBigBomb",12);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftMoreBullet", 12);
	UserDefault::getInstance()->setIntegerForKey("FlytimeOfGiftBlood", 12);
	//UserDefault::getInstance()->setIntegerForKey("CheckPoint", 3);
	UserDefault::getInstance()->setBoolForKey("ISEndlessGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISAllBossGameMode", false);
	UserDefault::getInstance()->setBoolForKey("ISOrdinaryGameMode", false);
	UserDefault::getInstance()->setIntegerForKey("ISEnemyBoss", 1);
	UserDefault::getInstance()->setBoolForKey("isSoundOn", true); //设置音乐是否开启
	UserDefault::getInstance()->setIntegerForKey("GameDifficulty", 1);//游戏难度设置 1 easy 2normal 3 hard

//	UserDefault::getInstance()->setIntegerForKey("MyPlaneSelect", 3);//选择飞机
// 	UserDefault::getInstance()->setIntegerForKey("BestScoreOfTheGameAllBoss", 0);
// 	UserDefault::getInstance()->setIntegerForKey("BestScoreOfTheGameEndless", 0);
}
