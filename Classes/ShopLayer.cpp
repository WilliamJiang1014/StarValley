#include "cocos2d.h"
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

	// 加载物品
	p->loadItems();
	srand(time(0)); // 初始化随机种子
	while (shopItems.size() < 5)
	{
		int randomIndex = rand() % p->items.size();
		Item randomItem = p->items[randomIndex];
		shopItems.push_back(randomItem);
	}
	// 创建商店界面UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// 显示玩家的当前金币
	coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 24);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// 创建购买物品的按钮
	for (int i = 0; i < shopItems.size(); i++)
	{
		string itemImage = (shopItems[i].isWeapon ? "weapon/" : "Item/") + shopItems[i].name + ".png";
		auto buyButton = ui::Button::create(itemImage, itemImage, itemImage);
		buyButton->setTitleText(shopItems[i].name);
		buyButton->setTitleFontSize(24);
		buyButton->setPosition(Vec2(winSize.width / 2, winSize.height - (i + 2) * 150));

		buyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) 
			{
			if (type == ui::Widget::TouchEventType::ENDED) 
			{
				// 调用购买物品的逻辑
				p->buyItem(shopItems[i].id);
				coinLabel->setString("Coins: " + std::to_string(p->getMoney()));
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

