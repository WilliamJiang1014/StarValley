#include "ShopLayer.h"
#include "player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* ShopLayer::createScene(player* p)
{
	auto scene = Scene::create();
	auto layer = ShopLayer::create(p); // 需要手动创建对象
	layer->init(p);
	scene->addChild(layer);

	return scene;
}

ShopLayer* ShopLayer::create(player* p)
{
	// 手动创建对象
	ShopLayer* layer = new (nothrow) ShopLayer();
	if (layer && layer->init(p))
	{
		layer->autorelease();
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool ShopLayer::init(player* p)
{
	if (!Layer::init())
	{
		return false;
	}
	this->p = p;
	end = false;

	// 创建商店界面UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// 显示玩家的当前金币
	auto coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 24);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// 创建购买物品的按钮
	for (int i = 0; i < 5; i++)
	{
		auto buyButton = ui::Button::create("HelloWorld.png", "HelloWorld.png", "HelloWorld.png");
		buyButton->setTitleText("Item " + std::to_string(i + 1));
		buyButton->setTitleFontSize(24);
		buyButton->setPosition(Vec2(winSize.width / 2, winSize.height - (i + 2) * 100));

		buyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) 
			{
			if (type == ui::Widget::TouchEventType::ENDED) 
			{
				// 购买物品
				if (p->buyItem(i)) 
				{
					log("Item %d purchased!", i);  // 输出购买成功的日志
				}
				else 
				{
					log("Not enough coins to buy item %d", i); // 输出购买失败的日志
				}
			}
			});
		this->addChild(buyButton);
	}

	// 创建关闭商店按钮
	auto closeButton = ui::Button::create("HelloWorld.png", "HelloWorld.png");
	closeButton->setTitleText("End");
	closeButton->setPosition(Vec2(winSize.width - 50, winSize.height - 50));
	closeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) 
		{
		if (type == ui::Widget::TouchEventType::ENDED) 
		{
			end = true;
		}
		});
	this->addChild(closeButton);
	
}

bool ShopLayer::toEnd() { return end; }

