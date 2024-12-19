#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include "player.h"
#include <vector>

using namespace cocos2d;
using namespace std;

class bullet;

class Weapon
{
public:
	Weapon();
	float x, y;
	float player_x, player_y;
	bullet* first, * last;
	Sprite* weapon[6];   // 武器精灵
	int damage[6];         // 攻击力
	float attackSpeed[6];       // 攻击速度（每秒攻击次数）
	float range[6];       // 攻击范围
	bool isRanged[6];           // 是否为远程攻击模式
	int num[6];           // 编号

	void init(float x, float y);
	void select_data(int i);
	Sprite* select_image(int tpye);
	void create(float x, float y);

	void generate_bullet(float X, float Y, float enemy_X, float enemy_Y,int damage,int i);
	Sprite* newbullet;
	void bullet_move();
	bullet* bullet_hit();
	void bullet_clear(bullet* k);
};

class bullet {
	friend class Weapon;
private:
	Weapon weapon;
public:
	float x, y;
	float enemy_x, enemy_y;
	float direction_x, direction_y;
	int bullet_damage;
	bullet* link;
	Sprite* bullet_s;
	bullet(float X, float Y, float enemy_X, float enemy_Y, int damage, bullet* next, int i);
	Sprite* select_bullet(int i);
	void move();
	bool hit();
};

#endif 