#include "Home.h"
#include "player.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

Scene* home::createScene() {
	return home::create();
}

bool home::init() {

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	player1 = Sprite::create("buildings/houses.png");
	player1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	player1->setScale(2.5);
	this->addChild(player1, 0);
	
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(home::OnKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}



void home::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		auto up = MoveBy::create(0.2, Vec2(0, 20));
		player1->runAction(up);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		auto up = MoveBy::create(0.2, Vec2(-20, 0));
		player1->runAction(up);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		auto up = MoveBy::create(0.2, Vec2(0, -20));
		player1->runAction(up);
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		auto up = MoveBy::create(0.2, Vec2(20, 0));
		player1->runAction(up);
	}
}




