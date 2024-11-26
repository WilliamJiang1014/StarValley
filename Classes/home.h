#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include "player.h"
using namespace cocos2d;

class home :public Scene {
private:
	Sprite* player1;
	std::map<EventKeyboard::KeyCode, bool> keyMap;
public:
	static Scene* createScene();
	virtual bool init();

	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void move(float delta);
	void move2(float delta);

	CREATE_FUNC(home);

};

#endif