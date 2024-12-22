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
		string ButtonImage = "character/character0" + to_string(i) + ".png";
		auto button = ui::Button::create(ButtonImage);
		button->setScale(1.0f); // �ɸ�����Ҫ������ť�Ĵ�С

		// ���ð�ťλ��
		float buttonSpacing = 300; // ��ť��࣬���Ը�����Ҫ����
		float totalWidth = buttonSpacing * (5 - 1); // �ܼ�ࣺ��ť��� * (��ť�� - 1)
		float startX = (winSize.width - totalWidth) / 2; // ��ʼX���꣬ȷ����ť����
		button->setPosition(Vec2(startX + i * buttonSpacing, winSize.height / 2));
		
		// ������ǩ��ʾ��ť���ı�
		char buttonText[16];
		sprintf(buttonText, "Character %d", i + 1);
		auto label = Label::createWithTTF(buttonText, "fonts/Marker Felt.ttf", 50);
		label->setPosition(Vec2(startX + i * buttonSpacing, winSize.height / 2 - button->getContentSize().height / 2 - 30)); // ���ñ�ǩ�ڰ�ť�·�

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
		// ����ǩ��ӵ���ǰ��
		this->addChild(label);
	}

	// �������ϽǵĹ�����Ϣ��ǩ
	auto infoLabel = Label::createWithTTF("Character Select", "fonts/Marker Felt.ttf", 100);
	infoLabel->setPosition(Vec2(960, winSize.height - 100));  // ���ñ�ǩλ��Ϊ���Ͻ�
	this->addChild(infoLabel);

	return true;
}

void CharacterSelectLayer::SelectCharacter(int characterIndex)
{
	// ����ѡ��ɫ��Ϣ���ݸ� GameLayer
	UserDefault::getInstance()->setIntegerForKey("SelectedCharacter", characterIndex); // ������ѡ��Ľ�ɫ����
	//auto scene = GameLayer::createScene();
	//Director::getInstance()->replaceScene(scene);
}