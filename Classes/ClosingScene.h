#ifndef __CLOSING_SCENE_H__
#define __CLOSING_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class ClosingScene : public Layer
{
public:
    static Scene* createScene(unsigned int tempScore);
    virtual bool init();
    
    CREATE_FUNC(ClosingScene);
};

#endif // __CLOSING_SCENE_H__