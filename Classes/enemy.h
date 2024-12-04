#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cocos2d.h>
using namespace cocos2d;

class enemylist;

class enemy {
	friend class enemylist;
private:
	float x, y;  
	float player_x, player_y;
	int damage;
	enemy* link;
public:
	Sprite* sprite;
};

class enemylist {
private:
	enemy* first, * last;
public:
	void set_playerlocation(float x,float y);
	void set_mylocation();
	int attack();
};




#endif 