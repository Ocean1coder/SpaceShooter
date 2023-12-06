#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"

class LoadingScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadingScene);

private:
    void loadGameAssets(float dt);
    cocos2d::ProgressTimer* loadingBar;
};

#endif // __LOADING_SCENE_H__