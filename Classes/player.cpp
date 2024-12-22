#include "cocos2d.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;



//void player::test() {
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	enemy = Sprite::create("buildings/houses.png");
//	enemy->setPosition(Vec2(origin.x + visibleSize.width / 3, origin.y + visibleSize.height * 0.3));
//	enemy->setScale(2.5);
//}

void player::init() 
{

	FULLHP = init_FULLHP;
	HP = init_FULLHP;
	Level = 1;
    totalTime = 20;
    countdown = totalTime;
	speed = 10;
	Strength = 10;
	attackSpeed = 0; // ÿ�빥������
	range = 0;
	lifeRegen = 2.0f;   // ÿ��ָ�2������
	experience = 0;
	money = 0;

    toBuyItem = true;
    toBuyWeapon = false;
    ifBuyWeapon = false;

    regenCooldown = 1.0f;

	initPlayerAttributes();
}

int player::getCharacterIndex()
{
    // �������ѡ���ʼ����ɫ
    int selectedCharacter = UserDefault::getInstance()->getIntegerForKey("SelectedCharacter", 0);
    return selectedCharacter;
}

void player::initPlayerAttributes()
{
    switch (getCharacterIndex())
    {
    case 0: // ��ɫ 1
        HP = 100;
        Strength = 10;
        speed = 15;
        //attackSpeed = 1.0f;
        //range = 100.0f;
        lifeRegen = 5.0f;
        break;
    case 1: // ��ɫ 2
        HP = 120;
        Strength = 8;
        speed = 8;
        //attackSpeed = 1.2f;
        //range = 120.0f;
        lifeRegen = 3.0f;
        break;
    case 2: // ��ɫ 3
        HP = 80;
        Strength = 15;
        speed = 13;
        //attackSpeed = 0.8f;
        //range = 80.0f;
        lifeRegen = 2.0f;
        break;
    case 3: // ��ɫ 4
        HP = 150;
        Strength = 5;
        speed = 10;
        //attackSpeed = 1.5f;
        //range = 150.0f;
        lifeRegen = 10.0f;
        break;
    case 4: // ��ɫ 5
        HP = 90;
        Strength = 12;
        speed = 5;
        //attackSpeed = 1.1f;
        //range = 90.0f;
        lifeRegen = 4.0f;
        break;
    default:
        HP = 100;
        Strength = 10;
        speed = 15;
        //attackSpeed = 1.0f;
        //range = 100.0f;
        lifeRegen = 5.0f;
        break;
    }
}

void player::checkCollisions(vector<Node*>& coins)
{
    // ��ȡ��ҵı߽��
    Rect playerBoundingBox = sprite->getBoundingBox();

    // �������н��
    for (auto it = coins.begin(); it != coins.end();)
    {
        // ��ȡ��ǰ��ҵı߽��
        Rect coinBoundingBox = (*it)->getBoundingBox();

        // �������뵱ǰ����Ƿ�����ײ
        if (playerBoundingBox.intersectsRect(coinBoundingBox))
        {
            // ���ʰȡ��ң����ӽ������
            addMoney(1);
            (*it)->removeFromParent(); // �ӳ������Ƴ���ǰ���
            it = coins.erase(it); // ʹ��erase�����µĵ��������Լ���������һ��Ԫ��
        }
        else
        {
            it++;
        }
    }
}

bool player::dead() 
{
	if (HP <= 0) 
		return true;
	else
		return false;
}

bool player::gameover() {
	if (countdown <= 0)
		return true;
	else
		return false;
}

void player::createPlayer() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �����û�ѡ����ز�ͬ�Ľ�ɫͼƬ
    string playerImage;
    switch (getCharacterIndex())
    {
    case 0:
        playerImage = "character/character00.png"; // ��ɫ1��ͼƬ
        break;
    case 1:
        playerImage = "character/character01.png"; // ��ɫ2��ͼƬ
        break;
    case 2:
        playerImage = "character/character02.png"; // ��ɫ3��ͼƬ
        break;
    case 3:
        playerImage = "character/character03.png"; // ��ɫ3��ͼƬ
        break;
    case 4:
        playerImage = "character/character04.png"; // ��ɫ3��ͼƬ
        break;
    default:
        playerImage = "character/character00.png"; // Ĭ�Ͻ�ɫͼƬ
        break;
    }
    sprite = Sprite::create(playerImage);
    sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
    sprite->setScale(1);
    init();
}

void player::createInfo()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ������ǩ����
    label = Label::createWithTTF("HP: " + to_string(HP) + "\n" +
        "Level: " + to_string(Level) + "\n" +
        "Time: " + to_string(countdown) + "\n" +
        "Money: " + to_string(money) + "\n\n\n" +
        "FULLHP: " + to_string(FULLHP) + "\n" +
        "Strength: " + to_string(Strength) + "\n" +
        "AttackSpeed: " + to_string(attackSpeed) + "\n" +
        "Range: " + to_string(range) + "\n" +
        "LifeRegen: " + to_string(lifeRegen),
        "fonts/Marker Felt.ttf", 40);

    label->setPosition(Vec2(origin.x + visibleSize.width * 0.1, origin.y + visibleSize.height * 0.7));
}

void player::showInfo() {
    label->setString("HP: " + to_string(HP) + "\n" +
        "Level: " + to_string(Level) + "\n" +
        "Time: " + to_string(countdown) + "\n" +
        "Money: " + to_string(money) + "\n\n\n" +
        "FULLHP: " + to_string(FULLHP) + "\n" +
        "Strength: " + to_string(Strength) + "\n" +
        "AttackSpeed: " + to_string(attackSpeed) + "\n" +
        "Range: " + to_string(range) + "\n" +
        "LifeRegen: " + to_string(lifeRegen));
}

void player::hurt(int total_damage) {
	HP -= total_damage;
    if (total_damage > 0)
        sprite->setColor(Color3B::RED);
    else
        sprite->setColor(Color3B::WHITE);
}

void player::addMoney(int amount)
{
    money += amount;
}

void player::regenerateHealth(float deltaTime)
{
    regenCooldown -= deltaTime;
    if (regenCooldown <= 0)
    {
        HP += lifeRegen;
        if (HP > FULLHP) HP = FULLHP;
        regenCooldown = 1.0f;
    }
}

void player::addExperience(int exp)
{
    experience += exp;
    if (experience >= Level * 100)
    {
        levelUp();
    }
}

void player::levelUp()
{
    Level++;
    FULLHP += 5;
    Strength += 1;
    attackSpeed += 0.1f;
    HP = FULLHP; // �����ָ�����
}

void player::loadItems()
{
    items.push_back(Item(1, "acid_icon", 15, 8, 0, -0.02f, 0, 0.0f));  
    items.push_back(Item(2, "adrenaline_icon", 30, 0, 0, 0.05f, 0, 0.0f)); 
    items.push_back(Item(3, "alien_baby_icon", 20, 15, 0, 0, 0, 0.0f)); 
    items.push_back(Item(4, "alien_magic_icon", 20, 0, 3, 0, 0, 0.0f));
    items.push_back(Item(5, "alien_tongue_icon", 25, 8, 0, 0, 3, 0.0f));
    items.push_back(Item(6, "alien_worm_icon", 25, 0, 0, 0, 0, 1.0f));
    items.push_back(Item(7, "ball_and_chain_icon", 15, 3, 0, 0, 2, 0.0f));
    items.push_back(Item(8, "bandana_icon", 30, 0, 3, 0, 0, 0.0f));
    items.push_back(Item(9, "banner_icon", 50, 0, 0, 0, 50, 5.0f));
    items.push_back(Item(10, "bat_icon", 22, 0, 0, 0.1, 0, 0.0f));
    items.push_back(Item(11, "bean_teacher_icon", 18, 0, 3, 0.1, 0, 0.0f));
    items.push_back(Item(12, "big_arms_icon", 35, 0, 0, 0, 100, 0.0f));
    items.push_back(Item(13, "black_belt_icon", 15, 10, 0, 0, 0, 0.0f));
    items.push_back(Item(14, "blood_donation_icon", 25, 0, 8, 0, 0, 0.0f));
    items.push_back(Item(15, "bowler_hat_icon", 45, 0, 5, 0.05f, 5, 0.0f));
    items.push_back(Item(16, "boxing_glove_icon", 45, 0, 0, 0.1f, 0, 0.0f));
    items.push_back(Item(17, "butterfly_icon", 55, 0, 0, 0.1f, 0, 0.0f));
    items.push_back(Item(18, "cake_icon", 25, 0, 0, 0, 3, 0.0f));
    items.push_back(Item(19, "chameleon_icon", 20, 0, 2, 0, 0, 0.0f));
    items.push_back(Item(20, "anvil_icon", 30, 0, 0, 0, 0, 0.0f));

    items.push_back(Item(21, "cactus_mace", 30, 0, 50, 0.5, 200, 0.0f, true, false));
    items.push_back(Item(22, "chopper", 30, 0, 25, 1.5, 200, 0.0f, true, false));
    items.push_back(Item(23, "claw", 30, 0, 30, 1, 200, 0.0f, true, false));
    items.push_back(Item(24, "double_barrel_shotgun", 30, 0, 90, 0.3, 800, 0.0f, true, true));
    items.push_back(Item(25, "medical_gun", 30, 0, 15, 1, 800, 5.0f, true, true));
    items.push_back(Item(26, "minigun", 30, 0, 5, 2, 800, 0.0f, true, true));
    items.push_back(Item(27, "revolver", 30, 0, 50, 0.5, 800, 0.0f, true, true));
}

void player::updateAttribute(int health, int strength, float attackSpeed_, int range_, float lifeRegen_)
{
    FULLHP += health;
    Strength += strength;
    attackSpeed += attackSpeed_;
    range += range_;
    lifeRegen += lifeRegen_;
}

bool player::buyItem(int itemId)
{
    Item item = items[itemId - 1]; // ��ȡ��Ʒ

    if (money >= item.cost)
    {
        if (item.isWeapon)
        {
            toBuyWeapon = true;
            currentItem = item;  // ���浱ǰѡ�е�����

        }
        else {
            // ������Ʒ�������������
            updateAttribute(item.health, item.strength, item.attackSpeed, item.range, item.lifeRegen);
        }
        money -= item.cost; // �۳����
        purchasedItems.push_back(item);  // ����Ʒ��ӵ��ѹ�����б���
        toBuyItem = true;

        return true;
    }
    return false;
}


int player::getAttackSpeed() const { return attackSpeed; }
int player::getLifeRegen() const { return lifeRegen; }
int player::getMoney() const { return money; }

bool player::getToBuyWeapon() const { return toBuyWeapon; }
Item player::getCurrentItem() const { return currentItem; }  // ��ȡ��ǰѡ�е���Ʒ

void player::updateIfBuyWeapon()
{
    ifBuyWeapon = !ifBuyWeapon;
}
void player::updateToBuyWeapon()
{
    toBuyWeapon = !toBuyWeapon;
}