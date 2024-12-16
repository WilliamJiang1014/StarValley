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
	int Strength;
	int damage;
	//int defence;
	int money;
	int range;

	// new
	float attackSpeed;       // �����ٶȣ�ÿ�빥��������
	float lifeRegen;         // ÿ�������ָ���
	int experience;          // ��ǰ����ֵ
	float regenCooldown;     // �����ָ���ȴʱ�䣨�ڲ���ʱ����


public:
	int HP;
	int countdown;
	int totalTime;
	int speed;

	Sprite* sprite;
	//Sprite* enemy;
	Label* label;

	void createPlayer();
	void init();

	// ������ҳ�ʼ����
	void initPlayerAttributes(int characterIndex);

	// ��ײ��⣨����ʰȡ��ң�
	void checkCollisions(vector<Node*>& coins);
	
	// ���ӽ��
	void addMoney(int amount);

	// ����ֵ�ָ�
	void regenerateHealth(float deltaTime);

	// ����ֵ����
	void addExperience(int exp);

	// ����
	void levelUp();

	// ������Ʒ����
	bool buyItem(int itemId);

	bool dead();
	bool gameover();

	// ״̬����ʾ
	void createInfo();
	void showInfo();

	void hurt(int total_damage); // �ܵ��˺�

	// ��ȡ
	int getAttackSpeed() const;
	int getLifeRegen() const;
	int getMoney() const;
};

#endif 