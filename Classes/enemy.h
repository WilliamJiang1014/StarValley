#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <cocos2d.h>
using namespace cocos2d;
//�����������
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
	void update_playerlocation(float x,float y);  //��¼��ҵ�λ��
	void update_mylocation();  //��¼�Լ���λ��
	int hit_damage();  //����������ɵ��˺�
	Sprite* generate_enemy();  //���ɵ���
	Sprite* newBullet[100];
	void generate_bullet();  //Զ�̵��˹��������ӵ�
	void update_direction();
	void move();
};




#endif 