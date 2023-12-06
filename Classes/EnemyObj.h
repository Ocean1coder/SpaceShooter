#ifndef _SMALL_ENEMY_H_
#define _SMALL_ENEMY_H_	

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class SmallEnemy : public Enemy
{
public:
	static SmallEnemy* createSmallEnemy();
	virtual bool init();

	Sprite* smallEnemy;

	PhysicsBody* enemySmallPhysisc;

	int getHealthEnemy();
	void setHealthEnemy();

	void updateDie(float);

	CREATE_FUNC(SmallEnemy);
private:
	void onDestructionAnimationComplete(Sprite* destructionEffect);

	cocos2d::Sprite* destructionEffect;
};

#endif // !_SMALL_ENEMY_H

#ifndef _BIG_ENEMY_H_
#define _BIG_ENEMY_H_	

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class BigEnemy : public Enemy
{
public:
	static BigEnemy* createBigEnemy();
	virtual bool init();

	Sprite* bigEnemy;

	PhysicsBody* enemyBigPhysisc;

	

	int getHealthEnemy();
	void setHealthEnemy();

	void updateDie(float);



	CREATE_FUNC(BigEnemy);

private:
	void onDestructionAnimationComplete(Sprite* destructionEffect);

	cocos2d::Sprite* destructionEffect;
};

#endif // !_BIG_ENEMY_H


#ifndef _MEDIUM_ENEMY_H_
#define _MEDIUM_ENEMY_H_	

#include "cocos2d.h"
#include "Enemy.h"

using namespace cocos2d;

class MediumEnemy : public Enemy
{
public:
	static MediumEnemy* createMediumEnemy();
	virtual bool init();

	Sprite* mediumEnemy;

	PhysicsBody* enemyMediumPhysisc;

	int getHealthEnemy();
	void setHealthEnemy();

	void updateDie(float dt);

	CREATE_FUNC(MediumEnemy);
private:
	void onDestructionAnimationComplete(Sprite* destructionEffect);

	cocos2d::Sprite* destructionEffect;

};

#endif // !_MEDIUM_ENEMY_H
