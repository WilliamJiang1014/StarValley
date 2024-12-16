#include "cocos2d.h"
#include "battle.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Layer* battle::createlayer() {
	return Layer::create();
}

bool battle::init() {

	if (!Layer::init())
	{
		return false;
	}
	int wave = 1;

	//������ҽ�ɫ
	Brotato.createPlayer();
	this->addChild(Brotato.sprite);

	Brotato.createInfo();
	this->addChild(Brotato.label);

	//bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);


	//�������̼���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(battle::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(battle::OnKeyReleased, this);
	this ->schedule(schedule_selector(battle::playermove));
	this->schedule(schedule_selector(battle::playermove2));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(battle::update_per_frame));
	this->schedule(schedule_selector(battle::update_per_second), 1);
	this->schedule(schedule_selector(battle::generate_enemy), 5);
	this->schedule(schedule_selector(battle::generate_bullet), 4);

	return true;
}

void battle::playermove(float delta) {   //���̿��ƽ�ɫ�ƶ�
	auto w = EventKeyboard::KeyCode::KEY_W;
	auto s = EventKeyboard::KeyCode::KEY_S;
	auto a = EventKeyboard::KeyCode::KEY_A;
	auto d = EventKeyboard::KeyCode::KEY_D;
	if (keyMap[w] == true) {
		if (Brotato.sprite->getPositionY() < 1080)
			Brotato.sprite->setPositionY(Brotato.sprite->getPositionY() + Brotato.speed);
	}
	if (keyMap[a] == true) {
		if (Brotato.sprite->getPositionX() > 0)
			Brotato.sprite->setPositionX(Brotato.sprite->getPositionX() - Brotato.speed);
	}
	if (keyMap[s] == true) {
		if (Brotato.sprite->getPositionY() > 0)
			Brotato.sprite->setPositionY(Brotato.sprite->getPositionY() - Brotato.speed);
	}
	if (keyMap[d] == true) {
		if (Brotato.sprite->getPositionX() < 1920)
			Brotato.sprite->setPositionX(Brotato.sprite->getPositionX() + Brotato.speed);
	}
}

void battle::playermove2(float delta) {   //���̿��ƽ�ɫ�ƶ�
	auto i = EventKeyboard::KeyCode::KEY_I;
	auto k = EventKeyboard::KeyCode::KEY_K;
	auto j = EventKeyboard::KeyCode::KEY_J;
	auto l = EventKeyboard::KeyCode::KEY_L;
	if (keyMap[i] == true) {
		if (Brotato.sprite->getPositionY() < 1080)
			Brotato.sprite->setPositionY(Brotato.sprite->getPositionY() + 10);
	}
	if (keyMap[j] == true) {
		if (Brotato.sprite->getPositionX() > 0)
			Brotato.sprite->setPositionX(Brotato.sprite->getPositionX() - 10);
	}
	if (keyMap[k] == true) {
		if (Brotato.sprite->getPositionY() > 0)
			Brotato.sprite->setPositionY(Brotato.sprite->getPositionY() - 10);
	}
	if (keyMap[l] == true) {
		if (Brotato.sprite->getPositionX() < 1920)
			Brotato.sprite->setPositionX(Brotato.sprite->getPositionX() + 10);
	}
}

void battle::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {  //��¼���̰��µ�״̬
	keyMap[keyCode] = true;
}

void battle::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {  //�������̰��µ�״̬
	keyMap[keyCode] = false;
}

void battle::update_per_frame(float delta) {   //����ÿ֡��Ҫ���Ĳ���

	//Brotato.hurt(enemylist.hit_damage());
	Brotato.showInfo();

	enemylist.update(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	enemylist.move();

	/*
	if (Brotato.dead()) {
		auto scene_helloworld = HelloWorld::createScene();
		Director::getInstance()->replaceScene(CCTransitionFade::create(0.8f, scene_helloworld));
	}
	if (Brotato.gameover()) {
		//auto scene_helloworld = home::createScene();
		//Director::getInstance()->replaceScene(CCTransitionFade::create(0.8f, scene_helloworld));
		this->removeChild(battle);
	}

	*/
}

void battle::update_per_second(float delta) {  //����ÿ�붼Ҫ���Ĳ���
	Brotato.countdown--;
	Brotato.hurt(enemylist.hit_damage());
	//Brotato.hurt(enemylist.hit_damage());
	//Brotato.showInfo();
}

void battle::generate_enemy(float delta) {  //���ɵ���
	this->addChild(enemylist.generate_enemy());
	//Brotato.hurt(-1);
}

void battle::generate_bullet(float delta) {  //Զ�̵��˹��������ӵ�
	enemylist.generate_bullet();
	Sprite* p;
	for (int i = 0; i < 100; i++) {
		p = enemylist.newBullet[i];
		if (p == NULL)
			break;
		else
			this->addChild(p);
	}
}



// ������
bool battle::gameover() 
{
	if (Brotato.gameover())
	{
		wave++;
		Brotato.totalTime += 10;
		Brotato.countdown = Brotato.totalTime;
		return true;
	}
	else
		return false;
}

// �ֽ���
int battle::totalOver()
{
	if (Brotato.dead()) // ��ɫ����
	{
		return -1;
	}
	else if (wave == 10) // ս������
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool battle::dead() 
{
	if (Brotato.dead())
		return true;
	else
		return false;
}

player* battle::getPlayer()
{
	player* p = &Brotato;
	return p;
}