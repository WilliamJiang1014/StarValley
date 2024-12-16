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

	// ��������ɫѡ��ť
	for (int i = 0; i < 5; i++)
	{
		// ������ť����������״̬��ѡ��״̬�ͽ���״̬��ͼƬ
		auto button = ui::Button::create("HelloWorld.png", "HelloWorld.png", "HelloWorld.png");

		// ���ð�ť�ı�
		char buttonText[16];
		sprintf(buttonText, "Character %d", i + 1);
		button->setTitleText(buttonText);
		button->setTitleFontSize(24); // ���ð�ť�ı������С

		// ���ð�ťλ��
		button->setPosition(Vec2(winSize.width / 2, winSize.height - (i + 1) * 100));

		// ��Ӵ����¼�������
		button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				// ���ý�ɫѡ��Ĵ����߼�
				this->SelectCharacter(i);
				end = false;
			}

			});

		// ����ť��ӵ���ǰ��
		this->addChild(button);
	}
	return true;
}

void CharacterSelectLayer::SelectCharacter(int characterIndex)
{
	// ����ѡ��ɫ��Ϣ���ݸ� GameLayer
	UserDefault::getInstance()->setIntegerForKey("SelectedCharacter", characterIndex); // ������ѡ��Ľ�ɫ����
	//auto scene = GameLayer::createScene();
	//Director::getInstance()->replaceScene(scene);
}