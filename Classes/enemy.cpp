#include "cocos2d.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void enemylist::set_playerlocation(float x, float y) {
	enemy* p = first->link;
	while (p != last) {
		p->player_x = x;
		p->player_y = y;
	}
}

void enemylist::set_mylocation() {
	enemy* p = first->link;
	while (p != last) {
		p->x = p->sprite->getPositionX();
		p->y = p->sprite->getPositionY();
	}
}

int enemylist::attack() {
	int total_damage = 0;
	enemy* p = first->link;
	while (p != last) {
		if (distance(p->x, p->y, p->player_x, p->player_y) < 100)
			total_damage += p->damage;
	}
	return total_damage;
}