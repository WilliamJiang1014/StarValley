#ifndef __ITEM_H__
#define __ITEM_H__

#include <string>

using namespace std;

class Item
{
public:
    int id;               // ��ƷID
    string name;          // ��Ʒ����
    int cost;             // ��Ʒ�۸�
    int health;           // ����ֵ�ӳ�
    int strength;         // �����ӳ�
    float attackSpeed;    // �����ٶȼӳ�
    int range;            // ������Χ�ӳ�
    float lifeRegen;    // �����ָ��ӳ�

    bool isWeapon;      // �Ƿ�Ϊ����
    bool isRanged;     // �������ͣ���/ǹ��

    Item(int id = 0, string name = "", int cost = 0, int health = 0, int strength = 0, float attackSpeed = 0.0f,
        int range = 0, float lifeRegen = 0.0f, bool isWeapon = false, bool isRanged = false)
        : id(id), name(name), cost(cost), health(health), strength(strength), attackSpeed(attackSpeed), range(range), lifeRegen(lifeRegen), isWeapon(isWeapon), isRanged(isRanged) {}

    // ���غ������������
    void operator()(int id, string name, int cost, int health, int strength,
        float attackSpeed, int range, float lifeRegen, bool isWeapon, bool isRanged)
    {
        this->id = id;
        this->name = name;
        this->cost = cost;
        this->health = health;
        this->strength = strength;
        this->attackSpeed = attackSpeed;
        this->range = range;
        this->lifeRegen = lifeRegen;
        this->isWeapon = isWeapon;
        this->isRanged = isRanged;
    }

};


#endif 
