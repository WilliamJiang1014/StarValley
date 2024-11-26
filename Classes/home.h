#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include "player.h"
using namespace cocos2d;

class home :public Scene {
private:
	Sprite* player1;
public:
	static Scene* createScene();
	virtual bool init();

	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	CREATE_FUNC(home);

};

#endif