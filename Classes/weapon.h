#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

class Weapon
{
public:
	float x, y;
	float player_x, player_y;

	Sprite* weapon;          // ��������
	int damage;         // ������
	float attackSpeed;       // �����ٶȣ�ÿ�빥��������
	float range;       // ������Χ
	bool isRanged;           // �Ƿ�ΪԶ�̹���ģʽ
	int num;           // ���

	void create(float x, float y);
	void select(int i);

	// �ƶ����ܣ������ͬ����
	void move(float x, float y);


};

#endif 