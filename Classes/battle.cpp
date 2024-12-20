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

	//������Ϣ���
	Brotato.createInfo();
	this->addChild(Brotato.label);

	weapon.init(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	set_weapon();

	//bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("bgm/BGM02.wav", true);

	//�������̼���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(battle::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(battle::OnKeyReleased, this);
	this->schedule(schedule_selector(battle::playermove));
	this->schedule(schedule_selector(battle::playermove2));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);


	//ÿ֡Ҫ���ĺ���
	this->schedule(schedule_selector(battle::update_per_frame));

	//ÿ��Ҫ���ĺ���
	this->schedule(schedule_selector(battle::update_per_second), 1);

	//����ܵ��˺�����
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

void battle::updatePurchasedItemsUI()
{
	// ��ȡ���ڴ�С
	auto winSize = Director::getInstance()->getWinSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	// ��ȡ��Ҷ���
	player* p = getPlayer();

	// �����ѹ�����Ʒ����ʾ
	for (int i = 0; i < p->purchasedItems.size(); i++)
	{
		string itemImage = (p->purchasedItems[i].isWeapon ? "weapon/" : "Item/") + p->purchasedItems[i].name + ".png";
		auto itemSprite = Sprite::create(itemImage);

		itemSprite->setPosition(Vec2(winSize.width - 50, winSize.height - 50 - i * 70));  // ���Ҳ���������
		itemSprite->setScale(0.5f); // ��С��ʾ�ߴ�
		this->addChild(itemSprite); // ����Ʒͼ����ӵ���ǰ��
	}
}

// �������������߼�
void battle::purchaseWeapon(Item item)
{
	// �ж��������Ƿ��п�λ�����п�λ����룬�����������е�����
	if (weapon.addWeapon(item))
	{
		// ������ӳɹ������Ϊ�������
		Brotato.updateToBuyWeapon();
		Brotato.updateIfBuyWeapon();

		/*bool* ptr1 = Brotato.getIfBuyWeapon();
		*ptr1 = false;*/
	}
	else
	{
		// ����ʧ�ܣ����磬������������
		CCLOG("Cannot add more weapons or no matching weapon found.");
	}

}


void battle::update_per_frame(float delta) {   //����ÿ֡��Ҫ���Ĳ���

	//Brotato.hurt(enemylist.hit_damage());
	Brotato.showInfo();

	// �����ѹ�����Ʒ UI ........................................................
	updatePurchasedItemsUI();

	enemylist.update(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	enemylist.move();

	// �������Ƿ���������������
	if (Brotato.getToBuyWeapon())
	{
		Item item = Brotato.getCurrentItem();
		purchaseWeapon(item);
	}

	remove_weapon();
	weapon.create(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY());
	set_weapon();

	weapon.bullet_move();
	enemyhurt();

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
}

void battle::generate_enemy(float delta) {  //���ɵ���
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
	for (int i = 0; i < 6; i++) {
		if (weapon.num[i]) {
			this->addChild(weapon.weapon[i]);
		}
	}
}

void battle::remove_weapon() {
	for (int i = 0; i < 6; i++) {
		if (weapon.num[i]) {
			this->removeChild(weapon.weapon[i]);
		}
	}
}

void battle::bullet(float X, float Y, float enemy_X, float enemy_Y, int damage, int i) {
	weapon.generate_bullet(X, Y, enemy_X, enemy_Y, damage, i);
	Sprite* p;
	p = weapon.newbullet;
	if (p != NULL)
		this->addChild(p);
}

void battle::enemyhurt() {
	while (weapon.bullet_hit() != weapon.last) {
		Sprite* p = weapon.bullet_hit()->bullet_s;
		enemylist.hurt(p->getPositionX(), p->getPositionY(), 150, weapon.bullet_hit()->bullet_damage);
		weapon.bullet_clear(weapon.bullet_hit());
		this->removeChild(p);
	}
}

void battle::update_per_attack(float delta) {
	if (weapon.num[0]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[0])) {
			if (weapon.isRanged[0] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(),enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()),enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[0], 0);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(),(Brotato.range + weapon.range[0]), (Brotato.Strength + weapon.damage[0]));
			}
		}
	}
}

void battle::update_per_attack1(float delta) {
	if (weapon.num[1]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[1])) {
			if (weapon.isRanged[1] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[1], 1);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), (Brotato.range + weapon.range[1]), (Brotato.Strength + weapon.damage[1]));
			}
		}
	}
}

void battle::update_per_attack2(float delta) {
	if (weapon.num[2]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[2])) {
			if (weapon.isRanged[2] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[2], 2);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), (Brotato.range + weapon.range[2]), (Brotato.Strength + weapon.damage[2]));
			}
		}
	}
}

void battle::update_per_attack3(float delta) {
	if (weapon.num[3]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[3])) {
			if (weapon.isRanged[3] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[3], 3);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), (Brotato.range + weapon.range[3]), (Brotato.Strength + weapon.damage[3]));
			}
		}
	}
}

void battle::update_per_attack4(float delta) {
	if (weapon.num[4]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[4])) {
			if (weapon.isRanged[4] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[4], 4);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), (Brotato.range + weapon.range[4]), (Brotato.Strength + weapon.damage[4]));
			}
		}
	}
}

void battle::update_per_attack5(float delta) {
	if (weapon.num[5]) {
		if (enemylist.nearestDistance(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()) <= (Brotato.range + weapon.range[5])) {
			if (weapon.isRanged[5] == true) {
				bullet(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), enemylist.nearestX(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), enemylist.nearestY(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY()), Brotato.Strength + weapon.damage[5], 5);//���䵯Ļ
			}
			else {
				enemylist.hurt(Brotato.sprite->getPositionX(), Brotato.sprite->getPositionY(), (Brotato.range + weapon.range[5]), (Brotato.Strength + weapon.damage[5]));
			}
		}
	}
}

	//����ܵ��˺�����
void battle::playerHurt(float delta) {
	Brotato.hurt(enemylist.hit_damage());
	getCoin();
}

//ʰȡ���
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


//ֹͣ���к�������
void battle::stopSchedule() {
	this->unschedule(schedule_selector(battle::update_per_frame));
	this->unschedule(schedule_selector(battle::update_per_second));
	this->unschedule(schedule_selector(battle::playerHurt));
	this->unschedule(schedule_selector(battle::update_per_attack));
	this->unschedule(schedule_selector(battle::update_per_attack1));
	this->unschedule(schedule_selector(battle::update_per_attack2));
	this->unschedule(schedule_selector(battle::update_per_attack3));
	this->unschedule(schedule_selector(battle::update_per_attack4));
	this->unschedule(schedule_selector(battle::update_per_attack5));
	this->unschedule(schedule_selector(battle::generate_enemy));
	this->unschedule(schedule_selector(battle::generate_bullet));
}

//��ʼ���к�������
void battle::startSchedule() {
	this->schedule(schedule_selector(battle::update_per_frame));

	//ÿ��Ҫ���ĺ���
	this->schedule(schedule_selector(battle::update_per_second), 1);

	//����ܵ��˺�����
	this->schedule(schedule_selector(battle::playerHurt), 0.2);
	this->schedule(schedule_selector(battle::update_per_attack), 1 / (Brotato.attackSpeed + weapon.attackSpeed[0]));
	this->schedule(schedule_selector(battle::update_per_attack1), 1 / (Brotato.attackSpeed + weapon.attackSpeed[1]));
	this->schedule(schedule_selector(battle::update_per_attack2), 1 / (Brotato.attackSpeed + weapon.attackSpeed[2]));
	this->schedule(schedule_selector(battle::update_per_attack3), 1 / (Brotato.attackSpeed + weapon.attackSpeed[3]));
	this->schedule(schedule_selector(battle::update_per_attack4), 1 / (Brotato.attackSpeed + weapon.attackSpeed[4]));
	this->schedule(schedule_selector(battle::update_per_attack5), 1 / (Brotato.attackSpeed + weapon.attackSpeed[5]));
	this->schedule(schedule_selector(battle::generate_enemy), 5);
	this->schedule(schedule_selector(battle::generate_bullet), 4);
}

// ������
bool battle::gameover() 
{
	if (Brotato.gameover())
	{
		wave++;
		Brotato.totalTime += 10;
		Brotato.countdown = Brotato.totalTime;
		enemylist.clear();
		stopSchedule();
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