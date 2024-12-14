#include "cocos2d.h"
#include "weapon.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;

void Weapon::create(float x, float y) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	weapon = Sprite::create("buildings/houses.png");
	weapon->setPosition(x,y);
	weapon->setScale(1);
}

void Weapon::select(int i) {
	switch (i) {
	case 0:
		damage = 0;
		attackSpeed = 0;
		range = 0;
		isRanged = false;
		num = 0;
		break;
	case 1:
		damage = 5;
		attackSpeed = 1.0f;
		range = 100;
		isRanged = true;
		num = 1;
		break;
	case 2:
		damage = 10;
		attackSpeed = 1.0f;
		range = 0;
		isRanged = false;
		num = 2;
		break;
	default:
		damage = 0;
		attackSpeed = 0;
		range = 0;
		isRanged = false;
		num = 0;
		break;
	}
}

void Weapon::move(float x, float y) {
	weapon->setPosition(x, y);
}