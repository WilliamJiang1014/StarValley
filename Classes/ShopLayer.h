#ifndef SHOPLAYER_H
#define SHOPLAYER_H

#include "cocos2d.h"
#include "player.h"
#include <vector>

USING_NS_CC;

class ShopLayer : public Layer
{
private:
	player* p;   // ��Ҷ���
	Label* coinLabel;
	bool end;
	vector<Item> shopItems;

public:
	// �Զ��崴���������������� player ����
	static Scene* createScene(player* p);
	// �Զ����ʼ������
	static ShopLayer* create(player* p);
	// ��ʼ������
	virtual bool init(player* p);

	// ��ʼ���̵����
	void createShopUI();
	bool toEnd();
};


#endif
