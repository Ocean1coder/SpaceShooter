#include "Bullet.h"
USING_NS_CC;

Bullet* Bullet ::createBullet()
{
	return Bullet::create();
}

bool Bullet::init()
{
	if (!Node::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Player/bullet.plist", "Player/bullet.png");
	spriteBullet = Sprite::createWithSpriteFrameName("bullet002.png");
	this->addChild(spriteBullet);

	Vector<SpriteFrame*> aniFrames;
	aniFrames.reserve(2);
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet002.png"));
	aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet003.png"));

	Animation* animation = Animation::createWithSpriteFrames(aniFrames, 0.1f);
	Animate* animate = Animate::create(animation);

	spriteBullet->runAction(RepeatForever::create(animate));

	auto onTop = MoveBy::create(1, Vec2(0, 800));
	this->runAction(onTop);

	bulletPhysics = PhysicsBody::createBox(spriteBullet->getContentSize());
	bulletPhysics->setDynamic(false);

	bulletPhysics->setContactTestBitmask(true);
	bulletPhysics->setCollisionBitmask(10);

	this->addComponent(bulletPhysics);

	return true;

}

void Bullet::update(float)
{
	if ((int)this->getPositionY() > 800)
	{
		this->removeFromParent();
	}
}
