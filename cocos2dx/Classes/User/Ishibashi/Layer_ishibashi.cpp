#include "Layer_ishibashi.h"

#define BUTTON_POS_X 340//�{�^���̈ʒu(x)
#define BUTTON_POS_Y 120//�{�^���̈ʒu(y)

USING_NS_CC;

namespace User
{
	Layer_ishibashi::Layer_ishibashi()
	{
	}
	Layer_ishibashi::~Layer_ishibashi()
	{
	}
	bool Layer_ishibashi::init()
	{
		if (!Layer::init()) return false;

		food = Sprite::create();

		this->scheduleUpdate();

		exist = false;

		eatMenu();
		eatText();

		return true;
	}
	void Layer_ishibashi::setup()
	{
		//���j���[�\
	}
	void Layer_ishibashi::update(float delta)
	{

	}

	//�H���̃��j���[�p�̐�����
	void Layer_ishibashi::eatText()
	{

		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 600, 200));
		sprite->setColor(Color3B::WHITE);
		sprite->setName("Text");

		float x = 365;
		float y = 200;
		sprite->setPosition(Point(x, y));
		this->addChild(sprite);

		showButton();
	}

	//�E�B���h�E���ǂ��폜�p
	void Layer_ishibashi::erase_eatText()
	{
		this->removeChildByName("Text");
	}

	void Layer_ishibashi::showButton()
	{
		//�{�^�����쐬����
		ui::Button * button = ui::Button::create();
		button->setTouchEnabled(true);
		button->loadTextures( "res/texture/button.png", "res/texture/button.png" );

		//�{�^���̈ʒu�ݒ�
		button->setPosition(Vec2(600, 200));

		//�{�^���ɕ\�����镶��
		// �e�L�X�g
		button->setTitleText("Confirm");
		// �t�H���g
		button->setTitleFontName("res/fonts/Arial");
		// �t�H���g�T�C�Y
		button->setTitleFontSize(20);
		// �t�H���g�J���[
		button->setTitleColor(Color3B::BLACK);

		//����{�^��
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
		{

		});

		addChild(button);
	}

	void Layer_ishibashi::eatMenu()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto listView = ui::ListView::create();
		listView->setContentSize(Size(400, 700));//defult Size(240,320)
		listView->setPosition(Vec2(550, 400));
		listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		listView->setBounceEnabled(true);
		this->addChild(listView);

		//eatTexture();

		//15�̃R���e���c�̍쐬
		for (int i = 0; i < food_name.size(); ++i)
		{
			//���C�A�E�g�ɕ\������{�^�����쐬
			auto button = ui::Button::create("res/texture/button.png", "res/texture/button.png" );//�{�^���摜
			button->setScale9Enabled(true);
			button->setPosition(button->getContentSize() / 2);
			button->setTitleText(food_name[i]);//�H�ו��@�A�C�e����

			//�{�^�����������Ƃ��̔���
			button->addTouchEventListener([this, i](Ref* button, ui::Widget::TouchEventType type)
			{
				if (type == ui::Widget::TouchEventType::ENDED)
				{
					if (exist)
					{
						eatTexture(i);
					}
					else
					{
						food = Sprite::create("res/texture/" + food_texture[i]);
						food->setPosition(Vec2(200, 400));
						this->addChild(food);
						exist = true;
					}
				}
			});
			//CCLOG("%d\n", food_name[i]);
			//���C�A�E�g���쐬
			auto layout = ui::Layout::create();
			layout->setContentSize(button->getContentSize());
			layout->addChild(button);
			listView->addChild(layout);
		}
	}

	void Layer_ishibashi::selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type)
	{
		switch (type)
		{
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Item Start Index = %ld", listView->getCurSelectedIndex());
			break;
		}//
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Child End Index = %ld", listView->getCurSelectedIndex());
			break;
		}
		default:
			break;
		}
	}

	void Layer_ishibashi::eatTexture(int food_num)
	{
		food->setSpriteFrame(Sprite::create("res/texture/" + food_texture[food_num])->getSpriteFrame());
	}

	//void Layer_ishibashi::erase_eatTexture(int erase_num)
	//{

	//}
}