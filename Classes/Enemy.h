#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"

using namespace cocos2d;

class Enemy : public Node
{
public:
	virtual int getHealthEnemy() = 0;
	virtual void setHealthEnemy() = 0;
protected:
	int healthEnemy;
};

#endif _ENEMY_H_

