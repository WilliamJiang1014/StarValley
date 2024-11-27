#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

#include "cocos2d.h"
#include "player.h"
using namespace cocos2d;

class home :public Scene {
private:
	player Brotato;
	std::map<EventKeyboard::KeyCode, bool> keyMap;
public:
	static Scene* createScene();
	virtual bool init();

	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void playermove(float delta);
	void playermove2(float delta);

	void update_player(float delta);

	void test(float delta);

	CREATE_FUNC(home);

};

#endif