#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "player.h"
#include "enemy.h"
using namespace cocos2d;

class battle :public Layer {
private:
	player Brotato;
	List enemylist;
	std::map<EventKeyboard::KeyCode, bool> keyMap;
public:
	Layer* createlayer();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void playermove(float delta);
	void playermove2(float delta);

	void update_per_frame(float delta);
	void update_per_second(float delta);

	void generate_enemy(float delta);

	bool gameover();
	bool dead();

	CREATE_FUNC(battle);
};


#endif 