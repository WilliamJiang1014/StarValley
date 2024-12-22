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

	bool weaponAdded = false; // 用于标记是否已经添加了武器
	while (shopItems.size() < 5)
	{
		int randomIndex = rand() % p->items.size();
		Item randomItem = p->items[randomIndex];

		// 检查是否已添加过武器
		if (randomItem.isWeapon && weaponAdded)
		{
			continue; // 如果已经有武器了，跳过该物品
		}

		shopItems.push_back(randomItem);

		// 如果是武器，更新标记
		if (randomItem.isWeapon)
		{
			weaponAdded = true;
		}
	}

	// 创建商店界面UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// 显示玩家的当前金币
	coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 36);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// 创建购买物品的按钮
	for (int i = 0; i < shopItems.size(); i++)
	{
		string itemImage = (shopItems[i].isWeapon ? "weapon/" : "Item/") + shopItems[i].name + (shopItems[i].isWeapon ? "_icon.png" : ".png");
		auto buyButton = ui::Button::create(itemImage, itemImage, itemImage);
		buyButton->setScale(1.0f); // 根据需要调整按钮的大小

		// 设置按钮位置（横向排列）
		float buttonSpacing = 350; // 按钮间距，可以根据需要调整
		float totalWidth = buttonSpacing * (shopItems.size() - 1); // 总间距：按钮间距 * (按钮数 - 1)
		float startX = (winSize.width - totalWidth) / 2; // 起始X坐标，确保按钮居中
		buyButton->setPosition(Vec2(startX + i * buttonSpacing, winSize.height - 250));

		// 创建标签，显示按钮的文本
		auto label = Label::createWithTTF(shopItems[i].name, "fonts/Marker Felt.ttf", 24);
		label->setPosition(Vec2(startX + i * buttonSpacing, winSize.height - 250 - buyButton->getContentSize().height / 2 - 30)); 

		// 创建标签，显示装备的属性加成
		string attributesText = "Health: " + std::to_string(shopItems[i].health) +
			"\nStrength: " + std::to_string(shopItems[i].strength) +
			"\nAttack Speed: " + std::to_string(shopItems[i].attackSpeed) +
			"\nRange: " + std::to_string(shopItems[i].range) +
			"\nLife Regen: " + std::to_string(shopItems[i].lifeRegen);
		auto attributesLabel = Label::createWithTTF(attributesText, "fonts/Marker Felt.ttf", 24);
		attributesLabel->setPosition(Vec2(startX + i * buttonSpacing, winSize.height - 250 - buyButton->getContentSize().height / 2 - 150));

		buyButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					// 调用购买物品的逻辑
					p->buyItem(shopItems[i].id);
					coinLabel->setString("Coins: " + std::to_string(p->getMoney()));

					// 更新按钮状态
					buyButton->setEnabled(false);
					buyButton->setColor(Color3B(128, 128, 128)); // 使图片变暗
					buyButton->setTitleText("Sold");
				}
			});
		this->addChild(buyButton);
		this->addChild(label);
		this->addChild(attributesLabel); // 添加装备属性标签
	}

	// 创建关闭商店按钮
	auto closeButton = ui::Button::create("menu/EndGame.png");
	closeButton->setScale(2.2f);
	closeButton->setPosition(Vec2(winSize.width - 80, winSize.height - 70));
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


