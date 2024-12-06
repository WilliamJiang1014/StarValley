#include "cocos2d.h"
#include "enemy.h"
#include <string>
#include <cmath>
#include <random>
using namespace cocos2d;
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

enemy::enemy(enemy* l) {
	//��ʼ������
	x = -1;
	y = -1;
	player_x = -1;
	player_y = -1;
	damage = 1;
	speed = 5;
	link = l;

	//���ɵ���sprite
	auto visibleSize = Director::getInstance()->getVisibleSize();
	sprite = Sprite::create("buildings/houses.png");
	sprite->setPosition(rand() % int(visibleSize.width), rand() % int(visibleSize.height));
	sprite->setScale(1);
}

void enemy::move() {
	sprite->setPositionX(sprite->getPositionX() + speed * direction_x);
	sprite->setPositionY(sprite->getPositionY() + speed * direction_y);
}

List::List() {
	last = new enemy(NULL);
	first = new enemy(last);
}

void List::update(float x, float y) {
	update_playerlocation(x, y);
	update_mylocation();
	update_direction();
}

void List::update_playerlocation(float x, float y) {  //��¼��ҵ�λ��
	enemy* p = first->link;
	while (p != last) {
		p->player_x = x;
		p->player_y = y;
		p = p->link;
	}
}

void List::update_mylocation() {  //��¼�Լ���λ��
	enemy* p = first->link;
	while (p != last) {
		p->x = p->sprite->getPositionX();
		p->y = p->sprite->getPositionY();
		p = p->link;
	}
}

void List::update_direction() {
	enemy* p = first->link;
	while (p != last) {
		//��λ��ÿ����������
		int X = p->player_x - p->x;
		int Y = p->player_y - p->y;
		p->direction_x = X / (sqrt(X * X + Y * Y));
		p->direction_y = Y / (sqrt(X * X + Y * Y));

		p = p->link;
	}
}

int List::hit_damage() {  //����������ɵ��˺�
	int total_damage = 0;
	enemy* p = first->link;
	while (p != last) {
		if (distance(p->x, p->y, p->player_x, p->player_y) < 100)
			total_damage += p->damage;
		p = p->link;
	}
	return total_damage;
}

Sprite* List::generate_enemy() {   //���ɵ���
	enemy* new_enemy = new enemy(first->link);
	first->link = new_enemy;
	return new_enemy->sprite;
}

void List::move() {
	enemy* p = first->link;
	while (p != last) {
		p->move();
		p = p->link;
	}
}