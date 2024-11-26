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

	//��ȡ���ڴ�С
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//������ҽ�ɫ
	player1 = Sprite::create("buildings/houses.png");
	player1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	player1->setScale(2.5);
	this->addChild(player1, 0);
	
	//bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);


	//�������̼���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(home::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(home::OnKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//ÿһ֡����һ�ν�ɫ�ƶ�����
	this->schedule(schedule_selector(home::move));
	this->schedule(schedule_selector(home::move2),0.2);

	return true;
}


void home::move(float delta) {   //���̿��ƽ�ɫ�ƶ�
	auto w = EventKeyboard::KeyCode::KEY_W;
	auto s = EventKeyboard::KeyCode::KEY_S;
	auto a = EventKeyboard::KeyCode::KEY_A;
	auto d = EventKeyboard::KeyCode::KEY_D;
	if (keyMap[w]==true) {
		if (player1->getPositionY() <  1080)
			player1->setPositionY(player1->getPositionY() + 10);
	}
	if (keyMap[a] == true) {
		if(player1->getPositionX()>0)
			player1->setPositionX(player1->getPositionX() - 10);
	}
	if (keyMap[s] == true) {
		if (player1->getPositionY() > 0)
			player1->setPositionY(player1->getPositionY() - 10);
	}
	if (keyMap[d] == true) {
		if (player1->getPositionX() < 1920)
			player1->setPositionX(player1->getPositionX() + 10);
	}
}

void home::move2(float delta) {   //���̿��ƽ�ɫ�ƶ�
	auto i = EventKeyboard::KeyCode::KEY_I;
	auto k = EventKeyboard::KeyCode::KEY_K;
	auto j = EventKeyboard::KeyCode::KEY_J;
	auto l = EventKeyboard::KeyCode::KEY_L;
	if (keyMap[i] == true) {
		if (player1->getPositionY() < 1080) 
			player1->setPositionY(player1->getPositionY() + 10);
	}
	if (keyMap[j] == true) {
		if (player1->getPositionX() > 0)
			player1->setPositionX(player1->getPositionX() - 10);
	}
	if (keyMap[k] == true) {
		if (player1->getPositionY() > 0)
			player1->setPositionY(player1->getPositionY() - 10);
	}
	if (keyMap[l] == true) {
		if (player1->getPositionX() < 1920)
			player1->setPositionX(player1->getPositionX() + 10);
	}
}




void home::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {  //��¼���̰��µ�״̬
	keyMap[keyCode] = true;
}

void home::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {  //�������̰��µ�״̬
	keyMap[keyCode] = false;
}




