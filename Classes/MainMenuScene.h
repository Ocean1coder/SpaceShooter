#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene : public cocos2d::Scene
{
private:
    int backgroundMusic = -1;
    bool soundOn = true;
    Label* soundLabel;

public:
    static Scene* createScene();
    virtual bool init() override;
    void startGame(cocos2d::Ref* sender);
    void soundGame(Ref* sender);
    void quitGame(cocos2d::Ref* sender);

    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__