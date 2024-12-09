#include "ShopLayer.h"
#include "GameLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* ShopLayer::createScene(Player* player)
{
	auto scene = Scene::create();
	auto layer = ShopLayer::create(player); // ��Ҫ�ֶ���������
	layer->init(player);
	scene->addChild(layer);

	return scene;
}

ShopLayer* ShopLayer::create(Player* player)
{
	// �ֶ���������
	ShopLayer* layer = new (nothrow) ShopLayer();
	if (layer && layer->init(player))
	{
		layer->autorelease();
		return layer;
	}

	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool ShopLayer::init(Player* player)
{
	if (!Layer::init())
	{
		return false;
	}
	this->player = player;

	// ��ʾ��ǰ�����
	auto coinLabel = Label::createWithTTF("Coins: " + std::to_string(player->getCoins()), "fonts/arial.ttf", 24);
	coinLabel->setPosition(Vec2(200, 500));
	this->addChild(coinLabel);

	auto winSize = Director::getInstance()->getWinSize();

	// ������Ʒ��ť
	for(int i =0;i<5;i++)
	{
		auto buyButton = ui::Button::create("normal_image.png", "selected_image.png", "disabled_image.png");
		buyButton->setTitleText("Item " + std::to_string(i + 1));
		buyButton->setTitleFontSize(24); // ���ð�ť�ı������С
		buyButton->setPosition(Vec2(winSize.width / 2, winSize.height - (i + 1) * 100));
		buyButton->addTouchEventListener([player, i](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				// ��������Ʒ���߼�
				player->buyItem(i);
			}
			});

		this->addChild(buyButton);
	}

	// �ر��̵갴ť
	auto closeButton = ui::Button::create("close_button.png", "close_button_selected.png");
	closeButton->setPosition(Vec2(400, 500));
	closeButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) 
		{
		if (type == ui::Widget::TouchEventType::ENDED) 
		{
			this->removeFromParent();  // �ر��̵����
			Director::getInstance()->replaceScene(GameLayer::createScene());  // ������һ��ս��
		}
		});
	this->addChild(closeButton);

	return true;
}

