#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

#define init_FULLHP 100;

class Bullet; // 前向声明。。。。。。。。。。。。。。还没写

class Player : public Node
{
private:
	Sprite* player;          // 玩家精灵

	// 玩家属性
	int health;              // 当前血量
	int maxHealth;           // 最大生命值 
	int attackPower;         // 攻击力
	float speed;             // 移动速度
	float attackSpeed;       // 攻击速度（每秒攻击次数）
	float attackRange;       // 攻击范围
	float lifeRegen;         // 每秒生命恢复量
	int level;               // 等级
	int experience;          // 当前经验值
	int coin;                // 金币
	bool isRanged;           // 是否为远程攻击模式
	float attackCooldown;    // 攻击冷却时间（内部计时器）
	float regenCooldown;     // 生命恢复冷却时间（内部计时器）

public:
	// 初始化函数
	static Player* create();
	virtual bool init();

	// 设置玩家初始属性
	void initPlayerAttributes(int characterIndex);

	// 移动功能。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。这两个我没自己写
	void move(const Vec2& direction, float deltaTime);
	// 攻击功能
	void attack(const vector<Node*>& enemies, float deltaTime);

	// 碰撞检测（用于拾取金币）
	void checkCollisions(vector<Node*>& coins);

	// 涉及属性操作
	void takeDamage(int damage);                  // 受到伤害
	void regenerateHealth(float deltaTime);       // 生命值恢复
	void addExperience(int exp);                  // 经验值增加
	void levelUp();                               // 升级
	void addCoin(int amount);                     // 增加金币
	bool isDead() const;                          // 检查角色是否死亡
	
	// 购买物品功能
	bool buyItem(int itemId);

	// 显示状态栏
	Label* label;
	void createInfo();
	void showInfo();

	// 更新逻辑
	void update(float dt);


	// 获取
	int getLevel() const;
	Sprite* getPlayerSprite() const;
	int getCoin() const;
	int getHealth() const;
	int getAttackPower() const;
	int getAttackSpeed() const;
	int getAttackRange() const;
	int getLifeRegen() const;

};

#endif 