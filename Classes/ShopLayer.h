#ifndef SHOPLAYER_H
#define SHOPLAYER_H

#include "cocos2d.h"
#include "player.h"

USING_NS_CC;

class ShopLayer : public Layer
{
private:
	Player* player;   // ��Ҷ���
	void closeShop(); // �ر��̵����
public:
	// �Զ��崴���������������� player ����
	static Scene* createScene(Player* player);
	// �Զ����ʼ������
	static ShopLayer* create(Player* player);
	// ��ʼ������
	virtual bool init(Player* player);
};


#endif
