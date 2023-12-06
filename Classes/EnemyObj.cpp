#include "EnemyObj.h"

USING_NS_CC;

using namespace cocos2d;

SmallEnemy* SmallEnemy::createSmallEnemy()
{
	return SmallEnemy::create();
}

bool SmallEnemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 1;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player/enemy.plist", "Player/enemy.png");
	smallEnemy = Sprite::createWithSpriteFrameName("smallEnemy1.png");

	this->addChild(smallEnemy);

	Vector<SpriteFrame*> aniFrames;
	aniFrames.reserve(2);
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("smallEnemy1.png"));
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("smallEnemy2.png"));

	Animation* animation = Animation::createWithSpriteFrames(aniFrames, 0.5f);
	Animate* animate = Animate::create(animation);

	smallEnemy->runAction(RepeatForever::create(animate));

	auto moveDown = MoveBy::create(4, Vec2(0, -900));
	this->runAction(moveDown);

	enemySmallPhysisc = PhysicsBody::createBox(smallEnemy->getContentSize());
	enemySmallPhysisc->setDynamic(false);

	enemySmallPhysisc->setContactTestBitmask(true);
	enemySmallPhysisc->setCollisionBitmask(20);

	this->addComponent(enemySmallPhysisc);

	this->schedule(CC_SCHEDULE_SELECTOR(SmallEnemy::updateDie));


	return true;
}

int SmallEnemy::getHealthEnemy()
{
	return this->healthEnemy;
}

void SmallEnemy::setHealthEnemy()
{
	healthEnemy -= 1;
}

void SmallEnemy::updateDie(float dt)
{
	if (healthEnemy == 0 )
	{
		auto destructionEffect = Sprite::create("destroy1.png");
		destructionEffect->setPosition(this->getPosition());
		destructionEffect->retain();
		this->getParent()->addChild(destructionEffect);

		auto destructionAnimation = Animation::create();
		destructionAnimation->setDelayPerUnit(0.1f);

		for (int i = 1; i <= 5; i++)
		{
			std::string frameName = StringUtils::format("destroy%d.png", i);
			destructionAnimation->addSpriteFrameWithFile(frameName);
		}

		auto destructionAction = Animate::create(destructionAnimation);

		auto sequence = Sequence::create(destructionAction, CallFunc::create([this, destructionEffect]() {
			SmallEnemy::onDestructionAnimationComplete(destructionEffect);
			}), nullptr);
		destructionEffect->runAction(sequence);

		this->removeFromParentAndCleanup(true);
	}

	else if((int)this->getPositionY() < 0)
	{
		this->removeFromParentAndCleanup(true);
	}


}

void SmallEnemy::onDestructionAnimationComplete(Sprite* destructionEffect)
{
	if (destructionEffect != nullptr)
		destructionEffect->removeFromParentAndCleanup(true);
}

BigEnemy* BigEnemy::createBigEnemy()
{
	return BigEnemy::create();
}

bool BigEnemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 3;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player/enemy.plist", "Player/enemy.png");
	bigEnemy = Sprite::createWithSpriteFrameName("bigEnemy1.png");

	this->addChild(bigEnemy);

	Vector<SpriteFrame*> aniFrames;
	aniFrames.reserve(2);
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigEnemy1.png"));
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bigEnemy2.png"));

	Animation* animation = Animation::createWithSpriteFrames(aniFrames, 0.5f);
	Animate* animate = Animate::create(animation);

	bigEnemy->runAction(RepeatForever::create(animate));

	
	

	auto moveDown = MoveBy::create(4, Vec2(0, -900));
	this->runAction(moveDown);

	enemyBigPhysisc = PhysicsBody::createBox(bigEnemy->getContentSize());
	enemyBigPhysisc->setDynamic(false);

	enemyBigPhysisc->setContactTestBitmask(true);
	enemyBigPhysisc->setCollisionBitmask(40);

	this->addComponent(enemyBigPhysisc);

	this->schedule(CC_SCHEDULE_SELECTOR(BigEnemy::updateDie));

	return true;
}


int BigEnemy::getHealthEnemy()
{
	return this->healthEnemy;
}

void BigEnemy::setHealthEnemy()
{
	healthEnemy -= 1;
}

void BigEnemy::updateDie(float dt)
{
	if (healthEnemy == 0 || (int)this->getPositionY() < 0)
	{
		auto destructionEffect = Sprite::create("destroy1.png");
		destructionEffect->setPosition(this->getPosition());
		destructionEffect->retain();
		this->getParent()->addChild(destructionEffect);

		auto destructionAnimation = Animation::create();
		destructionAnimation->setDelayPerUnit(0.1f);

		for (int i = 1; i <= 5; i++)
		{
			std::string frameName = StringUtils::format("destroy%d.png", i);
			destructionAnimation->addSpriteFrameWithFile(frameName);
		}

		auto destructionAction = Animate::create(destructionAnimation);

		auto sequence = Sequence::create(destructionAction, CallFunc::create([this, destructionEffect]() {
			BigEnemy::onDestructionAnimationComplete(destructionEffect);
			}), nullptr);
		destructionEffect->runAction(sequence);

		this->removeFromParentAndCleanup(true);
	}
	
	else if ((int)this->getPositionY() < 0)
	{
		this->removeFromParentAndCleanup(true);
	}

}

void BigEnemy::onDestructionAnimationComplete(Sprite* destructionEffect)
{
	if (destructionEffect != nullptr)
	destructionEffect->removeFromParentAndCleanup(true);
}
		



MediumEnemy* MediumEnemy::createMediumEnemy()
{
	return MediumEnemy::create();
}

bool MediumEnemy::init()
{
	if (!Node::init())
	{
		return false;
	}

	healthEnemy = 2;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player/enemy.plist", "Player/enemy.png");
	mediumEnemy = Sprite::createWithSpriteFrameName("mediumEnemy1.png");

	this->addChild(mediumEnemy);

	Vector<SpriteFrame*> aniFrames;
	aniFrames.reserve(2);
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("mediumEnemy1.png"));
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("mediumEnemy2.png"));

	Animation* animation = Animation::createWithSpriteFrames(aniFrames, 0.5f);
	Animate* animate = Animate::create(animation);

	mediumEnemy->runAction(RepeatForever::create(animate));

	auto moveDown = MoveBy::create(4, Vec2(0, -900));
	this->runAction(moveDown);

	enemyMediumPhysisc = PhysicsBody::createBox(mediumEnemy->getContentSize());
	enemyMediumPhysisc->setDynamic(false);

	enemyMediumPhysisc->setContactTestBitmask(true);
	enemyMediumPhysisc->setCollisionBitmask(30);

	this->addComponent(enemyMediumPhysisc);

	this->schedule(CC_SCHEDULE_SELECTOR(MediumEnemy::updateDie));

	return true;
}

int MediumEnemy::getHealthEnemy()
{
	return this->healthEnemy;
}

void MediumEnemy::setHealthEnemy()
{
	healthEnemy -= 1;
}

void MediumEnemy::updateDie(float dt)
{
	if (healthEnemy == 0 || (int)this->getPositionY() < 0)
	{
		auto destructionEffect = Sprite::create("destroy1.png");
		destructionEffect->setPosition(this->getPosition());
		destructionEffect->retain();
		this->getParent()->addChild(destructionEffect);

		auto destructionAnimation = Animation::create();
		destructionAnimation->setDelayPerUnit(0.1f);

		for (int i = 1; i <= 5; i++)
		{
			std::string frameName = StringUtils::format("destroy%d.png", i);
			destructionAnimation->addSpriteFrameWithFile(frameName);
		}

		auto destructionAction = Animate::create(destructionAnimation);

		auto sequence = Sequence::create(destructionAction, CallFunc::create([this, destructionEffect]() {
			MediumEnemy::onDestructionAnimationComplete(destructionEffect);
			}), nullptr);
		destructionEffect->runAction(sequence);

		this->removeFromParentAndCleanup(true);
	}

	else if ((int)this->getPositionY() < 0)
	{
		this->removeFromParentAndCleanup(true);
	}
}

void MediumEnemy::onDestructionAnimationComplete(Sprite* destructionEffect)
{
	if (destructionEffect != nullptr)
		destructionEffect->removeFromParentAndCleanup(true);
}
