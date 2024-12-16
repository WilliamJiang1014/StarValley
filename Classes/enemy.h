#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cocos2d.h>
using namespace cocos2d;
//定义敌人类型
#define FIGHTER 1
#define ARCHER 2
#define ELITE 3
#define BULLET 4

class List;

class enemy {
	friend class List;
private:
	int enemyType;
	float x, y;
	float player_x, player_y;
	float direction_x, direction_y;
	int speed;
	int damage;
	enemy* link;
public:
	Sprite* sprite;
	enemy(float myX, float myY, float playerX, float playerY, enemy* l,int Type);
	void move();
};


class List {
private:
	enemy* first, * last;
	float playerX, playerY;
public:
	List();
	void update(float x, float y);
	void update_playerlocation(float x,float y);  //记录玩家的位置
	void update_mylocation();  //记录自己的位置
	int hit_damage();  //计算对玩家造成的伤害
	Sprite* generate_enemy();  //生成敌人
	Sprite* newBullet[100];
	void generate_bullet();  //远程敌人攻击生成子弹
	void update_direction();
	void move();
};




#endif 