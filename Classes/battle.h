#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "player.h"
#include "enemy.h"
#include "weapon.h"
using namespace cocos2d;

class battle :public Layer {
private:
	int wave;
	player Brotato;
	List enemylist;
	Weapon weapon1, weapon2, weapon3, weapon4, weapon5, weapon6;
	std::map<EventKeyboard::KeyCode, bool> keyMap;
public:
	Layer* createlayer();
	virtual bool init();
	void OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void playermove(float delta);
	void playermove2(float delta);
	void playerHurt(float delta);

	void update_per_frame(float delta);
	void update_per_second(float delta);
	void update_per_attack1(float delta);
	void update_per_attack2(float delta);
	void update_per_attack3(float delta);
	void update_per_attack4(float delta);
	void update_per_attack5(float delta);
	void update_per_attack6(float delta);

	void generate_enemy(float delta);
	void generate_bullet(float delta);

	void getCoin();

	bool gameover();
	bool dead();

	int totalOver();

	// ªÒ»°
	player* getPlayer();

	CREATE_FUNC(battle);
};


#endif 