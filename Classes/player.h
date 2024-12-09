#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

#define init_FULLHP 100;

class Bullet; // ǰ������������������������������������ûд

class Player : public Node
{
private:
	Sprite* player;          // ��Ҿ���

	// �������
	int health;              // ��ǰѪ��
	int maxHealth;           // �������ֵ 
	int attackPower;         // ������
	float speed;             // �ƶ��ٶ�
	float attackSpeed;       // �����ٶȣ�ÿ�빥��������
	float attackRange;       // ������Χ
	float lifeRegen;         // ÿ�������ָ���
	int level;               // �ȼ�
	int experience;          // ��ǰ����ֵ
	int coin;                // ���
	bool isRanged;           // �Ƿ�ΪԶ�̹���ģʽ
	float attackCooldown;    // ������ȴʱ�䣨�ڲ���ʱ����
	float regenCooldown;     // �����ָ���ȴʱ�䣨�ڲ���ʱ����

public:
	// ��ʼ������
	static Player* create();
	virtual bool init();

	// ������ҳ�ʼ����
	void initPlayerAttributes(int characterIndex);

	// �ƶ����ܡ�������������������������������������������������������������������û�Լ�д
	void move(const Vec2& direction, float deltaTime);
	// ��������
	void attack(const vector<Node*>& enemies, float deltaTime);

	// ��ײ��⣨����ʰȡ��ң�
	void checkCollisions(vector<Node*>& coins);

	// �漰���Բ���
	void takeDamage(int damage);                  // �ܵ��˺�
	void regenerateHealth(float deltaTime);       // ����ֵ�ָ�
	void addExperience(int exp);                  // ����ֵ����
	void levelUp();                               // ����
	void addCoin(int amount);                     // ���ӽ��
	bool isDead() const;                          // ����ɫ�Ƿ�����
	
	// ������Ʒ����
	bool buyItem(int itemId);

	// ��ʾ״̬��
	Label* label;
	void createInfo();
	void showInfo();

	// �����߼�
	void update(float dt);


	// ��ȡ
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