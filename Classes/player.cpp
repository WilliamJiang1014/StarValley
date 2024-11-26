#include "cocos2d.h"
#include "player.h"
using namespace cocos2d;


void player::controlPlayer() {
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(player::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}




Sprite* player::createPlayer() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto Player = Sprite::create("buildings/houses.png");
	Player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	Player->setScale(2.5);
	return Player;
}


void player::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		auto up = MoveBy::create(1, Vec2(0, 500));
		Player->runAction(up);
	}
}

