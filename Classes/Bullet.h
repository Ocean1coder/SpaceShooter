#ifndef __BULLET_H_
#define __BULLET_H_

#include "cocos2d.h"

using namespace cocos2d;

class Bullet : public Node
{

public:
	static Bullet* createBullet();
	virtual bool init();

	Sprite* spriteBullet;

	PhysicsBody* bulletPhysics;

	void update(float);
	
	CREATE_FUNC(Bullet);

private:
	int moveCheck;
};
#endif __BULLET_H_

