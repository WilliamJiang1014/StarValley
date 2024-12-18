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

	Sprite* weapon0,* weapon1,* weapon2,* weapon3,* weapon4,* weapon5;   // ��������
	int damage[6];         // ������
	float attackSpeed[6];       // �����ٶȣ�ÿ�빥��������
	float range[6];       // ������Χ
	bool isRanged[6];           // �Ƿ�ΪԶ�̹���ģʽ
	int num[6];           // ���

	void upgrade(float x,float y);
	void set(float x, float y);
	void select_data(int i,int type);
	Sprite* select_image(int tpye);
	void create(float x, float y, int i);
	void create1(float x, float y, int i);
	void create2(float x, float y, int i);
	void create3(float x, float y, int i);
	void create4(float x, float y, int i);
	void create5(float x, float y, int i);

	Sprite* newbullet[99999];
	void generate_bullet(float x, float y);

};

#endif 