#ifndef __PLAYER_SCENE_H__
#define __PLAYER_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class player :public Sprite {
private:
	Sprite* Player;
public:
	static Sprite* createPlayer();
	void controlPlayer();
	//virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	CREATE_FUNC(player);
};

#endif