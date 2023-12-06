#include "LoadingScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}

bool LoadingScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("BGloadingscene.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    background->setContentSize(Size(400, 400));
    this->addChild(background);

    auto loadingLabel = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 20);
    loadingLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    loadingLabel->enableOutline(Color4B::BLACK, 2);
    this->addChild(loadingLabel);

    loadingBar = ProgressTimer::create(Sprite::create("loadingbar.png"));
    loadingBar->setType(ProgressTimer::Type::BAR);
    loadingBar->setMidpoint(Vec2(0, 0.5));
    loadingBar->setBarChangeRate(Vec2(1, 0));
    loadingBar->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 50);
    this->addChild(loadingBar);
    
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(LoadingScene::loadGameAssets), 3.0f);

    return true;
}

void LoadingScene::loadGameAssets(float dt)
{
    loadingBar->setPercentage(100);

    auto gameScene = GameScene::create();
    Director::getInstance()->replaceScene(gameScene);
}