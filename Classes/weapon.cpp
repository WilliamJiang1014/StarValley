#include "cocos2d.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;
#define L 25

void Weapon::upgrade(float x, float y) {
	create(x - L, y + L * sqrt(3), 0);
	create1(x - 2 * L, y, 1);
	create2(x - L, y - L * sqrt(3), 2);
	create3(x + L, y - L * sqrt(3), 3);
	create4(x + 2 * L, y, 4);
	create5(x + L, y + L * sqrt(3), 5);
}

void Weapon::set(float x,float y){
	num[0] = 1;
	num[1] = 1;
	num[2] = 0;
	num[3] = 0;
	num[4] = 0;
	num[5] = 0;
	upgrade(x, y);
}

void Weapon::select_data(int i,int type) {
	switch (type) {
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
		range[i] = 100;
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
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon0 = select_image(num[i]);
		weapon0->setPosition(x, y);
		weapon0->setScale(1);
	}
}

void Weapon::create1(float x, float y, int i) {
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon1 = select_image(num[i]);
		weapon1->setPosition(x, y);
		weapon1->setScale(1);
	}
}

void Weapon::create2(float x, float y, int i) {
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon2 = select_image(num[i]);
		weapon2->setPosition(x, y);
		weapon2->setScale(1);
	}
}

void Weapon::create3(float x, float y, int i) {
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon3 = select_image(num[i]);
		weapon3->setPosition(x, y);
		weapon3->setScale(1);
	}
}

void Weapon::create4(float x, float y, int i) {
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon4 = select_image(num[i]);
		weapon4->setPosition(x, y);
		weapon4->setScale(1);
	}
}

void Weapon::create5(float x, float y, int i) {
	select_data(i, num[i]);
	if (num[i]) {
		auto visibleSize = Director::getInstance()->getVisibleSize();
		weapon5 = select_image(num[i]);
		weapon5->setPosition(x, y);
		weapon5->setScale(1);
	}
}

void Weapon::generate_bullet(float x, float y) {

}