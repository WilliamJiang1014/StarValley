#ifndef GAMEOVERLAYER_H
#define GAMEOVERLAYER_H

#include "cocos2d.h"
USING_NS_CC;

class GameOverLayer : public Layer 
{
public:
    static Scene* createScene(bool playerWon);
    static GameOverLayer* create(bool playerWon);
    virtual bool init(bool playerWon);
};











#endif