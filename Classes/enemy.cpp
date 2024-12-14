#include "cocos2d.h"
#include "enemy.h"
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
using namespace cocos2d;
using namespace std;

float distance(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int randType() {   
	srand(time(0));
	int enemyType;
	int r = rand() % 10;
	if (r >= 0 && r <= 0)
		enemyType = FIGHTER;
	else if (r >= 1 && r <= 3)
		enemyType = ARCHER;
	else
		enemyType = ELITE;
	return enemyType;
}

enemy::enemy(float myX, float myY, float playerX, float playerY, enemy* l, int Type) {
	//初始化参数
	x = myX;
	y = myY;
	player_x = playerX;
	player_y = playerY;
	direction_x = -1;
	direction_y = -1;
	damage = 1;
	HP = 5;
	speed = 3;
	link = l;
	enemyType = Type;

	//生成敌人sprite
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (enemyType == FIGHTER) {
		sprite = Sprite::create("enemy/bruiser.png");
		sprite->setPosition(rand() % int(visibleSize.width), rand() % int(visibleSize.height));
		sprite->setScale(1);
	}
	else if (enemyType == ARCHER) {
		sprite = Sprite::create("enemy/baby_alien.png");
		sprite->setPosition(rand() % int(visibleSize.width), rand() % int(visibleSize.height));
		sprite->setScale(1);
	}
	else if (enemyType == ELITE) {
		sprite = Sprite::create("enemy/buffer.png");
		sprite->setPosition(rand() % int(visibleSize.width), rand() % int(visibleSize.height));
		sprite->setScale(1);
	}
	else {
		sprite = Sprite::create("enemy/HelloWorld.png");
		sprite->setPosition(myX, myY);
		sprite->setScale(0.3);
	}
}

void enemy::move() {
	sprite->setPositionX(sprite->getPositionX() + speed * direction_x);
	sprite->setPositionY(sprite->getPositionY() + speed * direction_y);
}

List::List() {
	last = new enemy(-1, -1, -1, -1, NULL, -1);
	first = new enemy(-1, -1, -1, -1, last, -1);
	for (int i = 0; i < 100; i++)
		newBullet[i] = NULL;
}

void List::update(float x, float y) {
	update_playerlocation(x, y);
	update_mylocation();
	update_direction();
}

void List::update_playerlocation(float x, float y) {  //记录玩家的位置
	playerX = x;
	playerY = y;
	enemy* p = first->link;
	while (p != last) {
		p->player_x = x;
		p->player_y = y;
		p = p->link;
	}
}

void List::update_mylocation() {  //记录自己的位置
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
		//单位化每个方向向量
		if (p->enemyType != BULLET) {
			int X = p->player_x - p->x;
			int Y = p->player_y - p->y;
			p->direction_x = X / (sqrt(X * X + Y * Y));
			p->direction_y = Y / (sqrt(X * X + Y * Y));
		}
		p = p->link;
	}
}

int List::hit_damage() {  //计算对玩家造成的伤害
	int total_damage = 0;
	enemy* p = first->link;
	while (p != last) {
		if (p->enemyType == FIGHTER || p->enemyType == BULLET) {
			if (distance(p->x, p->y, p->player_x, p->player_y) < 60)
				total_damage += p->damage;
		}
		p = p->link;
	}
	return total_damage;
}

Sprite* List::generate_enemy() {   //生成敌人
	enemy* new_enemy = new enemy(900, 900, playerX, playerY, first->link, randType());
	first->link = new_enemy;
	return new_enemy->sprite;
}

void List::generate_bullet() {
	for (int i = 0; i < 100; i++)
		newBullet[i] = NULL;
	int pos = 0;
	enemy* p = first->link;
	while (p != last) {
		if (p->enemyType == ARCHER) {
			enemy* new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			//?趨???????
			int X = p->player_x - p->x;
			int Y = p->player_y - p->y;
			new_enemy->direction_x = X / (sqrt(X * X + Y * Y));
			new_enemy->direction_y = Y / (sqrt(X * X + Y * Y));

			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;
		}
		if (p->enemyType == ELITE) {
			enemy* new_enemy;
			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = 0.6;
			new_enemy->direction_y = 0.6;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = 0.6;
			new_enemy->direction_y = -0.6;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = -0.6;
			new_enemy->direction_y = 0.6;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = -0.6;
			new_enemy->direction_y = -0.6;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = 0;
			new_enemy->direction_y = 0.85;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = 0.85;
			new_enemy->direction_y = 0.0;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = 0;
			new_enemy->direction_y = -0.85;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;

			new_enemy = new enemy(p->x, p->y, playerX, playerY, first->link, BULLET);
			new_enemy->direction_x = -0.85;
			new_enemy->direction_y = 0;
			first->link = new_enemy;
			newBullet[pos] = new_enemy->sprite;
			pos++;
		}
		p = p->link;
	}
}

void List::move() {
	enemy* p = first->link;
	while (p != last) {
		p->move();
		p = p->link;
	}
}

float List::nearestDistance() {//寻找最近的敌人
	float nearest = 99999;
	enemy* p = first->link;
	while (p != last) {
		if (float d = distance(p->x, p->y, p->player_x, p->player_y) < nearest)
			nearest = d;
		p = p->link;
	}
	return nearest;
}

void List::hurt(int range,int damage) {//敌人受伤
	enemy* p = first->link;
	float nearest = List::nearestDistance();
	if (nearest <= range) {
		while (p != last) {
			if (distance(p->x, p->y, p->player_x, p->player_y) == nearest) {
				p->HP -= damage;
				if (p->HP <= 0) {
					                  //敌人死亡
				}
				break;
			}
			p = p->link;
		}
	}
}