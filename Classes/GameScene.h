/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Bullet.h"
#include "EnemyObj.h"

class GameScene : public cocos2d::Scene
{
private:

    PhysicsWorld* world;
    void setPhysicWorld(PhysicsWorld* _world)
    {
        world = _world;
    }

    Sprite* background1;
    Sprite* background2;

    float scrollSpeed;

    unsigned int m_score;
    Label* scoreLabel;

    static const int PAUSE_BUTTON_TAG = 1;
    static const int RESUME_BUTTON_TAG = 2;


    cocos2d::MenuItemImage* pauseItem;
    cocos2d::MenuItemImage* resumeItem;

public:
   
    static cocos2d::Scene* createPhysicsWorld();

    virtual bool init();

    Player* player;

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

    void updateMove(float dt);  

    void updateBullet(float dt);

    void updateEnemy(float dt);

    void updateScroll(float dt);

    void updateEffect(float dt);

    void pauseGame(Ref* sender);

    void resumeGame(Ref* sender);

    bool onContactBegin(PhysicsContact& contact);

    CREATE_FUNC(GameScene);


};

#endif // __GAME_SCENE_H__
