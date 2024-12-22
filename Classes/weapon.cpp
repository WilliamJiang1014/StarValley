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

void Weapon::init(float x,float y){
	last = new bullet(-1, -1, -1, -1, 0, NULL, 0);
	first = new bullet(-1, -1, -1, -1, 0, last, 0);

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
		items[0].id = 22;
		items[0].name = "chopper";
		items[0].cost = 30;
		items[0].health = 0;
		items[0].strength = 30;
		items[0].attackSpeed = 0.15f;
		items[0].range = 200;
		items[0].isWeapon = true;
		items[0].isRanged = false;
		break;
	case 3:
	case 4:
		items[0].id = 25;
		items[0].name = "medical_gun";
		items[0].cost = 30;
		items[0].health = 0;
		items[0].strength = 50;
		items[0].attackSpeed = 0.1f;
		items[0].range = 500;
		items[0].isWeapon = true;
		items[0].isRanged = true;
		break;
	}

	create(x, y);
}

bool Weapon::addWeapon(const Item& item)
{
	// ���ҿյ�������
	for (int i = 1; i < 6; i++)
	{
		if (num[i] == 0)
		{
			// �ҵ��ղۣ��������
			num[i] = 1;
			items[i] = item;
			return true;
		}
	}
	//// ���û�пղۣ�����Ƿ�����ͬ����
	//for (int i = 0; i < 6; i++) 
	//{
	//	if (num[i] == type) 
	//	{
	//		// ��������
	//		upgradeWeapon(i);
	//		return true;
	//	}
	//}
	//// ���������������û����ͬ����������ʧ��
	//return false;

	// ������в۶�����û��ƥ�������������ʧ��
	return false;
}


void Weapon::select_data(int i) {
	// .................................................
	damage[i] = items[i].strength;
	attackSpeed[i] = items[i].attackSpeed;
	range[i] = items[i].range;
	isRanged[i] = items[i].isRanged;
}

Sprite* Weapon::select_image(int i) {
	string weaponImage = "weapon/" + items[i].name + ".png";
	return Sprite::create(weaponImage);
}

void Weapon::create(float x, float y) {
	for (int i = 0; i < 6; i++) 
	{
		if (num[i]) 
		{
			select_data(i);
			Sprite* p = select_image(i);
			weapon[i] = p;
			switch (i) 
			{
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
		//��λ��ÿ����������
		direction_x = dx / (sqrt(dx * dx + dy * dy));
		direction_y = dy / (sqrt(dx * dx + dy * dy));
	}

}

Sprite* bullet::select_bullet(int i) {
	Sprite* bulletSprite = nullptr;

	if (weapon.items[i].id == 24) {
		bulletSprite = Sprite::create("weapon/bullet_shredder_0000.png");
	}
	else if (weapon.items[i].id == 25) {
		bulletSprite = Sprite::create("weapon/bullet_medical.png");
	}
	else if (weapon.items[i].id == 26) {
		bulletSprite = Sprite::create("weapon/frame0001.png");
	}
	else {
		bulletSprite = Sprite::create("weapon/bullet_shredder_0000.png");
	}
	// ������Ļ����Ĵ�СΪԭ���� 0.5 ��
	bulletSprite->setScale(0.5f);

	return bulletSprite;
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