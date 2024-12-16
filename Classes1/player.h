#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

#define init_FULLHP 100;

class player 
{
private:
	int FULLHP;
	int Level;
	//int defence;
	int money;

	// new
	float lifeRegen;         // 每秒生命恢复量
	int experience;          // 当前经验值
	float regenCooldown;     // 生命恢复冷却时间（内部计时器）


public:
	int Strength;
	int damage;
	int range;
	float attackSpeed;       // 攻击速度（每秒攻击次数）
	int HP;
	int countdown;
	int totalTime;
	int speed;

	Sprite* sprite;
	//Sprite* enemy;
	Label* label;

	void createPlayer();
	void init();

	// 设置玩家初始属性
	void initPlayerAttributes(int characterIndex);

	// 碰撞检测（用于拾取金币）
	void checkCollisions(vector<Node*>& coins);
	
	// 增加金币
	void addMoney(int amount);

	// 生命值恢复
	void regenerateHealth(float deltaTime);

	// 经验值增加
	void addExperience(int exp);

	// 升级
	void levelUp();

	// 购买物品功能
	bool buyItem(int itemId);

	bool dead();
	bool gameover();

	// 状态栏显示
	void createInfo();
	void showInfo();

	void hurt(int total_damage); // 受到伤害

	// 获取
	int getAttackSpeed() const;
	int getLifeRegen() const;
	int getMoney() const;
};

#endif 