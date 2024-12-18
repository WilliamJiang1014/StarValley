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

	Sprite* weapon0,* weapon1,* weapon2,* weapon3,* weapon4,* weapon5;   // 武器精灵
	int damage[6];         // 攻击力
	float attackSpeed[6];       // 攻击速度（每秒攻击次数）
	float range[6];       // 攻击范围
	bool isRanged[6];           // 是否为远程攻击模式
	int num[6];           // 编号

	void upgrade(float x,float y);
	void set(float x, float y);
	void select_data(int i,int type);
	Sprite* select_image(int tpye);
	void create(float x, float y, int i);
	void create1(float x, float y, int i);
	void create2(float x, float y, int i);
	void create3(float x, float y, int i);
	void create4(float x, float y, int i);
	void create5(float x, float y, int i);

	Sprite* newbullet[99999];
	void generate_bullet(float x, float y);

};

#endif 