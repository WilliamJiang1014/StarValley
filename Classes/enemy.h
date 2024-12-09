#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cocos2d.h>
using namespace cocos2d;

class List;

class enemy {
	friend class List;
private:
	float x, y;
	float player_x, player_y;
	float direction_x, direction_y;
	int speed;
	int damage;
	enemy* link;
public:
	Sprite* sprite;
	enemy(enemy* l);
	void move();
};


class List {
private:
	enemy* first, * last;
public:
	List();
	void update(float x, float y);
	void update_playerlocation(float x,float y);  //记录玩家的位置
	void update_mylocation();  //记录自己的位置
	int hit_damage();  //计算对玩家造成的伤害
	Sprite* generate_enemy();  //生成敌人
	void update_direction();
	void move();
};




#endif 