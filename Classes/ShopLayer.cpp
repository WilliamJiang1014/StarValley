#include "cocos2d.h"
#include "ShopLayer.h"
#include "player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* ShopLayer::createScene(player* p)
{
	auto scene = Scene::create();
	auto layer = ShopLayer::create(p); // ��Ҫ�ֶ���������
	layer->init(p);
	scene->addChild(layer);

	return scene;
}

ShopLayer* ShopLayer::create(player* p)
{
	// �ֶ���������
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

	// ������Ʒ
	p->loadItems();
	srand(time(0)); // ��ʼ���������
	while (shopItems.size() < 5)
	{
		int randomIndex = rand() % p->items.size();
		Item randomItem = p->items[randomIndex];
		shopItems.push_back(randomItem);
	}
	// �����̵����UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// ��ʾ��ҵĵ�ǰ���
	coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 24);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// ����������Ʒ�İ�ť
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
				// ���ù�����Ʒ���߼�
				p->buyItem(shopItems[i].id);
				coinLabel->setString("Coins: " + std::to_string(p->getMoney()));
			}
			});
		this->addChild(buyButton);
	}

	// �����ر��̵갴ť
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

