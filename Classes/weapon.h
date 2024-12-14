#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

class Weapon
{
public:
	float x, y;
	float player_x, player_y;

	Sprite* weapon;          // 武器精灵
	int damage;         // 攻击力
	float attackSpeed;       // 攻击速度（每秒攻击次数）
	float range;       // 攻击范围
	bool isRanged;           // 是否为远程攻击模式
	int num;           // 编号

	void create(float x, float y);
	void select(int i);

	// 移动功能（与玩家同步）
	void move(float x, float y);


};

#endif 