#include "ClosingScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

unsigned int m_score;

Scene* ClosingScene::createScene(unsigned int tempScore)
{
    m_score = tempScore;

    auto scene = Scene::create();

    auto layer = ClosingScene::create();

    scene->addChild(layer);

    return scene;
}
bool ClosingScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("BGclosingscene.png");
    background->setContentSize(Size(400, 400));
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(background);

    auto label = Label::createWithSystemFont("Game Over", "fonts/Marker Felt.ttf", 45);
    label->enableOutline(Color4B::BLACK, 2);
    label->setColor(Color3B::YELLOW);
    addChild(label);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 175));

    auto playAgainLabel = Label::createWithTTF("Play Again", "fonts/Marker Felt.ttf", 20);
    playAgainLabel->enableOutline(Color4B::BLACK, 2);
    playAgainLabel->setColor(Color3B::YELLOW);

    auto playAgainButton = MenuItemLabel::create(playAgainLabel, [](Ref* sender)
        {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::create()));
        });

    auto mainMenuLabel = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 20);
    mainMenuLabel->enableOutline(Color4B::BLACK, 2);
    mainMenuLabel->setColor(Color3B::YELLOW);
   
    auto backToMainMenuButton = MenuItemLabel::create(mainMenuLabel, [](Ref* sender)
        {
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, MainMenuScene::create()));
        });

    auto quitLabel = Label::createWithTTF("Quit Game", "fonts/Marker Felt.ttf", 20);
    quitLabel->enableOutline(Color4B::BLACK, 2);
    quitLabel->setColor(Color3B::YELLOW);

    auto quitButton = MenuItemLabel::create(quitLabel, [](Ref* sender)
        {
            Director::getInstance()->end();
        });

    auto menu = Menu::create(playAgainButton, backToMainMenuButton, quitButton, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 125));
    
    this->addChild(menu);


    std::string tempscore = cocos2d::StringUtils::format("High Score: %i", m_score);

    auto highScoreLabel = cocos2d::Label::createWithTTF(tempscore, "fonts/Marker Felt.ttf", 40);
    highScoreLabel->enableOutline(Color4B::BLACK, 2);
    highScoreLabel->setColor(Color3B::YELLOW);
    highScoreLabel->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(highScoreLabel);

    return true;
}