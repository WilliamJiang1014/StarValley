#ifndef SHOPLAYER_H
#define SHOPLAYER_H

#include "cocos2d.h"
#include "player.h"

USING_NS_CC;

class ShopLayer : public Layer
{
private:
	Player* player;   // 玩家对象
	void closeShop(); // 关闭商店界面
public:
	// 自定义创建场景函数，传入 player 参数
	static Scene* createScene(Player* player);
	// 自定义初始化函数
	static ShopLayer* create(Player* player);
	// 初始化函数
	virtual bool init(Player* player);
};


#endif
