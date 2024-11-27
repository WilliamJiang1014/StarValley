#include "cocos2d.h"
#include "player.h"
#include <string>
using namespace cocos2d;
using namespace std;


void player::test() {
	//sprite->setPositionY(sprite->getPositionY() + 10);
}

void player::init() {
	FULLHP = init_FULLHP;
	HP = init_FULLHP;
	Level = 1;

}

bool player::dead() {
	if (HP <= 0) 
		return true;
	else
		return false;
}

void player::createPlayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite = Sprite::create("buildings/houses.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	sprite->setScale(2.5);
	init();
}

void player::createInfo() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	label = Label::createWithTTF("HP: " + to_string(HP) + "\n" + "Level: " + to_string(Level), "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.9));
}

void player::showInfo() {
	label->setString("HP: " + to_string(HP) + "\n" + "Level: " + to_string(Level));
}