#include "Layer_ishibashi.h"
#include "cocos2d/external/json/rapidjson.h"
#include "cocos2d/external/json/document.h"
#include "audio/include/AudioEngine.h"
#include "../Novel/ScriptHeart.h"

#include "../SceneManager.h"

USING_NS_CC;

namespace User
{
    Layer_meal::Layer_meal( )
    {
        setLayer( meal );
    }
    Layer_meal::Layer_meal( int layer )
    {
        setLayer( layer );
    }
    Layer_meal::~Layer_meal( )
    {
    }
    bool Layer_meal::init( )
    {
        if ( !Layer::init( ) ) return false;

        food = Sprite::create( );

        this->scheduleUpdate( );

        exist = false;
        reside = true;

        loadData( );
        mealDressVolume();
        Menu( );
        eatText( );
        character(fashion_show[now_dress], clear[now_dress]);
        //mealTutorial( );
		decoration();
        //heart();

        {
            auto scale = Director::getInstance( )->getContentScaleFactor( );

            auto button = ui::Button::create( u8"res/texture/system/backbutton.png" );
            addChild( button );
            button->setScale( 0.5, 0.5 );
            button->setAnchorPoint( Vec2( 0, 0 ) );
            button->addTouchEventListener( [ this ] ( Ref* pSender, ui::Widget::TouchEventType type )
            {
                if ( type == ui::Widget::TouchEventType::ENDED )
                {
                    SceneManager::createBreeding( );
                }
            } );
        }

		auto heart = HeartGauge::create()->make();
		if (heart)
		{

			heart->setAnchorPoint(Vec2(0, 1));
			heart->setPosition(Director::getInstance()->getVisibleOrigin() + Vec2(0, Director::getInstance()->getVisibleSize().height - 50));
			heart->setScale(0.85f);
			this->addChild(heart);
		}

        return true;
    }
    void Layer_meal::setup( )
    {
        //���j���[�\
    }
    void Layer_meal::update( float delta )
    {

    }

    void Layer_meal::setLayer( int _layerName )
    {
        change = _layerName;
    }

    //�H���̃��j���[�p�̐�����
    void Layer_meal::eatText( )
    {

		auto board = Sprite::create();
		board->setTextureRect(Rect( 0, 0, 640, 200));
		board->setColor(Color3B::WHITE);
		board->setPosition(Point(365, 225));
		this->addChild(board);

        Sprite* sprite = Sprite::create("res/texture/item/message_window_life.png");
        //sprite->setTextureRect( Rect( 0, 0, 600, 200 ) );
        //sprite->setColor( Color3B::WHITE );
        //sprite->setName( "Text" );
        sprite->setPosition( Point( 365, 225 ) );
        this->addChild( sprite );

        confirmButton( );
    }

    //����{�^��
    void Layer_meal::confirmButton( )
    {
        //�{�^�����쐬����
        ui::Button * button = ui::Button::create( "res/texture/button.png" );
        button->setTouchEnabled( true );

        //�{�^���̈ʒu�ݒ�
        button->setPosition( Vec2( 600, 275 ) );

        //�{�^���ɕ\�����镶��
        // �e�L�X�g
        button->setTitleText( u8"����" );
        // �t�H���g
        button->setTitleFontName( "Arial" );
        // �t�H���g�T�C�Y
        button->setTitleFontSize( 20 );
        // �t�H���g�J���[
        button->setTitleColor( Color3B::BLACK );
        button->setName( "delite" );

        //����{�^�����e
        button->addTouchEventListener( [ this ] ( Ref* button, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                buttonAudio( ".../button70.mp3", audio_volume );

                switch ( change )
                {
                case meal:
                    //�H���p�A�N�V�����i�b��j
                    animation( animation_num );
                    this->removeChildByName( "delite" );
					loveMetor();
                    reside = false;
                    break;
                case dressClothes:
                    //���ւ��p�A�N�V����
					dressAnimetion(now_dress, next_dress);
					dressChange();
                    break;
                default:
                    break;
                }
            }
        } );

        addChild( button );
    }

    void Layer_meal::Menu( )
    {
        //json�t�@�C���̓ǂݍ���
        auto fileUtils = FileUtils::getInstance( );
        auto path = fileUtils->getStringFromFile( "res/json/meal_clothes.json" );
        rapidjson::Document doc;

        //json�t�@�C�����p�[�X
        doc.Parse<rapidjson::kParseDefaultFlags>( path.c_str( ) );

        if ( !doc.HasParseError( ) )
        {
            const rapidjson::Value& buttonsData = doc["button_texture"];
            for ( int k = 0; k < 5; k++ )
            {
                food_button.push_back( buttonsData[k]["texture"].GetString( ) );
            }
        }

        if ( !doc.HasParseError( ) )
        {
            const rapidjson::Value& buttonsData = doc["dress_texture"];
            for ( int k = 0; k < 5; k++ )
            {
                dress_button.push_back( buttonsData[k]["clothes"].GetString( ) );
            }
        }

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["princess_texture"];
			for (int k = 0; k < 5; k++)
			{
				fashion_show.push_back(buttonsData[k]["princess"].GetString());
			}
		}

		if (!doc.HasParseError())
		{
			const rapidjson::Value& buttonsData = doc["clear_texture"];
			for (int k = 0; k < 5; k++)
			{
				clear.push_back(buttonsData[k]["clear"].GetString());
			}
		}

		now = UserDefault::getInstance();
		now_dress = now->getIntegerForKey(u8"���݂̕�");

		auto sprite = Sprite::create();
		sprite->setTextureRect(Rect(0, 0, 150, 900));
		sprite->setColor(Color3B::WHITE);
		sprite->setPosition(Point(600, 800));
		this->addChild(sprite);

        switch ( change )
        {
        case meal:
            for ( int i = 0; i < 5; ++i )
                normalButton( i, food_button[i], i );
            break;
        case dressClothes:
            for ( int i = 0; i < 5; ++i )
                normalButton( i, dress_button[i], 4 + i );
            break;
        default:
            break;
        }
    }

    void Layer_meal::foodText( std::string commentary, int x, int y, int size )
    {
        auto text = Label::createWithSystemFont( commentary, "Arial", size );
        text->setPosition( Point( 400 - x * 48, 210 + y) );
        text->setColor( ccc3( 255, 0, 0 ) );
        text->setName( "commentary_text" );
        this->addChild( text );
    }

    void Layer_meal::eraseFoodText( )
    {
        this->removeChildByName( "commentary_text" );
    }

    void Layer_meal::selectedItemEvent( Ref *pSender, cocos2d::ui::ListView::EventType type )
    {
        switch ( type )
        {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            auto listView = static_cast<ui::ListView*>( pSender );
            CCLOG( "Select Item Start Index = %ld", listView->getCurSelectedIndex( ) );
            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            auto listView = static_cast<ui::ListView*>( pSender );
            CCLOG( "Select Child End Index = %ld", listView->getCurSelectedIndex( ) );
            break;
        }
        default:
            break;
        }
    }

   /* void Layer_meal::eatTime( std::string eatTime )
    {
        Sprite* sprite = Sprite::create( );
        sprite->setTextureRect( Rect( 0, 0, 100, 50 ) );
        sprite->setColor( Color3B::WHITE );
        sprite->setPosition( Point( 300, 1100 ) );
        this->addChild( sprite );

        auto text = Label::createWithSystemFont( eatTime, "Arial", 24 );
        text->setPosition( Point( 300, 1100 ) );
        text->setColor( ccc3( 0, 0, 0 ) );
        text->setName( "time_text" );
        this->addChild( text );
    }*/

    void Layer_meal::character(std::string chara_texture, std::string puppet)
    {
        cocos2d::Sprite * kuroe = Sprite::create( "res/texture/" + puppet);
        kuroe->setScale( 0.3 );
		kuroe->setName("KUROE");
		kuroe->setOpacity(0);
        kuroe->setPosition( Vec2( 285, 700 ) );
        this->addChild( kuroe );

		auto dress = Sprite::create("res/texture/item/dress_setup/" + chara_texture);
		dress->setScale(0.3);
		dress->setName("costume");
		dress->setOpacity(0);
		dress->setPosition(Vec2(285, 700));
		this->addChild(dress);

		//�t�F�[�h 1�b�ŁA100%��  
		CCFiniteTimeAction* fade = FadeIn::create(2);
		kuroe->runAction(fade);
		CCFiniteTimeAction* fade2 = FadeIn::create(2);
		dress->runAction(fade2);
    }

	void Layer_meal::eraseCharacter()
	{
		removeChildByName("KUROE");
		removeChildByName("costume");
	}

    void Layer_meal::animation( int anime_num )
    {
        food = Sprite::create( "res/texture/item/" + food_button[anime_num] );
        food->setPosition( Vec2( 280, 1050 ) );
        food->setScale( 0.5 );
        this->addChild( food );

        CCFiniteTimeAction* move = CCMoveTo::create( 1.0f, ccp( 280, 850 ) );
        food->runAction( move );

		//�t�F�[�h 1�b�ŁA100%��  
		CCFiniteTimeAction* fade = CCFadeTo::create(1.0f, 0);
        food->runAction( fade );
    }

	void Layer_meal::dressAnimetion(int my_dress, int dress_num)
	{
		eraseCharacter();

		Sprite * kuroe = Sprite::create("res/texture/" + clear[my_dress]);
		kuroe->setScale(0.3);
		kuroe->setName("fashion");
		kuroe->setPosition(Vec2(285, 700));
		this->addChild(kuroe);

		auto dress = Sprite::create("res/texture/item/dress_setup/" + fashion_show[my_dress]);
		dress->setScale(0.3);
		dress->setName("changeCostume");
		dress->setPosition(Vec2(285, 700));
		this->addChild(dress);

		//�t�F�[�h 1�b�ŁA100%��  
		CCFiniteTimeAction* fade = FadeOut::create(1);
		kuroe->runAction(fade);
		CCFiniteTimeAction* fade2 = FadeIn::create(2);
		dress->runAction(fade2);

		character(fashion_show[dress_num], clear[dress_num]);
	}

    void Layer_meal::normalButton( int text_number, std::string button_photo, int normalButtonTag )
    {
        auto button = ui::Button::create( "res/texture/item/" + button_photo );//�{�^���摜

        button->setScale9Enabled( true );
        button->setPosition( Vec2( 600, 1150 - 180 * text_number ) );

        int w = 255;

        switch ( change )
        {
        case meal:
			if (food_gain[text_number] == false) w = 150;
            break;
        case dressClothes:
            if ( dress_gain[text_number] == false ) w = 180;
            break;
        default:
            break;
        }
        button->setOpacity( w );//�����x0�Ŋ��S�����A255�Ŏ��̉�
        button->setTag( normalButtonTag );

        //�{�^�����������Ƃ��̔���
        button->addTouchEventListener( [ this, text_number ] ( Ref* button, ui::Widget::TouchEventType type )
        {
            if ( type == ui::Widget::TouchEventType::ENDED )
            {
                switch ( change )
                {
                case meal://�H���p
					if (food_gain[text_number] == true) {
						if (reside == true)
						{
							buttonAudio(".../button70.mp3", audio_volume);
							love_degrees = text_number;

							animation_num = text_number;

							eraseFoodText();
							eraseFoodText();
							eraseFoodText();
							foodText(food_commentary[text_number], 3, 70, 48);
							foodText(food_text2[text_number], 0, 0, 36);
							foodText(food_text3[text_number], 0, -48, 36);
						}
					}
                    break;
                case dressClothes://���ւ��p
					if (dress_gain[text_number] == true) {
						if (reside == true)
						{
							buttonAudio(".../button70.mp3", audio_volume);

							//���ւ��铮�������
							eraseFoodText();
							eraseFoodText();
							eraseFoodText();
							foodText(dress_commentary[text_number], 3, 70, 48);
							foodText(dress_text2[text_number], 0, 0, 36);
							foodText(dress_text3[text_number], 0, -48, 36);
							next_dress = text_number;
						}
					}

					
					removeChildByName("fashion");
					removeChildByName("changeCostume");

                    break;
                default:
                    break;
                }
            }
        } );

        addChild( button );
    }

    void Layer_meal::heart( )
    {
        auto spirit = Sprite::create( "res/texture/heart.png" );
        spirit->setPosition( Vec2( 110, 1100 ) );
        spirit->setScale( 0.8 );
        addChild( spirit );
    }

    void Layer_meal::buttonAudio( std::string audio_name, int volume )
    {
        int id = experimental::AudioEngine::play2d( "res/sound/SE" + audio_name );
        experimental::AudioEngine::setVolume( id, volume );
    }

    void Layer_meal::mealDressVolume()
    {
		auto volume = UserDefault::getInstance();

        audio_volume = volume->getFloatForKey("se");
    }

    void Layer_meal::mealTutorial( )
    {
        auto left_line = Sprite::create( );
        left_line->setTextureRect( Rect( 0, 0, 10, 900 ) );
        left_line->setColor( Color3B::RED );
        left_line->setPosition( Point( 500, 800 ) );
        left_line->setName( "left" );
        this->addChild( left_line );

        auto right_line = Sprite::create( );
        right_line->setTextureRect( Rect( 0, 0, 10, 900 ) );
        right_line->setColor( Color3B::RED );
        right_line->setPosition( Point( 700, 800 ) );
        right_line->setName( "right" );
        this->addChild( right_line );

        auto top_line = Sprite::create( );
        top_line->setTextureRect( Rect( 0, 0, 210, 10 ) );
        top_line->setColor( Color3B::RED );
        top_line->setPosition( 600, 1250 );
        top_line->setName( "top" );
        this->addChild( top_line );

        auto under_line = Sprite::create( );
        under_line->setTextureRect( Rect( 0, 0, 210, 10 ) );
        under_line->setColor( Color3B::RED );
        under_line->setPosition( 600, 350 );
        under_line->setName( "under" );
        this->addChild( under_line );


		//������
        auto text_board = Sprite::create( );
        text_board->setTextureRect( Rect( 0, 0, 200, 400 ) );
        text_board->setColor( Color3B::WHITE );
        text_board->setPosition( Vec2( 300, 600 ) );
        text_board->setName( "text_broard" );
        this->addChild( text_board );
    }

    void Layer_meal::eraseMealTutorial( )
    {
        this->removeChildByName( "left" );
        this->removeChildByName( "right" );
        this->removeChildByName( "top" );
        this->removeChildByName( "under" );
        this->removeChildByName( "text_broard" );
    }

	void Layer_meal::decoration()
	{
		auto left_line = Sprite::create("res/texture/item/b_ornament_100_0M.png");
		//left_line->setTextureRect(Rect(0, 0, 10, 900));
		left_line->setRotation(90);
		left_line->setPosition(Point(500, 800));
		this->addChild(left_line);

		auto right_line = Sprite::create("res/texture/item/b_ornament_100_0M.png");
		//right_line->setTextureRect(Rect(0, 0, 10, 900));
		right_line->setRotation(270);
		right_line->setPosition(Point(700, 800));
		this->addChild(right_line);

		auto top_line = Sprite::create("res/texture/item/b_ornament_100_0M_TU.png");
		//top_line->setTextureRect(Rect(0, 0, 210, 10));
		top_line->setRotation(180);
		top_line->setPosition(600, 1250);
		this->addChild(top_line);

		auto under_line = Sprite::create("res/texture/item/b_ornament_100_0M_TU.png");
		//under_line->setTextureRect(Rect(0, 0, 210, 10));
		under_line->setPosition(600, 350);
		this->addChild(under_line);
	}

    void Layer_meal::loadData( )
    {
        auto item = UserDefault::getInstance();

        food_gain.push_back(item->getBoolForKey(u8"�p����"));
        food_gain.push_back(item->getBoolForKey(u8"��"));
        food_gain.push_back(item->getBoolForKey(u8"�ʕ�"));
        food_gain.push_back(item->getBoolForKey(u8"�R���y�C�g�E"));
        food_gain.push_back(item->getBoolForKey(u8"���"));
        dress_gain.push_back(item->getBoolForKey(u8"��A"));
        dress_gain.push_back(item->getBoolForKey(u8"��B"));
        dress_gain.push_back(item->getBoolForKey(u8"��C"));
        dress_gain.push_back(item->getBoolForKey(u8"��D"));
        dress_gain.push_back(item->getBoolForKey(u8"��E"));
    }

	void Layer_meal::dressChange()
	{
		now->setIntegerForKey(u8"���݂̕�", next_dress);
	}

	//���m�F
	void Layer_meal::loveMetor()
	{
		int love_gauge;

		auto love = UserDefault::getInstance();
		love_gauge = love->getIntegerForKey(u8"�e���x");
		love_gauge += love_degrees;
		love->setIntegerForKey(u8"�e���x", love_gauge);
	}
}