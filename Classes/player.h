#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Item.h"
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
	float lifeRegen;         // ÿ�������ָ���
	int experience;          // ��ǰ����ֵ
	float regenCooldown;     // �����ָ���ȴʱ�䣨�ڲ���ʱ����

	// ��������
	bool toBuyWeapon; // ���ھ����Ƿ�����battle�е�����������
	bool ifBuyWeapon; // �ж������Ƿ���ɹ�
	Item currentItem;   // ��ǰѡ�����Ʒ��������

public:
	int Strength;
	int damage;
	int range;
	float attackSpeed;       // �����ٶȣ�ÿ�빥��������
	int HP;
	int countdown;
	int totalTime;
	int speed;

	bool toBuyItem;
	// �洢���пɹ������Ʒ
	vector<Item> items;
	// ����ѹ�����Ʒ
	vector<Item> purchasedItems;
	// ��������
	void updateAttribute(int health, int strength, float attackSpeed, int range, float lifeRegen);

	Sprite* sprite;
	//Sprite* enemy;
	Label* label;

	void createPlayer();
	void init();

	// ����������Ʒ
	void loadItems();

	// ������ҳ�ʼ����
	void initPlayerAttributes();

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

	int getCharacterIndex();
	bool getToBuyWeapon() const;
	Item getCurrentItem() const;

	void updateToBuyWeapon();
	void updateIfBuyWeapon();
};

#endif 