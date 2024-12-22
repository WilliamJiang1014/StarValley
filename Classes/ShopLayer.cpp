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

	bool weaponAdded = false; // ���ڱ���Ƿ��Ѿ����������
	while (shopItems.size() < 5)
	{
		int randomIndex = rand() % p->items.size();
		Item randomItem = p->items[randomIndex];

		// ����Ƿ�����ӹ�����
		if (randomItem.isWeapon && weaponAdded)
		{
			continue; // ����Ѿ��������ˣ���������Ʒ
		}

		shopItems.push_back(randomItem);

		// ��������������±��
		if (randomItem.isWeapon)
		{
			weaponAdded = true;
		}
	}

	// �����̵����UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// ��ʾ��ҵĵ�ǰ���
	coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 36);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// ����������Ʒ�İ�ť
	for (int i = 0; i < shopItems.size(); i++)
	{
		string itemImage = (shopItems[i].isWeapon ? "weapon/" : "Item/") + shopItems[i].name + (shopItems[i].isWeapon ? "_icon.png" : ".png");
		auto buyButton = ui::Button::create(itemImage, itemImage, itemImage);
		buyButton->setScale(1.0f); // ������Ҫ������ť�Ĵ�С

		// ���ð�ťλ�ã��������У�
		float buttonSpacing = 350; // ��ť��࣬���Ը�����Ҫ����
		float totalWidth = buttonSpacing * (shopItems.size() - 1); // �ܼ�ࣺ��ť��� * (��ť�� - 1)
		float startX = (winSize.width - totalWidth) / 2; // ��ʼX���꣬ȷ����ť����
		buyButton->setPosition(Vec2(startX + i * buttonSpacing, winSize.height - 250));

		// ������ǩ����ʾ��ť���ı�
		auto label = Label::createWithTTF(shopItems[i].name, "fonts/Marker Felt.ttf", 24);
		label->setPosition(Vec2(startX + i * buttonSpacing, winSize.height - 250 - buyButton->getContentSize().height / 2 - 30)); 

		// ������ǩ����ʾװ�������Լӳ�
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
					// ���ù�����Ʒ���߼�
					p->buyItem(shopItems[i].id);
					coinLabel->setString("Coins: " + std::to_string(p->getMoney()));

					// ���°�ť״̬
					buyButton->setEnabled(false);
					buyButton->setColor(Color3B(128, 128, 128)); // ʹͼƬ�䰵
					buyButton->setTitleText("Sold");
				}
			});
		this->addChild(buyButton);
		this->addChild(label);
		this->addChild(attributesLabel); // ���װ�����Ա�ǩ
	}

	// �����ر��̵갴ť
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


