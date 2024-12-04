#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
using namespace cocos2d;

#define init_FULLHP 100;

class player {
private:
	int FULLHP;
	int Level;
	int Strength;
	int damage;
	int defence;
	int money;
	int range;
public:
	int HP;
	int countdown;
	int speed;
	Sprite* sprite;
	Sprite* enemy;
	Label* label;
	void init();
	bool dead();
	bool gameover();
	void test();
	void createPlayer();
	void createInfo();
	void showInfo();
	void hurt();
};

#endif 