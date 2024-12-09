#include "GameOverLayer.h"
#include "CharacterSelectLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* GameOverLayer::createScene(bool playerWon)
{
	auto scene = Scene::create();
	auto layer = GameOverLayer::create(playerWon);
	layer->init(playerWon);
	scene->addChild(layer);

	return scene;
}

GameOverLayer* GameOverLayer::create(bool playerWon)
{
	GameOverLayer* layer = new GameOverLayer();
	if (layer && layer->init(playerWon))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return nullptr;
}

bool GameOverLayer::init(bool playeWon)
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getWinSize();

	// 创建结算label
	auto label = Label::createWithTTF(playeWon ? "You Win!" : "You Lose!", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(label);
	
	// 创建按钮
	auto retryButton = ui::Button::create("normal_image.png", "selected_image.png", "disabled_image.png");

	retryButton->setTitleText("Retry");
	retryButton->setTitleFontSize(24);

	retryButton->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - 50));

	retryButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) 
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			// 按下按钮后，返回到角色选择界面
			Director::getInstance()->replaceScene(CharacterSelectLayer::createScene());
			break;
		default:
			break;
		}
		});

	// 添加按钮到当前层
	this->addChild(retryButton);

	return true;
}


