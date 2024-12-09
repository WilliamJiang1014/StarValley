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

	// �����̵����UI
	createShopUI();

	return true;
}

void ShopLayer::createShopUI()
{
	auto winSize = Director::getInstance()->getWinSize();

	// ��ʾ��ҵĵ�ǰ���
	auto coinLabel = Label::createWithTTF("Coins: " + std::to_string(p->getMoney()), "fonts/arial.ttf", 24);
	coinLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 50));
	this->addChild(coinLabel);

	// ����������Ʒ�İ�ť
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
				// ������Ʒ
				if (p->buyItem(i)) 
				{
					log("Item %d purchased!", i);  // �������ɹ�����־
				}
				else 
				{
					log("Not enough coins to buy item %d", i); // �������ʧ�ܵ���־
				}
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

