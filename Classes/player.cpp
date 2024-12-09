#include "cocos2d.h"
#include "player.h"
#include "enemy.h"
#include <string>
#include <cmath>
using namespace cocos2d;
using namespace std;

Player* Player::create()
{
	Player* player = new (nothrow) Player();
	if (player && player->init())
	{
		player->autorelease();
		return player;
	}

	CC_SAFE_DELETE(player);
	return nullptr;
}

bool Player::init()
{
	if (!Node::init())
	{
		return false;
	}

    // 初始化属性
    maxHealth = 100;
    health = maxHealth;
    attackPower = 10;
    speed = 200.0f;     // 移动速度
    attackSpeed = 1.0f; // 每秒攻击次数
    attackRange = 100.0f;
    lifeRegen = 2.0f;   // 每秒恢复2点生命
    level = 1;
    experience = 0;
    coin = 0;
    isRanged = true;

    attackCooldown = 0.0f;
    regenCooldown = 0.0f;
	
	// 根据玩家选择初始化角色
	int selectedCharacter = UserDefault::getInstance()->getIntegerForKey("SelectedCharacter", 0);
	initPlayerAttributes(selectedCharacter);

	// 创建玩家精灵
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	player = Sprite::create("buildings/houses.png");
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7));
	player->setScale(2.5);

	this->addChild(player);

    // 创建状态显示标签
    createInfo();

	return true;
}

void Player::initPlayerAttributes(int characterIndex)
{
    switch (characterIndex)
    {
    case 0: // 角色 1
        health = 100;
        attackPower = 10;
        speed = 150.0f;
        attackSpeed = 1.0f;
        attackRange = 100.0f;
        lifeRegen = 5.0f;
        break;
    case 1: // 角色 2
        health = 120;
        attackPower = 8;
        speed = 130.0f;
        attackSpeed = 1.2f;
        attackRange = 120.0f;
        lifeRegen = 3.0f;
        break;
    case 2: // 角色 3
        health = 80;
        attackPower = 15;
        speed = 170.0f;
        attackSpeed = 0.8f;
        attackRange = 80.0f;
        lifeRegen = 2.0f;
        break;
    case 3: // 角色 4
        health = 150;
        attackPower = 5;
        speed = 100.0f;
        attackSpeed = 1.5f;
        attackRange = 150.0f;
        lifeRegen = 10.0f;
        break;
    case 4: // 角色 5
        health = 90;
        attackPower = 12;
        speed = 140.0f;
        attackSpeed = 1.1f;
        attackRange = 90.0f;
        lifeRegen = 4.0f;
        break;
    default:
        health = 100;
        attackPower = 10;
        speed = 150.0f;
        attackSpeed = 1.0f;
        attackRange = 100.0f;
        lifeRegen = 5.0f;
        break;
    }
}

void Player::checkCollisions(vector<Node*>& coins) 
{
    for (auto it = coins.begin(); it != coins.end();) 
    {
        if (player->getBoundingBox().intersectsRect((*it)->getBoundingBox())) 
        {
            addCoin(10); // 拾取金币增加数量
            (*it)->removeFromParent();
            it = coins.erase(it);
        }
        else 
        {
            ++it;
        }
    }
}

void Player::takeDamage(int damage)
{
    health -= damage;
    if (health < 0) health = 0;
}

void Player::addCoin(int amount)
{
    coin += amount;
}

void Player::regenerateHealth(float deltaTime) 
{
    regenCooldown -= deltaTime;
    if (regenCooldown <= 0) 
    {
        health += lifeRegen;
        if (health > maxHealth) health = maxHealth;
        regenCooldown = 1.0f;
    }
}

void Player::addExperience(int exp) 
{
    experience += exp;
    if (experience >= level * 100) 
    {
        levelUp();
    }
}

void Player::levelUp() 
{
    level++;
    maxHealth += 20;
    attackPower += 5;
    attackSpeed += 0.1f;
    health = maxHealth; // 升级恢复生命
}

bool Player::isDead() const 
{
    return health <= 0;
}

bool Player::buyItem(int itemId) 
{
    const int itemCost[] = { 50, 100, 150, 200, 250 };

    if (itemId < 0 || itemId >= sizeof(itemCost) / sizeof(int)) return false;

    if (coin >= itemCost[itemId]) 
    {
        coin -= itemCost[itemId];
        switch (itemId) 
        {
        case 0:
            maxHealth += 10;
            health += 10;
            break;
        case 1:
            attackPower += 5;
            break;
        case 2:
            attackSpeed += 0.1f;
            break;
        case 3:
            attackRange += 10.0f;
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

void Player::update(float dt) 
{
    regenerateHealth(dt);
    showInfo();
}

void Player::createInfo() 
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	label = Label::createWithTTF("HP: " + to_string(health) + "\n" + "Level: " + to_string(level) + "\n" + "Coin: " + to_string(coin), "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(origin.x + visibleSize.width * 0.05, origin.y + visibleSize.height * 0.9));
}

void Player::showInfo() 
{
	label->setString("HP: " + to_string(health) + "\n" + "Level: " + to_string(level) + "\n" + "Coin: " + to_string(coin));
}

Sprite* Player::getPlayerSprite() const { return player; }
int Player::getCoin() const { return coin; }
int Player::getHealth() const { return health; }
int Player::getAttackPower() const { return attackPower; }
int Player::getAttackSpeed() const { return attackSpeed; }
int Player::getAttackRange() const { return attackRange; }
int Player::getLifeRegen() const { return lifeRegen; }
int Player::getLevel() const { return level; }


