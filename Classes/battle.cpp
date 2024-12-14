#include "cocos2d.h"
#include "battle.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
#define L 25

Layer* battle::createlayer() {
	return Layer::create();
}

bool battle::init() {

	if (!Layer::init())
	{
		return false;
	}
	int wave = 1;

	//创建玩家角色
	Brotato.createPlayer();
	this->addChild(Brotato.sprite);

	Brotato.createInfo();
	this->addChild(Brotato.label);

	//bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);

	weapon1.select(1);
	weapon2.select(0);
	weapon3.select(0);
	weapon4.select(0);
	weapon5.select(0);
	weapon6.select(0);

	if (weapon1.num != 0) {
		weapon1.create(Brotato.sprite->getPositionX() - L * sqrt(3) , Brotato.sprite->getPositionY() + L);
		this->addChild(weapon1.weapon);
	}
	if (weapon2.num != 0) {
		weapon2.create(Brotato.sprite->getPositionX() - L * sqrt(3) , Brotato.sprite->getPositionY() - L);
		this->addChild(weapon1.weapon);
	}
	if (weapon3.num != 0) {
		weapon3.create(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY() - 2 * L);
		this->addChild(weapon1.weapon);
	}
	if (weapon4.num != 0) {
		weapon4.create(Brotato.sprite->getPositionX() + L * sqrt(3) , Brotato.sprite->getPositionY() - L);
		this->addChild(weapon1.weapon);
	}
	if (weapon5.num != 0) {
		weapon5.create(Brotato.sprite->getPositionX() + L * sqrt(3) , Brotato.sprite->getPositionY() + L);
		this->addChild(weapon1.weapon);
	}
	if (weapon6.num != 0) {
		weapon6.create(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY() + 2 * L);
		this->addChild(weapon1.weapon);
	}

	//创建键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(battle::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(battle::OnKeyReleased, this);
	this->schedule(schedule_selector(battle::playermove));
	this->schedule(schedule_selector(battle::playermove2));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	this->schedule(schedule_selector(battle::update_per_frame));
	this->schedule(schedule_selector(battle::update_per_second), 1);
	if (weapon1.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack1), 1 / (Brotato.attackSpeed + weapon1.attackSpeed));
	}
	if (weapon2.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack2), 1 / (Brotato.attackSpeed + weapon2.attackSpeed));
	}
	if (weapon3.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack3), 1 / (Brotato.attackSpeed + weapon3.attackSpeed));
	}
	if (weapon4.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack4), 1 / (Brotato.attackSpeed + weapon4.attackSpeed));
	}
	if (weapon5.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack5), 1 / (Brotato.attackSpeed + weapon5.attackSpeed));
	}
	if (weapon6.num != 0) {
		this->schedule(schedule_selector(battle::update_per_attack6), 1 / (Brotato.attackSpeed + weapon6.attackSpeed));
	}
	this->schedule(schedule_selector(battle::generate_enemy), 5);
	this->schedule(schedule_selector(battle::generate_bullet), 4);

	return true;
}

void battle::playermove(float delta) {   //键盘控制角色移动
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

void battle::playermove2(float delta) {   //键盘控制角色移动
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

void battle::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {  //记录键盘按下的状态
	keyMap[keyCode] = true;
}

void battle::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {  //撤销键盘按下的状态
	keyMap[keyCode] = false;
}

void battle::update_per_frame(float delta) {   //所有每帧都要做的操作

	//Brotato.hurt(enemylist.hit_damage());
	Brotato.showInfo();

	enemylist.update(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	enemylist.move();
	
	if (weapon1.num != 0) {
		weapon1.move(Brotato.sprite->getPositionX() - L * sqrt(3) , Brotato.sprite->getPositionY() + L);
	}
	if (weapon2.num != 0) {
		weapon2.move(Brotato.sprite->getPositionX() - L * sqrt(3) , Brotato.sprite->getPositionY() - L);
	}
	if (weapon3.num != 0) {
		weapon3.move(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY() - 2 * L);
	}
	if (weapon4.num != 0) {
		weapon4.move(Brotato.sprite->getPositionX() + L * sqrt(3) , Brotato.sprite->getPositionY() - L);
	}
	if (weapon5.num != 0) {
		weapon5.move(Brotato.sprite->getPositionX() + L * sqrt(3) , Brotato.sprite->getPositionY() + L);
	}
	if (weapon6.num != 0) {
		weapon6.move(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY() + 2 * L);
	}
	
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

void battle::update_per_second(float delta) {  //所有每秒都要做的操作
	Brotato.countdown--;
	Brotato.hurt(enemylist.hit_damage());
	//Brotato.showInfo();
}

void battle::generate_enemy(float delta) {  //生成敌人
	this->addChild(enemylist.generate_enemy());
	//Brotato.hurt(-1);
}

void battle::generate_bullet(float delta) {
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

void battle::update_per_attack1(float delta) {
	if (weapon1.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range+ weapon1.range), (Brotato.Strength + weapon1.damage));
}

void battle::update_per_attack2(float delta) {
	if (weapon2.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range + weapon2.range), (Brotato.Strength + weapon2.damage));
}

void battle::update_per_attack3(float delta) {
	if (weapon3.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range + weapon3.range), (Brotato.Strength + weapon3.damage));
}

void battle::update_per_attack4(float delta) {
	if (weapon4.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range + weapon4.range), (Brotato.Strength + weapon4.damage));
}

void battle::update_per_attack5(float delta) {
	if (weapon5.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range + weapon5.range), (Brotato.Strength + weapon5.damage));
}

void battle::update_per_attack6(float delta) {
	if (weapon6.isRanged == true) {
		//发射弹幕
	}
	enemylist.hurt((Brotato.range + weapon6.range), (Brotato.Strength + weapon6.damage));
}

// 波结束
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

// 局结束
int battle::totalOver()
{
	if (Brotato.dead()) // 角色死亡
	{
		return -1;
	}
	else if (wave == 10) // 战斗结束
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