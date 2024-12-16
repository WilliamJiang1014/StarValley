#include "CharacterSelectLayer.h"
//#include "GameLayer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;

Scene* CharacterSelectLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = CharacterSelectLayer::create();
	scene->addChild(layer);

	return scene;
}

bool CharacterSelectLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	auto winSize = Director::getInstance()->getWinSize();

	// 添加五个角色选择按钮
	for (int i = 0; i < 5; i++)
	{
		// 创建按钮，设置正常状态、选中状态和禁用状态的图片
		auto button = ui::Button::create("HelloWorld.png", "HelloWorld.png", "HelloWorld.png");

		// 设置按钮文本
		char buttonText[16];
		sprintf(buttonText, "Character %d", i + 1);
		button->setTitleText(buttonText);
		button->setTitleFontSize(24); // 设置按钮文本字体大小

		// 设置按钮位置
		button->setPosition(Vec2(winSize.width / 2, winSize.height - (i + 1) * 100));

		// 添加触摸事件监听器
		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				// 调用角色选择的处理逻辑
				this->SelectCharacter(i);
				end = false;
			}

			});

		// 将按钮添加到当前层
		this->addChild(button);
	}
	return true;
}

void CharacterSelectLayer::SelectCharacter(int characterIndex)
{
	// 将所选角色信息传递给 GameLayer
	UserDefault::getInstance()->setIntegerForKey("SelectedCharacter", characterIndex); // 保存所选择的角色索引
	//auto scene = GameLayer::createScene();
	//Director::getInstance()->replaceScene(scene);
}