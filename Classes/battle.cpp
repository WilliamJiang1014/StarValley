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

	//创建玩家角色
	Brotato.createPlayer();
	this->addChild(Brotato.sprite);

	//创建信息面板
	Brotato.createInfo();
	this->addChild(Brotato.label);

	weapon.set(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	set_weapon();

	//bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);

	//创建键盘监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(battle::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(battle::OnKeyReleased, this);
	this->schedule(schedule_selector(battle::playermove));
	this->schedule(schedule_selector(battle::playermove2));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	//每帧要做的函数
	this->schedule(schedule_selector(battle::update_per_frame));

	//每秒要做的函数
	this->schedule(schedule_selector(battle::update_per_second), 1);

	//玩家受到伤害结算
	this->schedule(schedule_selector(battle::playerHurt), 0.2);
	this->schedule(schedule_selector(battle::update_per_attack), 1 / (Brotato.attackSpeed + weapon.attackSpeed[0]));
	this->schedule(schedule_selector(battle::update_per_attack1), 1 / (Brotato.attackSpeed + weapon.attackSpeed[1]));
	this->schedule(schedule_selector(battle::update_per_attack2), 1 / (Brotato.attackSpeed + weapon.attackSpeed[2]));
	this->schedule(schedule_selector(battle::update_per_attack3), 1 / (Brotato.attackSpeed + weapon.attackSpeed[3]));
	this->schedule(schedule_selector(battle::update_per_attack4), 1 / (Brotato.attackSpeed + weapon.attackSpeed[4]));
	this->schedule(schedule_selector(battle::update_per_attack5), 1 / (Brotato.attackSpeed + weapon.attackSpeed[5]));
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

	//getCoin();

	remove_weapon();
	weapon.upgrade(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	set_weapon();

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
}

void battle::generate_enemy(float delta) {  //生成敌人
	this->addChild(enemylist.generate_enemy());
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

void battle::set_weapon() {
	if (weapon.num[0]) {
		this->addChild(weapon.weapon0);
	}
	if (weapon.num[1]) {
		this->addChild(weapon.weapon1);
	}
	if (weapon.num[2]) {
		this->addChild(weapon.weapon2);
	}
	if (weapon.num[3]) {
		this->addChild(weapon.weapon3);
	}
	if (weapon.num[4]) {
		this->addChild(weapon.weapon4);
	}
	if (weapon.num[5]) {
		this->addChild(weapon.weapon5);
	}
}

void battle::remove_weapon() {
	if (weapon.num[0]) {
		this->removeChild(weapon.weapon0);
	}
	if (weapon.num[1]) {
		this->removeChild(weapon.weapon1);
	}
	if (weapon.num[2]) {
		this->removeChild(weapon.weapon2);
	}
	if (weapon.num[3]) {
		this->removeChild(weapon.weapon3);
	}
	if (weapon.num[4]) {
		this->removeChild(weapon.weapon4);
	}
	if (weapon.num[5]) {
		this->removeChild(weapon.weapon5);
	}
}

void battle::update_per_attack(float delta) {
	if (weapon.num[0]) {
		if (weapon.isRanged[0] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[0]), (Brotato.Strength + weapon.damage[0]));
	}
}

void battle::update_per_attack1(float delta) {
	if (weapon.num[1]) {
		if (weapon.isRanged[1] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[1]), (Brotato.Strength + weapon.damage[1]));
	}
}

void battle::update_per_attack2(float delta) {
	if (weapon.num[2]) {
		if (weapon.isRanged[2] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[2]), (Brotato.Strength + weapon.damage[2]));
	}
}

void battle::update_per_attack3(float delta) {
	if (weapon.num[3]) {
		if (weapon.isRanged[3] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[3]), (Brotato.Strength + weapon.damage[3]));
	}
}

void battle::update_per_attack4(float delta) {
	if (weapon.num[4]) {
		if (weapon.isRanged[4] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[4]), (Brotato.Strength + weapon.damage[4]));
	}
}

void battle::update_per_attack5(float delta) {
	if (weapon.num[5]) {
		if (weapon.isRanged[0] == true) {
			//发射弹幕
		}
		enemylist.hurt((Brotato.range + weapon.range[5]), (Brotato.Strength + weapon.damage[5]));
	}
}

	//玩家受到伤害结算
void battle::playerHurt(float delta) {
	Brotato.hurt(enemylist.hit_damage());
	getCoin();
}

//拾取金币
void battle::getCoin() {
	Brotato.addMoney(enemylist.collectCoin());
	Sprite* p;
	for (int i = 0; i < 100; i++) {
		p = enemylist.newCoin[i];
		if (p == NULL)
			break;
		else {
			this->addChild(p);
		}
	}
}


// 波结束
bool battle::gameover() 
{
	if (Brotato.gameover())
	{
		wave++;
		Brotato.totalTime += 10;
		Brotato.countdown = Brotato.totalTime;
		enemylist.clear();
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