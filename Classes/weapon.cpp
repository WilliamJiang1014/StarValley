#include "cocos2d.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;
#define L 25

Weapon::Weapon() {
	newbullet = NULL;
}

void Weapon::upgrade(float x, float y) {
	create(x - L, y + L * sqrt(3), 0);
	create1(x - 2 * L, y, 1);
	create2(x - L, y - L * sqrt(3), 2);
	create3(x + L, y - L * sqrt(3), 3);
	create4(x + 2 * L, y, 4);
	create5(x + L, y + L * sqrt(3), 5);
}

void Weapon::init(float x,float y){
	last = new bullet(-1, -1, -1, -1, 0, NULL, 0);
	first = new bullet(-1, -1, -1, -1, 0, last, 0);
	num[0] = 2;
	num[1] = 1;
	num[2] = 2;
	num[3] = 2;
	num[4] = 1;
	num[5] = 2;
	upgrade(x, y);
}

void Weapon::select_data(int i) {
	switch (num[i]) {
	case 0:
		damage[i] = 0;
		attackSpeed[i] = 1000;
		range[i] = 0;
		isRanged[i] = false;
		break;
	case 1:
		damage[i] = 10;
		attackSpeed[i] = 1.0f;
		range[i] = 0;
		isRanged[i] = false;
		break;
	case 2:
		damage[i] = 5;
		attackSpeed[i] = 1.0f;
		range[i] = 500;
		isRanged[i] = true;
		break;
	default:
		damage[i] = 0;
		attackSpeed[i] = 1000;
		range[i] = 0;
		isRanged[i] = false;
		break;
	}
}

Sprite* Weapon::select_image(int type) {
	switch (type) {
	case 0:
		break;
	case 1:
		return Sprite::create("weapon/knife.png");
	case 2:
		return Sprite::create("weapon/gun.png");
	default:
		break;
	}
}

void Weapon::create(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon0 = select_image(num[i]);
		weapon0->setPosition(x, y);
		weapon0->setScale(1);
	}
}

void Weapon::create1(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon1 = select_image(num[i]);
		weapon1->setPosition(x, y);
		weapon1->setScale(1);
	}
}

void Weapon::create2(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon2 = select_image(num[i]);
		weapon2->setPosition(x, y);
		weapon2->setScale(1);
	}
}

void Weapon::create3(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon3 = select_image(num[i]);
		weapon3->setPosition(x, y);
		weapon3->setScale(1);
	}
}

void Weapon::create4(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon4 = select_image(num[i]);
		weapon4->setPosition(x, y);
		weapon4->setScale(1);
	}
}

void Weapon::create5(float x, float y, int i) {
	select_data(i);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon5 = select_image(num[i]);
		weapon5->setPosition(x, y);
		weapon5->setScale(1);
	}
}

void Weapon::generate_bullet(float X, float Y, float enemy_X, float enemy_Y, int damage, int i) {
	bullet* new_bullet = new bullet(X, Y, enemy_X, enemy_Y, damage, first->link, i);
	first->link = new_bullet;
	newbullet = new_bullet->bullet_s;
}

void Weapon::bullet_move() {
	bullet* p = first->link;
	while (p != last) {
		p->move();
		p = p->link;
	}
}

bullet* Weapon::bullet_hit() {
	bullet* p = first->link;
	while (p != last) {
		if (p->hit()) {
			return p;
		}
		p = p->link;
	}
	return p;
}

void Weapon::bullet_clear(bullet* k) {
	bullet* p = first,* q;
	while (p != last) {
		if (p==k) {
			q->link = p->link;
			break;
		}
		q = p;
		p = p->link;
	}
}

bullet::bullet(float X, float Y, float enemy_X, float enemy_Y,int damage, bullet* next, int i) {
	bullet_damage = damage;
	link = next;
	x = X;
	y = Y;
	enemy_x = enemy_X;
	enemy_y = enemy_Y;
	int dx = enemy_x - x;
	int dy = enemy_y - y;
	if (dx == 0 && dx == 0) {
		direction_x = 0.6;
		direction_y = 0.6;
	}
	else {
		//单位化每个方向向量
		direction_x = dx / (sqrt(dx * dx + dy * dy));
		direction_y = dy / (sqrt(dx * dx + dy * dy));
	}
	bullet_s = select_bullet(i);
	switch (i) {
	case0:
		bullet_s->setPosition(x - L, y + L * sqrt(3));
		break;
	case1:
		bullet_s->setPosition(x - 2 * L, y);
		break;
	case2:
		bullet_s->setPosition(x - L, y - L * sqrt(3));
		break;
	case3:
		bullet_s->setPosition(x + L, y - L * sqrt(3));
		break;
	case4:
		bullet_s->setPosition(x + 2 * L, y);
		break;
	case5:
		bullet_s->setPosition(x + L, y + L * sqrt(3));
		break;
	default:
		bullet_s->setPosition(x, y);
		break;
	}
	bullet_s->setScale(1);
	
}

Sprite* bullet::select_bullet(int i) {
	if (weapon.num[i] == 2) {
		return Sprite::create("weapon/bullet_gun.png");
	}
	else {
		return Sprite::create("weapon/bullet_gun.png");
	}
}

void bullet::move() {
	bullet_s->setPositionX(bullet_s->getPositionX() + 15 * direction_x);
	bullet_s->setPositionY(bullet_s->getPositionY() + 15 * direction_y);
}

bool bullet::hit() {
	if (bullet_s->getPositionX() <= enemy_x + 10 && bullet_s->getPositionX() >= enemy_x - 10 && bullet_s->getPositionY() <= enemy_y + 10 && bullet_s->getPositionY() >= enemy_y - 10) {
		return true;
	}
	else {
		return false;
	}
}