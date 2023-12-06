#include "GameScene.h"
#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"
#include "ClosingScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>



USING_NS_CC;



Scene* GameScene::createPhysicsWorld()
{
    auto scene = GameScene::create();

    return scene;
}


bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    background1 = cocos2d::Sprite::create("Player/background1.png");
    background1->setAnchorPoint(cocos2d::Vec2::ZERO);
    /*background1->setPosition(cocos2d::Vec2(800, 400));*/
    background1->setContentSize(Size(400, 800));
    this->addChild(background1);

    background2 = cocos2d::Sprite::create("Player/background1.png");
    background2->setAnchorPoint(cocos2d::Vec2::ZERO);
    background2->setContentSize(cocos2d::Size(400, 800));
    /*background2->setPosition(cocos2d::Vec2(400, 800));*/
    this->addChild(background2);

    scrollSpeed = 50.f;

    player = Player::create();
    player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 10));
    addChild(player);

    m_score = 0;
    
    std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);

    scoreLabel = cocos2d::Label::createWithTTF(tempscore, "fonts/Marker Felt.ttf", 20);
    scoreLabel->setPosition(cocos2d::Vec2(50, 680));
    this->addChild(scoreLabel);

    pauseItem = cocos2d::MenuItemImage::create("btnPauseNormal.png", "btnPauseNormal.png", CC_CALLBACK_1(GameScene::pauseGame, this));
    resumeItem = cocos2d::MenuItemImage::create("btnPauseSelected.png", "btnPauseSelected.png", CC_CALLBACK_1(GameScene::resumeGame, this));
    

    if (pauseItem && resumeItem)
    {
        auto menu = cocos2d::Menu::create(pauseItem, resumeItem, nullptr);
        menu->setPosition(cocos2d::Vec2(visibleSize.width - 25, visibleSize.height - 25));
        
        this->addChild(menu);
    }

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateMove));
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateBullet), 0.5f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateEnemy), 3);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateScroll));
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateEffect), 0.5f);


    auto listener1 = EventListenerPhysicsContact::create();
    listener1->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case cocos2d::EventKeyboard::KeyCode::KEY_A:
            player->setMoveLeft();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_D:
            player->setMoveRight();
            break;
        /*case cocos2d::EventKeyboard::KeyCode::KEY_W:
            player->setMoveUp();
            break;
        case cocos2d::EventKeyboard::KeyCode::KEY_S:
            player->setMoveDown();
            break;*/
        default:
            break;
    }
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        player->setMoveIdol();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        player->setMoveIdol();
        break;
    /*case cocos2d::EventKeyboard::KeyCode::KEY_W:
        player->setMoveUp();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        player->setMoveDown();
        break;*/
    default:
        break;
    }
}

void GameScene::updateMove(float dt)
{
    auto moveRight = MoveBy::create(dt, Vec2(dt * 180, 0));
    auto moveLeft = moveRight->reverse();
    /*auto moveUp = MoveBy::create(dt, Vec2(0, dt * 180));
    auto moveDown = moveUp->reverse();*/

    if (player->getMoveCheck() == 1 && (int)player ->getPositionX() < 390)
    {
        player->runAction(moveRight);
    }
    else if (player->getMoveCheck() == -1 && (int)player->getPositionX() > 10)
    {
        player->runAction(moveLeft);
    }
    /*else if (player->getMoveCheck() == 1 && (int)player->getPositionY() < 750)
    {
        player->runAction(moveUp);
    }
    else if (player->getMoveCheck() == -1 && (int)player->getPositionY() > 10)
    {
        player->runAction(moveDown);
    }*/
    else
    {
        player->stopAllActions();
    }
}

void GameScene::updateBullet(float dt)
{
    auto bullet = Bullet::create();
    //bullet->setPosition(player->getPosition());
    bullet->setPosition(Vec2((int)player->getPositionX(), (int)player->getPositionY() + 3));
    addChild(bullet);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/bulletshot.mp3");
    
 
    
}

void GameScene::updateEnemy(float dt)
{
    auto smallEnemy = SmallEnemy::create();
    smallEnemy->setPosition(Vec2(random(10, 320), 800));
    addChild(smallEnemy);

    auto mediumEnemy = MediumEnemy::create();
    mediumEnemy->setPosition(Vec2(random(10, 320), 800));
    addChild(mediumEnemy);

    auto bigEnemy = BigEnemy::create();
    bigEnemy->setPosition(Vec2(random(10, 320), 800));
    addChild(bigEnemy);

    if (m_score >= 100)
    {
        auto smallEnemy = SmallEnemy::create();
        smallEnemy->setPosition(Vec2(random(10, 320), 800));
        addChild(smallEnemy);

        auto mediumEnemy = MediumEnemy::create();
        mediumEnemy->setPosition(Vec2(random(10, 320), 800));
        addChild(mediumEnemy);

        auto bigEnemy = BigEnemy::create();
        bigEnemy->setPosition(Vec2(random(10, 320), 800));
        addChild(bigEnemy);
    }

}


void GameScene::updateScroll(float dt)
{
    
    background1->setPositionY(background1->getPositionY() - scrollSpeed * dt);
    background2->setPositionY(background2->getPositionY() - scrollSpeed * dt);

   
    if (background1->getPositionY() <= -background1->getContentSize().height)
    {
        background1->setPositionY(background2->getPositionY() + background2->getContentSize().height);
    }

    if (background2->getPositionY() <= -background2->getContentSize().height)
    {
        background2->setPositionY(background1->getPositionY() + background1->getContentSize().height);
    }
}

//void GameScene::updateScore(int points)
//{
//    m_score += points;
//    /*scoreLabel->setString("Score: " + std::to_string(m_score));*/
//}

void GameScene::updateEffect(float dt)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto cloud = Sprite::create("cloud.png");
    cloud ->setPosition(Vec2(random(10, 320), 800));
    this->addChild(cloud);
    auto moveRight = MoveBy::create(2.0f, Vec2(visibleSize.width, 0));
    auto moveLeft = MoveBy::create(2.0f, Vec2(-visibleSize.width, 0));
    auto sequence = Sequence::create(moveRight, moveLeft, nullptr);
    auto repeatForever = RepeatForever::create(sequence);
    cloud->runAction(repeatForever);
}

void GameScene::pauseGame(Ref* sender)
{

    if (pauseItem)
    {
        pauseItem->setVisible(false);
    }
    if (resumeItem)
    {
        resumeItem->setVisible(true);
    }

    Director::getInstance()->pause();
    
}

void GameScene::resumeGame(Ref* sender)
{

    if (resumeItem)
    {
        resumeItem->setVisible(false);
    }
    if (pauseItem)
    {
        pauseItem->setVisible(true);
    }

    Director::getInstance()->resume();

}


bool GameScene::onContactBegin(PhysicsContact& contact)
{
    auto nodeA = contact.getShapeA()->getBody();
    auto nodeB = contact.getShapeB()->getBody();


    if (nodeA->getCollisionBitmask() == 10 && nodeB->getCollisionBitmask() == 20 ||
        nodeA->getCollisionBitmask() == 20 && nodeB->getCollisionBitmask() == 10)
    {

        if (nodeA->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                nodeA->getNode()->removeFromParent();
                /*updateScore(10);*/
                /*++ m_score;*/
                m_score += 10;
                std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                scoreLabel->setString(tempscore);

                auto smallEnemy = dynamic_cast<SmallEnemy*>(nodeB->getNode());
                smallEnemy->setHealthEnemy();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");

            }
        }

        if (nodeB->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {
                nodeB->getNode()->removeFromParent();
                /*updateScore(10);*/
                /*++ m_score;*/
                m_score += 10;
                std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                scoreLabel->setString(tempscore);

                auto smallEnemy = dynamic_cast<SmallEnemy*>(nodeA->getNode());
                smallEnemy->setHealthEnemy();
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
            }
        }

    }

    if (nodeA->getCollisionBitmask() == 10 && nodeB->getCollisionBitmask() == 30 ||
        nodeA->getCollisionBitmask() == 30 && nodeB->getCollisionBitmask() == 10)
    {

        if (nodeA->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                nodeA->getNode()->removeFromParent();

                auto mediumEnemy = dynamic_cast<MediumEnemy*>(nodeB->getNode());
                mediumEnemy->setHealthEnemy();
                if (mediumEnemy->getHealthEnemy() == 0)
                {
                    m_score += 20;
                    std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                    scoreLabel->setString(tempscore);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
                }
            }
        }

        if (nodeB->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {
                nodeB->getNode()->removeFromParent();

                auto mediumEnemy = dynamic_cast<MediumEnemy*>(nodeA->getNode());
                mediumEnemy->setHealthEnemy();
                if (mediumEnemy->getHealthEnemy() == 0)
                {
                    m_score += 20;
                    std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                    scoreLabel->setString(tempscore);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
                }
            }
        }

    }

    if (nodeA->getCollisionBitmask() == 10 && nodeB->getCollisionBitmask() == 40 ||
        nodeA->getCollisionBitmask() == 40 && nodeB->getCollisionBitmask() == 10)
    {

        if (nodeA->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                nodeA->getNode()->removeFromParent();

                auto bigEnemy = dynamic_cast<BigEnemy*>(nodeB->getNode());
                bigEnemy->setHealthEnemy();
                if (bigEnemy->getHealthEnemy() == 0)
                {
                    m_score += 30;
                    std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                    scoreLabel->setString(tempscore);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
                }
            }
        }

        if (nodeB->getCollisionBitmask() == 10)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {
                nodeB->getNode()->removeFromParent();

                auto bigEnemy = dynamic_cast<BigEnemy*>(nodeA->getNode());
                bigEnemy->setHealthEnemy();
                if (bigEnemy->getHealthEnemy() == 0)
                {
                    m_score += 30;
                    std::string tempscore = cocos2d::StringUtils::format("Score: %i", m_score);
                    scoreLabel->setString(tempscore);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
                }

            }
        }

    }

    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 20 ||
        nodeA->getCollisionBitmask() == 20 && nodeB->getCollisionBitmask() == 1)
    {

        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                player->setHealth(-1);
                
                nodeB->getNode()->removeFromParent();

                auto closingScene = ClosingScene::createScene(m_score);

                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                /*if (player->getHealth() <= 0)
                {
                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                    nodeA->getNode()->removeFromParent();
                }*/

            }

            if (nodeB->getCollisionBitmask() == 1)
            {
                if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
                {

                    player->setHealth(-1);

                    nodeB->getNode()->removeFromParent();

                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                   /* if (player->getHealth() <= 0)
                    {
                        auto closingScene = ClosingScene::createScene(m_score);

                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));
                        nodeA->getNode()->removeFromParent();
                    }*/



                }
            }

        }

    }

    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 30 ||
        nodeA->getCollisionBitmask() == 30 && nodeB->getCollisionBitmask() == 1)
    {

        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                player->setHealth(-1);

                nodeB->getNode()->removeFromParent();

                auto closingScene = ClosingScene::createScene(m_score);

                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                /*if (player->getHealth() <= 0)
                {
                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));
                    nodeA->getNode()->removeFromParent();
                }*/

            }

            if (nodeB->getCollisionBitmask() == 1)
            {
                if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
                {

                    player->setHealth(-1);

                    nodeB->getNode()->removeFromParent();

                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                   /* if (player->getHealth() <= 0)
                    {
                        auto closingScene = ClosingScene::createScene(m_score);

                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));
                        nodeA->getNode()->removeFromParent();
                    }*/

                }
            }

        }

    }

    if (nodeA->getCollisionBitmask() == 1 && nodeB->getCollisionBitmask() == 40 ||
        nodeA->getCollisionBitmask() == 40 && nodeB->getCollisionBitmask() == 1)
    {

        if (nodeA->getCollisionBitmask() == 1)
        {
            if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
            {

                player->setHealth(-1);

                nodeB->getNode()->removeFromParent();


                auto closingScene = ClosingScene::createScene(m_score);

                Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                /*if (player->getHealth() <= 0)
                {
                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));
                    nodeA->getNode()->removeFromParent();
                }*/

               

            }

            if (nodeB->getCollisionBitmask() == 1)
            {
                if (nodeA->getNode() != nullptr && nodeB->getNode() != nullptr)
                {

                    player->setHealth(-1);

                    nodeB->getNode()->removeFromParent();


                    auto closingScene = ClosingScene::createScene(m_score);

                    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));

                    /*if (player->getHealth() <= 0)
                    {
                        auto closingScene = ClosingScene::createScene(m_score);

                        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, closingScene));
                        nodeA->getNode()->removeFromParent();
                    }*/

                }
            }

        }

    }

    return true;

}

   

