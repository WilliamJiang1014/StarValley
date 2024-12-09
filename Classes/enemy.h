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
	void update_playerlocation(float x,float y);  //��¼��ҵ�λ��
	void update_mylocation();  //��¼�Լ���λ��
	int hit_damage();  //����������ɵ��˺�
	Sprite* generate_enemy();  //���ɵ���
	void update_direction();
	void move();
};




#endif 