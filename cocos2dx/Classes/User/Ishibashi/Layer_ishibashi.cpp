#include "Layer_ishibashi.h"
#include "cocos2d/external/json/rapidjson.h"
#include "cocos2d/external/json/document.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace experimental;

namespace User
{
	Layer_ishibashi::Layer_ishibashi()
	{
		setLayer(meal);
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
		reside = true;

		loadData();
		mealDressVolume(1.0f);
		Menu();
		eatText();
<<<<<<< HEAD

=======
		character();
		mealTutorial();
		//heart();
		
>>>>>>> 8651947... 画像差し替え他
		return true;
	}
	void Layer_ishibashi::setup()
	{
		//���j���[�\
	}
	void Layer_ishibashi::update(float delta)
	{

	}

	void Layer_meal::setLayer(int _layerName)
	{
		change = _layerName;
	}

	//�H���̃��j���[�p�̐�����
	void Layer_ishibashi::eatText()
	{

		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 600, 200));
		sprite->setColor(Color3B::WHITE);
		sprite->setName("Text");
<<<<<<< HEAD
=======

>>>>>>> 8651947... 画像差し替え他

		float x = 365;
		float y = 225;
		sprite->setPosition(Point(x, y));
		this->addChild(sprite);

		showButton();
	}

<<<<<<< HEAD
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
=======
	//����{�^��
	void Layer_meal::confirmButton()
	{
		//�{�^�����쐬����
		ui::Button * button = ui::Button::create("res/texture/button.png");
		button->setTouchEnabled(true);
>>>>>>> 8651947... 画像差し替え他

		//�{�^���̈ʒu�ݒ�
		button->setPosition(Vec2(600, 225));

		//�{�^���ɕ\�����镶��
		// �e�L�X�g
		button->setTitleText("Confirm");
		// �t�H���g
		button->setTitleFontName("res/fonts/Arial");
		// �t�H���g�T�C�Y
		button->setTitleFontSize(20);
		// �t�H���g�J���[
		button->setTitleColor(Color3B::BLACK);

<<<<<<< HEAD
		//����{�^��
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
=======
		//����{�^�����e
		button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				buttonAudio(".../button70.mp3",audio_volume);

				switch (change)
				{
				case meal:
					//�H���p�A�N�V�����i�b��j
					animation(animation_num);
					this->removeChildByName("delite");
					reside = false;
					break;
				case dressClothes:
					//���ւ��p�A�N�V����
					break;
				default:
					break;
				}
			}
		});

		addChild(button);
	}

	//�z�[���{�^��
	//void Layer_meal::backButton()
	//{
	//	//�{�^�����쐬����
	//	ui::Button * button = ui::Button::create("res/texture/button.png");
	//	button->setTouchEnabled(true);

	//	//�{�^���̈ʒu�ݒ�
	//	button->setPosition(Vec2(125, 1100));

	//	//�{�^���ɕ\�����镶��
	//	// �e�L�X�g
	//	button->setTitleText("Back");
	//	// �t�H���g
	//	button->setTitleFontName("Arial");
	//	// �t�H���g�T�C�Y
	//	button->setTitleFontSize(20);
	//	// �t�H���g�J���[
	//	button->setTitleColor(Color3B::BLACK);

	//	//�z�[���{�^�����e
	//	button->addTouchEventListener([this](Ref* button, ui::Widget::TouchEventType type)
	//	{
	//		
	//	});

	//	addChild(button);
	//}


	//void Layer_meal::Menu()
	//{
	//	Size visibleSize = Director::getInstance()->getVisibleSize();
	//	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//	auto listView = ui::ListView::create();
	//	listView->setContentSize(Size(700, 400));
	//	listView->setPosition(Vec2(50, 500));
	//	listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	//	listView->setBounceEnabled(true);
	//	this->addChild(listView);

	//	//json�t�@�C���̓ǂݍ���
	//	auto fileUtils = FileUtils::getInstance();
	//	auto path = fileUtils->getStringFromFile("res/json/meal_clothes.json");
	//	rapidjson::Document doc;

	//	//json�t�@�C�����p�[�X
	//	doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

	//	if (!doc.HasParseError())
	//	{
	//		const rapidjson::Value& buttonsData = doc["button_texture"];
	//		for (int k = 0; k < food_name.size(); k++)
	//		{
	//			food_button.push_back(buttonsData[k]["texture"].GetString());
	//		}
	//	}

	//	if (!doc.HasParseError())
	//	{
	//		const rapidjson::Value& buttonsData = doc["dress_texture"];
	//		for (int k = 0; k < food_name.size(); k++)
	//		{
	//			dress_button.push_back(buttonsData[k]["clothes"].GetString());
	//		}
	//	}

	//	switch (change)
	//	{
	//	case meal:
	//		//5�̃R���e���c�̍쐬
	//		for (int i = 0; i < food_name.size(); ++i)
	//		{
	//			//���C�A�E�g�ɕ\������{�^�����쐬
	//			cocos2d::Sprite * button = cocos2d::Sprite::create("res/texture/" + food_button[i]);//�{�^���摜
	//			//button->setScale9Enabled(true);
	//			button->setPosition(button->getContentSize() / 2);
	//			button->setTag(i);

	//			//���C�A�E�g���쐬
	//			auto layout = ui::Layout::create();
	//			layout->setContentSize(button->getContentSize());
	//			layout->addChild(button);
	//			listView->addChild(layout);
	//		}
	//		break;
	//	case dressClothes:
	//		//5�̃R���e���c�̍쐬
	//		for (int i = 0; i < food_name.size(); ++i)
	//		{
	//			//���C�A�E�g�ɕ\������{�^�����쐬
	//			cocos2d::Sprite * button = cocos2d::Sprite::create("res/texture/" + dress_button[i]);//�{�^���摜
	//			//button->setScale9Enabled(true);
	//			button->setPosition(button->getContentSize() / 2);
	//			button->setTag(5 + i);

	//			//���C�A�E�g���쐬
	//			auto layout = ui::Layout::create();
	//			layout->setContentSize(button->getContentSize());
	//			layout->addChild(button);
	//			listView->addChild(layout);
	//		}
	//		break;
	//	default:
	//		break;
	//	}
	//}

	void Layer_meal::Menu()
	{
		//json�t�@�C���̓ǂݍ���
		auto fileUtils = FileUtils::getInstance();
		auto path = fileUtils->getStringFromFile("res/json/meal_clothes.json");
		rapidjson::Document doc;

		//json�t�@�C�����p�[�X
		doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

		if (!doc.HasParseError())
>>>>>>> 8651947... 画像差し替え他
		{
			const rapidjson::Value& buttonsData = doc["button_texture"];
			for (int k = 0; k < 5; k++)
			{
				food_button.push_back(buttonsData[k]["texture"].GetString());
			}
		}

<<<<<<< HEAD
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
=======
		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["dress_texture"];
			for (int k = 0; k < 5; k++)
			{
				dress_button.push_back(buttonsData[k]["clothes"].GetString());
			}
		}

		
			food_gain.push_back(true);


		switch (change)
		{
		case meal:
			for (int i = 0; i < 5; ++i)
				normalButton(i, food_button[i], i);
			break;
		case dressClothes:
			for (int i = 0; i < 5; ++i)
				normalButton(i, dress_button[i], 4 + i);
			break;
		default:
			break;
		}
	}

	void Layer_meal::foodText(std::string commentary, int y)
	{
		auto text = Label::createWithSystemFont(commentary, "Arial", 48);
		text->setPosition(Point(300, 225));
		text->setColor(ccc3(255, 0, 0));
		text->setName("commentary_text");
		this->addChild(text);
	}

	void Layer_meal::eraseFoodText()
	{
		this->removeChildByName("commentary_text");
	}

	void Layer_meal::selectedItemEvent(Ref *pSender, cocos2d::ui::ListView::EventType type)
>>>>>>> 8651947... 画像差し替え他
	{
		switch (type)
		{
		case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
		{
			auto listView = static_cast<ui::ListView*>(pSender);
			CCLOG("Select Item Start Index = %ld", listView->getCurSelectedIndex());
			break;
		}
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

<<<<<<< HEAD
	void Layer_ishibashi::eatTexture(int food_num)
	{
		food->setSpriteFrame(Sprite::create("res/texture/" + food_texture[food_num])->getSpriteFrame());
	}

	//void Layer_ishibashi::erase_eatTexture(int erase_num)
	//{

	//}
=======
	//void Layer_meal::eatButton(int food_num)
	//{
	//	//json�t�@�C���̓ǂݍ���
	//	auto fileUtils = FileUtils::getInstance();
	//	auto path = fileUtils->getStringFromFile("res/json/meal_clothes.json");
	//	rapidjson::Document doc;

	//	//json�t�@�C�����p�[�X
	//	doc.Parse<rapidjson::kParseDefaultFlags>(path.c_str());

	//	if (!doc.HasParseError())
	//	{
	//		const rapidjson::Value& buttonsData = doc["button_texture"];
	//		for (int k = 0; k < 5; k++)
	//		{
	//			food_button.push_back(buttonsData[k]["texture"].GetString());
	//		}
	//	}

	//	food = Sprite::create("res/texture/" + food_button[food_num]);
	//	food->setPosition(Vec2(285, 800));
	//	this->addChild(food);
	//}

	void Layer_meal::eatTime(std::string eatTime)
	{
		Sprite* sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 100, 50));
		sprite->setColor(Color3B::WHITE);
		sprite->setPosition(Point(300, 1100));
		this->addChild(sprite);

		auto text = Label::createWithSystemFont(eatTime, "Arial", 24);
		text->setPosition(Point(300, 1100));
		text->setColor(ccc3(0, 0, 0));
		text->setName("time_text");
		this->addChild(text);
	}

	void Layer_meal::character()
	{
		cocos2d::Sprite * kuroe = Sprite::create(u8"res/texture/novel/�N���G����.png");
		kuroe->setScale(0.3);
		kuroe->setPosition(Vec2(285, 600));
		this->addChild(kuroe);
	}

	void Layer_meal::animation(int anime_num)
	{
		food = Sprite::create("res/texture/" + food_button[anime_num]);
		food->setPosition(Vec2(280, 1050));
		food->setScale(0.5);
		this->addChild(food);

		CCFiniteTimeAction* move = CCMoveTo::create(1.0f, ccp(280, 850));
		food->runAction(move);

		//�t�F�[�h 1�b�ŁA100%��  
		CCFiniteTimeAction* fade = CCFadeTo::create(1.0f, 0);
		food->runAction(fade);
	}

	void Layer_meal::normalButton(int text_number, std::string button_photo, int normalButtonTag)
	{
		auto button = ui::Button::create("res/texture/" + button_photo);//�{�^���摜

		button->setScale9Enabled(true);
		button->setPosition(Vec2(600, 1150 - 180 * text_number));

		int w = 255;

		switch (change)
		{
		case meal:
			if (food_gain[text_number] == true) w = 150;
			break;
		case dressClothes:
			if(dress_gain[text_number] == true) w = 180;
			break;
		default:
			break;
		}
		button->setOpacity(w);//�����x0�Ŋ��S�����A255�Ŏ��̉�
		button->setTag(normalButtonTag);

		//�{�^�����������Ƃ��̔���
		button->addTouchEventListener([this, text_number](Ref* button, ui::Widget::TouchEventType type)
		{
			if (type == ui::Widget::TouchEventType::ENDED)
			{
				switch (change)
				{
				case meal://�H���p
					if (reside == true)
					{
						buttonAudio(".../button70.mp3", audio_volume);

						animation_num = text_number;

						eraseFoodText();
						foodText(food_commentary[text_number], 1);
					}
					break;
				case dressClothes://���ւ��p
					if (reside == true)
					{
						buttonAudio(".../button70.mp3", audio_volume);

						//���ւ��铮�������
						eraseFoodText();
						foodText(dress_commentary[text_number], 1);
					}
					break;
				default:
					break;
				}
			}
		});

		addChild(button);
	}

	void Layer_meal::heart()
	{
		auto spirit = Sprite::create("res/texture/heart.png");
		spirit->setPosition(Vec2(110,1100));
		spirit->setScale(0.8);
		addChild(spirit);
	}

	void Layer_meal::buttonAudio(std::string audio_name, int volume)
	{
		int id = AudioEngine::play2d("res/sound/SE" + audio_name);
		experimental::AudioEngine::setVolume(id, volume);
	}

	void Layer_meal::mealDressVolume(int set)
	{
		audio_volume = set;
	}

	void Layer_meal::mealTutorial()
	{
		auto left_line = Sprite::create();
		left_line->setTextureRect(Rect(0, 0, 10, 900));
		left_line->setColor(Color3B::RED);
		left_line->setPosition(Point(500, 800));
		left_line->setName("left");
		this->addChild(left_line);

		auto right_line = Sprite::create();
		right_line->setTextureRect(Rect(0, 0, 10, 900));
		right_line->setColor(Color3B::RED);
		right_line->setPosition(Point(700, 800));
		right_line->setName("right");
		this->addChild(right_line);

		auto top_line = Sprite::create();
		top_line->setTextureRect(Rect(0, 0, 210, 10));
		top_line->setColor(Color3B::RED);
		top_line->setPosition(600, 1250);
		top_line->setName("top");
		this->addChild(top_line);

		auto under_line = Sprite::create();
		under_line->setTextureRect(Rect(0, 0, 210, 10));
		under_line->setColor(Color3B::RED);
		under_line->setPosition(600, 350);
		under_line->setName("under");
		this->addChild(under_line);

		auto text_board = Sprite::create();
		text_board->setTextureRect(Rect(0,0,200,400));
		text_board->setColor(Color3B::WHITE);
		text_board->setPosition(Vec2(300,600));
		text_board->setName("text_broard");
		this->addChild(text_board);
	}

	void Layer_meal::eraseMealTutorial()
	{
		this->removeChildByName("left");
		this->removeChildByName("right");
		this->removeChildByName("top");
		this->removeChildByName("under");
		this->removeChildByName("text_broard");
	}

	void Layer_meal::loadData()
	{
		auto path = FileUtils::getInstance()->getWritablePath();


		food_gain.push_back(true);
		food_gain.push_back(true);
		food_gain.push_back(true);
		food_gain.push_back(true);
		food_gain.push_back(true);
		dress_gain.push_back(true);
		dress_gain.push_back(true);
		dress_gain.push_back(true);
		dress_gain.push_back(true);
		dress_gain.push_back(true);
	}
>>>>>>> 8651947... 画像差し替え他
}