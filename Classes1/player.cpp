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
    totalTime = 30;
    countdown = totalTime;
	speed = 10;
	Strength = 10;
	attackSpeed = 1.0f; // 每秒攻击次数
	range = 100;
	lifeRegen = 2.0f;   // 每秒恢复2点生命
	experience = 0;
	money = 0;

    regenCooldown = 1.0f;

	// 根据玩家选择初始化角色
	int selectedCharacter = UserDefault::getInstance()->getIntegerForKey("SelectedCharacter", 0);
	initPlayerAttributes(selectedCharacter);
}

void player::initPlayerAttributes(int characterIndex)
{
    switch (characterIndex)
    {
    case 0: // 角色 1
        HP = 100;
        Strength = 10;
        speed = 15;
        attackSpeed = 1.0f;
        range = 100.0f;
        lifeRegen = 5.0f;
        break;
    case 1: // 角色 2
        HP = 120;
        Strength = 8;
        speed = 8;
        attackSpeed = 1.2f;
        range = 120.0f;
        lifeRegen = 3.0f;
        break;
    case 2: // 角色 3
        HP = 80;
        Strength = 15;
        speed = 13;
        attackSpeed = 0.8f;
        range = 80.0f;
        lifeRegen = 2.0f;
        break;
    case 3: // 角色 4
        HP = 150;
        Strength = 5;
        speed = 10;
        attackSpeed = 1.5f;
        range = 150.0f;
        lifeRegen = 10.0f;
        break;
    case 4: // 角色 5
        HP = 90;
        Strength = 12;
        speed = 5;
        attackSpeed = 1.1f;
        range = 90.0f;
        lifeRegen = 4.0f;
        break;
    default:
        HP = 100;
        Strength = 10;
        speed = 15;
        attackSpeed = 1.0f;
        range = 100.0f;
        lifeRegen = 5.0f;
        break;
    }
}

void player::checkCollisions(vector<Node*>& coins)
{
    // 获取玩家的边界框
    Rect playerBoundingBox = sprite->getBoundingBox();

    // 遍历所有金币
    for (auto it = coins.begin(); it != coins.end();)
    {
        // 获取当前金币的边界框
        Rect coinBoundingBox = (*it)->getBoundingBox();

        // 检查玩家与当前金币是否发生碰撞
        if (playerBoundingBox.intersectsRect(coinBoundingBox))
        {
            // 玩家拾取金币，增加金币数量
            addMoney(1);
            (*it)->removeFromParent(); // 从场景中移除当前金币
            it = coins.erase(it); // 使用erase返回新的迭代器，以继续遍历下一个元素
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
	sprite = Sprite::create("buildings/houses.png");
	sprite->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	sprite->setScale(2.5);
	init();
}

void player::createInfo() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	label = Label::createWithTTF("HP: " + to_string(HP) + "\n" + "Level: " + to_string(Level) + "\n" + "Time: " + to_string(countdown), "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.9));
}

void player::showInfo() {
	label->setString("HP: " + to_string(HP) + "\n" + "Level: " + to_string(Level) + "\n" + "Time: " + to_string(countdown));
}

void player::hurt(int total_damage) {
	HP -= total_damage;
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
    FULLHP += 20;
    Strength += 5;
    attackSpeed += 0.1f;
    HP = FULLHP; // 升级恢复生命
}

bool player::buyItem(int itemId)
{
    const int itemCost[] = { 50, 100, 150, 200, 250 };

    if (itemId < 0 || itemId >= sizeof(itemCost) / sizeof(int)) return false;

    if (money >= itemCost[itemId])
    {
        money -= itemCost[itemId];
        switch (itemId)
        {
        case 0:
            FULLHP += 10;
            HP += 10;
            break;
        case 1:
            Strength += 5;
            break;
        case 2:
            attackSpeed += 0.1f;
            break;
        case 3:
            range += 10;
            break;
        case 4:
            lifeRegen += 1.0f;
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

int player::getAttackSpeed() const { return attackSpeed; }
int player::getLifeRegen() const { return lifeRegen; }
int player::getMoney() const { return money; }
