#include "Player.h"
#include "GameScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>

USING_NS_CC;

Player* Player::createPlayer()
{
	return Player::create();
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player/player.plist", "Player/player.png");
	spritePlayer = Sprite::createWithSpriteFrameName("tile001.png");
	spritePlayer->retain();
	this->addChild(spritePlayer);

	Animate* animatePlayer = Animate::create(Player::creatAnimation("tile00", 10, 0.08f));
	spritePlayer->runAction(RepeatForever::create(animatePlayer));

	//barHP = Sprite::create("HpBar.png");
	//barHP->setPosition(Vec2(0, -25));
	//barHP->setScaleY(0.1f);
	///*barHP->setAnchorPoint(Vec2(0, 0.5));*/
	//addChild(barHP);

	playerPhysics = PhysicsBody::createBox(spritePlayer->getContentSize());
	playerPhysics->setDynamic(false);

	playerPhysics->setContactTestBitmask(true);
	playerPhysics->setCollisionBitmask(1);

	this->addComponent(playerPhysics);

	spritePlayer->release();

	this->schedule(CC_SCHEDULE_SELECTOR(Player::updateHealth));

	return true;
}

Animation* Player::creatAnimation(std::string tenFrame, int soFrame, float delay)
{
	Vector<SpriteFrame*> frameAni;
	for (int i = 1; i < soFrame; i++)
	{
		char buffer[20] = {0};
		sprintf(buffer, "%d.png", i);
		std::string str = tenFrame + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		frameAni.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameAni, delay);
	return animation;

}

int Player::getMoveCheck()
{
	return this->moveCheck;
}

void Player::setMoveRight()
{
	moveCheck = 1;
}

void Player::setMoveLeft()
{
	moveCheck = - 1;
}
//void Player::setMoveUp()
//{
//	moveCheck = 1;
//}
//void Player::setMoveDown()
//{
//	moveCheck = -1;
//}

void Player::setMoveIdol()
{
	moveCheck = 0;
}

int Player::getHealth()
{
	return healthPlayer;
}

void Player::setHealth(int x)
{
	healthPlayer += x;
}

void Player::updateHealth(float dt)
{
	if (this->getHealth() <= 0)
	{

		this->spritePlayer->removeFromParent();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/enemyexplosion.mp3");
			
	}

	/*switch (healthPlayer)
	{
	case 1:
		barHP->setScaleX(0.02f);
		barHP->setColor(Color3B::RED);
		break;
	case 2:
		barHP->setScaleX(0.04f);
		break;
	case 3:
		barHP->setScaleX(0.06f);
		break;
	case 4:
		barHP->setScaleX(0.08f);
		break;
	case 5:
		barHP->setScaleX(0.1f);
		break;
	default:
		break;
	}*/
}
