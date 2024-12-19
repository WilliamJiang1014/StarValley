#include "cocos2d.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;
#define L 25

<<<<<<< Updated upstream
Weapon::Weapon() {
	newbullet = NULL;
}

void Weapon::init(float x,float y){
	last = new bullet(-1, -1, -1, -1, 0, NULL, 0);
	first = new bullet(-1, -1, -1, -1, 0, last, 0);
	num[0] = 2;
	num[1] = 2;
	num[2] = 2;
	num[3] = 2;
	num[4] = 2;
	num[5] = 2;
	create(x, y);
}

void Weapon::select_data(int i) {
	switch (num[i]) {
=======
// 设置精灵位置
void Weapon::upgrade(float x, float y)
{
	create(x - L, y + L * sqrt(3), 0);
	create1(x - 2 * L, y, 1);
	create2(x - L, y - L * sqrt(3), 2);
	create3(x + L, y - L * sqrt(3), 3);
	create4(x + 2 * L, y, 4);
	create5(x + L, y + L * sqrt(3), 5);
}

bool Weapon::addWeapon(const Item& item)
{
	// 查找空的武器槽
	for (int i = 1; i < 6; i++)
	{
		if (num[i] == 0)
		{
			// 找到空槽，添加武器
			num[i] = 1;
			items[i] = item;
			return true;
		}
	}
	//// 如果没有空槽，检查是否有相同武器
	//for (int i = 0; i < 6; i++) 
	//{
	//	if (num[i] == type) 
	//	{
	//		// 升级武器
	//		upgradeWeapon(i);
	//		return true;
	//	}
	//}
	//// 如果武器槽已满且没有相同武器，返回失败
	//return false;

	// 如果所有槽都满且没有匹配的武器，则购买失败
	return false;
}

void Weapon::set(float x,float y){

	num[0] = 1;
	for (int i = 1; i < 6; i++)
	{
		num[i] = 0;
	}

	int selectedCharacter = UserDefault::getInstance()->getIntegerForKey("SelectedCharacter", 0);
	switch (selectedCharacter)
	{
	case 0:
	case 1:
	case 2:
		items[0].id = 0;
		items[0].name = "knife";
		items[0].cost = 0;
		items[0].health = 0;
		items[0].strength = 100;
		items[0].attackSpeed = 3;
		items[0].range = 200;
		items[0].isWeapon = true;
		items[0].isRanged = false;
		//items[0](0, "knife", 0, 0, 100, 3, 200, 0, true, false);
		/*damage[0] = 10;
		attackSpeed[0] = 1.0f;
		range[0] = 0;
		isRanged[0] = false;*/
		break;
	case 3:
	case 4:
		items[0].id = 1;
		items[0].name = "gun";
		items[0].cost = 0;
		items[0].health = 0;
		items[0].strength = 50;
		items[0].attackSpeed = 10;
		items[0].range = 500;
		items[0].isWeapon = true;
		items[0].isRanged = true;
		//items[0](0, "gun", 0, 0, 50, 10, 200, 0, true, true);
		/*damage[0] = 5;
		attackSpeed[0] = 1.0f;
		range[0] = 100;
		isRanged[0] = true;*/
		break;
	}
	
	upgrade(x, y);
}

void Weapon::select_data(int i)
{
	// .................................................
	damage[i] = items[i].strength;
	attackSpeed[i] = items[i].attackSpeed;
	range[i] = items[i].range;
	isRanged[i] = items[i].isRanged;

	/*switch (type) {
>>>>>>> Stashed changes
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
	}*/
}

Sprite* Weapon::select_image(int i) 
{
	string weaponImage = "weapon/" + items[i].name + ".png";
	return Sprite::create(weaponImage);

	/*switch (type) {
	case 0:
		break;
	case 1:
		return Sprite::create("weapon/knife.png");
	case 2:
		return Sprite::create("weapon/gun.png");
	default:
		break;
	}*/
}

<<<<<<< Updated upstream
void Weapon::create(float x, float y) {
	for (int i = 0; i < 6; i++) {
		select_data(i);
		if (num[i]) {
			Sprite* p = select_image(num[i]);
			weapon[i] = p;
			switch (i) {
			case 0:
				weapon[i]->setPosition(x - L, y + L * sqrt(3));
				break;
			case 1:
				weapon[i]->setPosition(x - 2 * L, y);
				break;
			case 2:
				weapon[i]->setPosition(x - L, y - L * sqrt(3));
				break;
			case 3:
				weapon[i]->setPosition(x + L, y - L * sqrt(3));
				break;
			case 4:
				weapon[i]->setPosition(x + 2 * L, y);
				break;
			case 5:
				weapon[i]->setPosition(x + L, y + L * sqrt(3));
				break;
			default:
				weapon[i]->setPosition(x, y);
				break;
			}
			weapon[i]->setScale(1);
		}
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
	enemy_x = enemy_X;
	enemy_y = enemy_Y;
	bullet_s = select_bullet(i);
	switch (i) {
	case 0:
		bullet_s->setPosition(X - L, Y + L * sqrt(3));
		break;
	case 1:
		bullet_s->setPosition(X - 2 * L, Y);
		break;
	case 2:
		bullet_s->setPosition(X - L, Y - L * sqrt(3));
		break;
	case 3:
		bullet_s->setPosition(X + L, Y - L * sqrt(3));
		break;
	case 4:
		bullet_s->setPosition(X + 2 * L, Y);
		break;
	case 5:
		bullet_s->setPosition(X + L, Y + L * sqrt(3));
		break;
	default:
		bullet_s->setPosition(X, Y);
		break;
	}
	bullet_s->setScale(1);
	x = bullet_s->getPositionX();
	y = bullet_s->getPositionY();
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
=======
void Weapon::create(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon0 = select_image(i);
		weapon0->setPosition(x, y);
		weapon0->setScale(1);
	}
}

void Weapon::create1(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon1 = select_image(i);
		weapon1->setPosition(x, y);
		weapon1->setScale(1);
	}
}

void Weapon::create2(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon2 = select_image(i);
		weapon2->setPosition(x, y);
		weapon2->setScale(1);
	}
}

void Weapon::create3(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon3 = select_image(i);
		weapon3->setPosition(x, y);
		weapon3->setScale(1);
	}
}

void Weapon::create4(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon4 = select_image(i);
		weapon4->setPosition(x, y);
		weapon4->setScale(1);
	}
}

void Weapon::create5(float x, float y, int i) {
	if (num[i]) {
		select_data(i);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon5 = select_image(i);
		weapon5->setPosition(x, y);
		weapon5->setScale(1);
>>>>>>> Stashed changes
	}
}