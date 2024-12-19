#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cocos2d.h>
#include <vector>
using namespace cocos2d;
#define FIGHTER 1
#define ARCHER 2
#define ELITE 3
#define BULLET 4

class List;

class enemy {
	friend class List;
private:
	bool dead;
	int enemyType;
	float x, y;
	float player_x, player_y;
	float direction_x, direction_y;
	int speed;
	int damage;
	int HP;
	enemy* link;
public:
	Sprite* sprite;
	enemy(float myX, float myY, float playerX, float playerY, enemy* l, int Type);
	void move();
};

class coin {
	friend class List;
private:
	bool collected;
	bool newGenerated;
	coin* link;
	float coinX, coinY;
public:
	Sprite* coinSprite;
	coin(float x, float y, coin* next);
};

class List {
private:
	enemy* first, * last;
	coin* coinFirst, * coinLast;
	float playerX, playerY;
public:
	List();
	void update(float x, float y);
	void update_playerlocation(float x,float y);  //��¼��ҵ�λ��
	void update_mylocation();  //��¼�Լ���λ��
	int hit_damage();  //����������ɵ��˺�
	Sprite* generate_enemy();  //���ɵ���
	Sprite* newBullet[100];
	Sprite* newCoin[100];
	void generate_bullet();
	void update_direction();
	void move();
	float nearestDistance(float X, float Y);
	float nearestX(float X, float Y);
	float nearestY(float X, float Y);
	void hurt(float X, float Y,int range, int damage);

	int collectCoin();

	void clear();
};




#endif 