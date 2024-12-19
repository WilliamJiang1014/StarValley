#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
<<<<<<< Updated upstream
#include "player.h"
=======
#include "Item.h"
>>>>>>> Stashed changes
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
	Sprite* weapon[6];   // ��������
	int damage[6];         // ������
	float attackSpeed[6];       // �����ٶȣ�ÿ�빥��������
	float range[6];       // ������Χ
	bool isRanged[6];           // �Ƿ�ΪԶ�̹���ģʽ
	int num[6];           // ���(���ڼ�¼���������Ƿ���������
	Item items[6];            // ���������item��

<<<<<<< Updated upstream
	void init(float x, float y);
=======
	void upgrade(float x,float y);
	void set(float x, float y);
>>>>>>> Stashed changes
	void select_data(int i);
	Sprite* select_image(int tpye);
	void create(float x, float y);

<<<<<<< Updated upstream
	void generate_bullet(float X, float Y, float enemy_X, float enemy_Y,int damage,int i);
	Sprite* newbullet;
	void bullet_move();
	bullet* bullet_hit();
	void bullet_clear(bullet* k);
};
=======
	// ���������������
	bool addWeapon(const Item& item);

	Sprite* newbullet[99999];
	void generate_bullet(float x, float y);
>>>>>>> Stashed changes

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