#ifndef __SHIP_H_
#define __SHIP_H_

#include "cocos2d.h"

using namespace cocos2d;

class Player : public Node
{

public:
	static Player* createPlayer();	
	virtual bool init();

	Sprite* spritePlayer;
	Sprite* barHP;

	PhysicsBody* playerPhysics;

	Animation* creatAnimation(std::string tenFrame, int soFrame, float delay);

	int getMoveCheck();
	void setMoveRight();
	void setMoveLeft();
	/*void setMoveUp();
	void setMoveDown();*/
	void setMoveIdol();

	int getHealth();
	void setHealth(int);
	void updateHealth(float dt);

	CREATE_FUNC(Player);

private:
	int moveCheck;
	int healthPlayer = 5;
};
#endif __SHIP_H_

